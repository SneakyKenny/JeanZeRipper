#include <stdio.h>
#include <omp.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
//#include "htab/htab.h"
#include "../purple/hash.h"
#include <sys/mman.h>



//TODO : Function to choose hash function from integrer
//
//TODO : Function which puts targets in hash table if
//		 there is more target than words in dict (extreme case)

int firstSmaller(const char *targetPath, const char *dictPath)
{
	struct stat targetBuff;
	struct stat dictBuff;

	if (stat(targetPath, &targetBuff) == -1 || stat(dictPath, &dictBuff) == -1)
		errx(EXIT_FAILURE, "Could not stat file");

	return (targetBuff.st_size < dictBuff.st_size) ;

}

/* Returns a hashtable containing all dictionary hashes with value
   Puts the number of hashes in length */
char *get_targets(const char *targetPath)
{
	struct stat targetSt;
	if (stat(targetPath, &targetSt) == -1)
		errx(EXIT_FAILURE, "stat()");

	int targetsFd = open(targetPath, O_RDONLY);

	char *mTargets;
	//size_t len=0;
	//ssize_t temp;
	//struct htab *table = htab_new();


	if (targetsFd == -1)
		errx(EXIT_FAILURE, "File not found");

	mTargets = mmap(NULL, targetSt.st_size, PROT_READ, MAP_SHARED, targetsFd, 0);

	if (mTargets == MAP_FAILED)
		errx(EXIT_FAILURE, "Could not map file to memory");


	close(targetsFd);

	return mTargets;
}

void dict_attack(const char *targetPath, const char *dictPath)
{
	printf("[+] Loading hashes\n");

	size_t dicoLen = 0;
	//int lessTargets = firstSmaller(targetPath, dictPath);
	char *mTargets = get_targets(targetPath);

	if (mTargets == NULL)
		errx(EXIT_FAILURE, "Could not load hashes, check your targets file");

	//free(mTargets);
}
