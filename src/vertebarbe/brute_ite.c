#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

const int NUM_THREADS = 8;
const char CHARSET[] = "abcdefghijklmnopqrstuvwxyz";//0123456789";//"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!_?.";
const int CHARSETLENGTH = sizeof(CHARSET) - 1;


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
		trVector[i] = start % (CHARSETLENGTH);
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

size_t bruteforce(int length)
{
	//char charset[] = "abcdefghijklmnopqrstuvwxyz";//0123456789";//"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!_?.";
	//int charsetLength = sizeof(charset) + 1;

	size_t total = 1;
	size_t n = 0;
	for (int i = 0; i < length; i++)
		total *= CHARSETLENGTH;


	//int trVectors[NUM_THREADS][length];
	size_t *endVector = calloc(1, (NUM_THREADS + 1) * sizeof(size_t));
	size_t chunk = total / NUM_THREADS;

	endVector[0] = 0;
	for (int i = 1; i < NUM_THREADS; i++)
		endVector[i] = endVector[i - 1] + chunk;
	endVector[NUM_THREADS] = total;

	#pragma omp parallel num_threads(NUM_THREADS)
	{
		int tid = omp_get_thread_num();
		size_t treated = endVector[tid];

		size_t treatedLoc = 0;

		char *pass = calloc(1, length + 1);

		int cur = length - 1;
		int max = length - 1;
		int curInCharset = 0;

		int *trVector = calloc(1, length * sizeof(int));


		//fill_tr_pass(endVector, pass, chunk * (tid + 1), length);

		fill_tr_pass(trVector, pass, endVector[tid] , length);

		//if (tid == NUM_THREADS - 1)
		//{
	//		chunk = chunkLast;
			//for (int i = 0; i < length; i++)
			//	endVector[i] = CHARSET[CHARSETLENGTH - 1];
	//	}
		//endVector[tid] = chunk;
		//endVector[NUM_THREADS] = total;

		printf("Thread %d started working from %s, chunk = %lu.\n", tid, pass, chunk);

		//#pragma omp barrier

		while ((cur >= 0 && treated <= endVector[tid+1]))
		{
			curInCharset = trVector[max];
			while (curInCharset < CHARSETLENGTH && treated < endVector[tid+1])
			{
				pass[max] = CHARSET[curInCharset];
				//test_password(pass);
				printf("%s\n", pass);
				curInCharset++;
				treated++;
				treatedLoc++;
			}

			cur--;
			while (cur >= 0 && trVector[cur] >= CHARSETLENGTH - 1)// && treated < endVector[tid+1])
			{
				trVector[cur] = 0;
				pass[cur] = CHARSET[0];
				cur--;
			}
			if (cur < 0 || treated >= endVector[tid+1])
			{
				printf("Thread %d finished working at %s\n", tid, pass); //at %s.\n", tid, pass);
				break;
			}
			trVector[cur]++;
			pass[cur] = CHARSET[trVector[cur]];
			cur = max;

		}
	

		printf("\nThread %d produced %lu passwords\n", tid, treatedLoc);
		n+=treatedLoc;
		free(pass);
		free(trVector);
	}
	free(endVector);
	printf("\nPasswords generated : %lu\n", n);
	return n;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;
	printf("Charset :%s\n", CHARSET);
	int length = atoi(argv[1]);
	size_t res = 1;
	size_t passes = bruteforce(length);
	for (int i = 0; i < length; i++)
		res*=CHARSETLENGTH;

	printf("CHARSETLENGTH ^ length = %d ^ %d = %lu.\n", CHARSETLENGTH, length, res);

	if (res == passes)
		printf("OK\n");
	else
		printf("KO\n");


	return 0;
}
