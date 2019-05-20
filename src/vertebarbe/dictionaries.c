#define _GNU_SOURCE
#include "brute_ite.h" //for the concat()
#include "dictionaries.h"
#include "../purple/hashing/hash.h"
#include <omp.h>

//TODO : Function to choose hash function from integrer
//
//TODO : Function which puts targets in hash table if
//		 there is more target than words in dict (extreme case)

/*
int firstSmaller(const char *targetPath, const char *dictPath)
{
	struct stat targetBuff;
	struct stat dictBuff;

	if (stat(targetPath, &targetBuff) == -1 || stat(dictPath, &dictBuff) == -1)
		errx(EXIT_FAILURE, "Could not stat file");

	return (targetBuff.st_size < dictBuff.st_size) ;

}
*/
int NUM_THREADS = 8;

int is_same(char *target, char *hash, unsigned char len, unsigned char hashLen) //len is the max char we want to check. close to zero => false positives
{
	if (len > hashLen || len == 0)
		errx(EXIT_FAILURE, "Invalid length !\n");
	for (unsigned char i = 0; i < len; i++)
		if (target[i] != hash[i])
			return 0;

	return 1;
}

void hash_and_compare(struct DData targets, struct DData dico, size_t buffLen, void (*hash_func)(char *, char *), unsigned char maxCheck, unsigned char hashLen, char *result)
{
	off_t tLen = targets.St.st_size;
	off_t dLen = dico.St.st_size;
	char *tMap = targets.map;
	char *dMap = dico.map;
	size_t nbTargets = tLen / (hashLen + 1); // + \n

	#pragma omp parallel num_threads(NUM_THREADS)
	{
		int tid = omp_get_thread_num();
		off_t chunk = dLen / NUM_THREADS;
		char *toHash = malloc(buffLen);
		char *hashed = malloc(hashLen + 1); //length of an md5 hash is 32B
		hashed[hashLen] = 0; // we use strlen
		off_t prev = tid * chunk; //offset of the previous line in dico
		off_t end = (tid + 1) * chunk; //we stop at the begining of the next thread
		off_t j = prev;

		printf("Thread %d started working from %ld to %ld\n", omp_get_thread_num(), j, end);

		while (j < dLen && j < end && nbTargets > 0)
		{
			for (j = prev; j < dLen && dMap[j] != '\n'; j++)
			{
				toHash[j-prev] = dMap[j];
			}

			toHash[j-prev] = 0; //we use strlen
			prev = j + 1; //We skip the '\n'
			hash_func(toHash, hashed);

			for (off_t k = 0; k < tLen && nbTargets > 0; k+=hashLen)
			{
				if (is_same(tMap + k, hashed, maxCheck, hashLen))
				{
					#pragma omp critical
					{
						size_t len = strlen(result);
						size_t i = len;
						size_t max = strlen(toHash);
						for (; i < hashLen + len; i++)
							result[i] = hashed[i-len];
						result[i] = ':';
						len+=hashLen+1;
						max+=len;
						i++;
						for (; i < max; i++)
							result[i] = toHash[i-len];
						result[i] = '\n';
						printf("%s:%s\n", hashed, toHash);
						nbTargets--;
					}
				}
				k++; //to skip the '\n'
			}
		}
		printf("Thread %d finished working\n", omp_get_thread_num());
		free(toHash);
		free(hashed);
	}
}


void get_targets(const char *targetPath, struct DData *data)
{
	struct stat targetSt;
	if (stat(targetPath, &targetSt) == -1)
		errx(EXIT_FAILURE, "stat()");

	FILE *targetsFd = fopen(targetPath, "rb");

	char *mTargets = malloc(targetSt.st_size + 1);
	if (targetsFd == NULL)
		errx(EXIT_FAILURE, "File not found");

	fread(mTargets, 1, targetSt.st_size, targetsFd);

	data->St = targetSt;
	data->map = mTargets;
	fclose(targetsFd);
}

struct DData get_data(const char *path)
{
	struct DData data;
	get_targets(path, &data);
	return data;
}

char *dict_attack(const char *targetPath, const char *dictPath, struct BData infos)//, int sorted)
{
	printf("Loading hashes...\n");

	struct DData targets = get_data(targetPath);

	printf("Loading dictionary...\n");

	struct DData dico = get_data(dictPath);

	printf("hashing dictionary and comparing entries...\n");

	char *result = calloc(1, targets.St.st_size*2);
	hash_and_compare(targets, dico, 4096, infos.hash_func, infos.hashLen, infos.hashLen, result);

	free(targets.map);
	free(dico.map);
	return result;
}
