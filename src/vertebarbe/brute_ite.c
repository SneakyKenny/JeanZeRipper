#define _GNU_SOURCE
#include "brute_ite.h"
#include <omp.h>

int NUM_THREAD = 6;
char *CHARSET = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!_?.";
int CHARSETLENGTH = 66;


int round_nearest(int a, int b)
{
	printf("round : %f, %d\n", (float)a / (float)b, (a + b / 2) / b);
	return (a + b + 1) / b;
}

void fill_tr_pass(int *trVector, char *pass, size_t start, int length)
{
	int i = length - 1;

	//size_t temp = start;
	

	while (start > 0 && i >= 0)
	{
		trVector[i] = start % CHARSETLENGTH;
		pass[i] = CHARSET[trVector[i]];
		start /= CHARSETLENGTH;
		i--;
	}
	while (i >= 0)
	{
		pass[i] = CHARSET[0];
		trVector[i] = 0;
		i--;
	}
	
	//printf("%lu to base 26 : %s\n", temp, pass);
}

void concat(char *str1, char *str2)
{
	size_t i = 0;
	for (; str1[i]; i++){}
	for (size_t j = 0; str2[j]; j++, i++)
		str1[i] = str2[j];
	free(str2);
}

size_t bruteforce(int length, struct DData targets, void (*hash_func)(char *, char *), unsigned char hashLen, size_t nbTargets, char *result)
{
	off_t tLen = targets.St.st_size;
	char *tMap = targets.map;
	size_t total = 1;
	size_t n = 0;
	for (int i = 0; i < length; i++)
		total *= CHARSETLENGTH;


	size_t *endVector = calloc(1, (NUM_THREAD + 1) * sizeof(size_t));
	size_t chunk = total / NUM_THREAD;

	endVector[0] = 0;
	for (int i = 1; i < NUM_THREAD; i++)
		endVector[i] = endVector[i - 1] + chunk;
	endVector[NUM_THREAD] = endVector[NUM_THREAD - 1] + chunk + total % NUM_THREAD;

	#pragma omp parallel num_threads(NUM_THREAD)
	{
		int tid = omp_get_thread_num();
		size_t treated = endVector[tid];

		size_t treatedLoc = 0;

		char *pass = calloc(1, length + 1);
		char *hashed = calloc(1, hashLen + 1);

		int cur = length - 1;
		int max = length - 1;
		int curInCharset = 0;

		int *trVector = calloc(1, length * sizeof(int));
		fill_tr_pass(trVector, pass, endVector[tid] , length);
		printf("Thread %d started working from %s, chunk = %lu. Passwords to find: %lu\n", tid, pass, chunk, nbTargets);

		while ((cur >= 0 && treated <= endVector[tid+1]) && nbTargets > 0)
		{
			curInCharset = trVector[max];
			while (curInCharset < CHARSETLENGTH && treated < endVector[tid+1] && nbTargets > 0)
			{
				pass[max] = CHARSET[curInCharset];
				hash_func(pass, hashed);
				for (off_t i=0; i < tLen; i += hashLen)
				{
					if (is_same(tMap + i, hashed, hashLen, hashLen)){
						char **next;
						asprintf(next, "%s : %s\n", hashed, pass);
						concat(result, *next);
						nbTargets--;
						break;
					}
					i++; //skip '\n'
				}
				curInCharset++;
				treated++;
				treatedLoc++;
			}
			if (nbTargets <= 0)
				break;
			cur--;
			while (cur >= 0 && trVector[cur] >= CHARSETLENGTH - 1)
			{
				trVector[cur] = 0;
				pass[cur] = CHARSET[0];
				cur--;
			}
			if (cur < 0 || treated >= endVector[tid+1])
			{
				printf("Thread %d finished working at %s\n", tid, pass);
				break;
			}
			trVector[cur]++;
			pass[cur] = CHARSET[trVector[cur]];
			cur = max;
		}
		//printf("\nThread %d produced %lu passwords\n", tid, treatedLoc);
		n+=treatedLoc;
		free(pass);
		free(trVector);
		free(hashed);
		//printf("progress :%lu\\%lu passes\nStill %lu passwords to break.\n", n, total, nbTargets);
	}
	free(endVector);
	printf("\nPasswords generated : %lu\n", n);
	return nbTargets;
}


char *brut_attack(const char *targetPath, int maxLen, struct BData infos, int nb_threads, char *charset)
{
	CHARSET = charset;
	CHARSETLENGTH = strlen(charset);
	printf("Charset :%s, length:%d\n", CHARSET, CHARSETLENGTH);
	char *result = calloc(1, 4096);
	NUM_THREAD = nb_threads;
	printf("threads: %d\n", NUM_THREAD);
	struct DData targets = get_data(targetPath);
	size_t nbTargets = targets.St.st_size / infos.hashLen;
	for (int i = 1; i <= maxLen && nbTargets > 0; i++)
		nbTargets = bruteforce(i, targets, infos.hash_func, infos.hashLen, nbTargets, result);
	free(targets.map);

	return result;
}
