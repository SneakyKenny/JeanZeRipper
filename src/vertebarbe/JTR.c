#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dictionaries.h"
#include "../purple/hashing/hash.h"
#include "../purple/bruteforce/para_rec/brute_rec.h"

int print_help()
{
	char help_buffer[]="Usage: ./JTR [dict/brut] [hashfile] [dictionary/maxlen] [hash_function] [maxcheck]\n";
	if (write(STDOUT_FILENO, help_buffer, strlen(help_buffer))==-1)
		exit(1);
	exit(0);
}

int main (int argc, char **argv)
{
	if (argc < 2)
		print_help();
	
	if (argc == 6)
	{
		struct BData infos;
		infos.maxCheck = atoi(argv[5]);

		if (strcmp(argv[4], "sha1") == 0)
		{
			infos.hash_func = sha1_hash_from_string;
			infos.hashLen = 40;

			if(strcmp(argv[1], "dict") == 0)
				dict_attack(argv[2], argv[3], infos);

			if(strcmp(argv[1], "brut") == 0)
				brut_attack(argv[2], atoi(argv[3]), infos);
		}

		if (strcmp(argv[4], "sha256") == 0)
		{
			infos.hash_func = sha256_hash_from_string;
			infos.hashLen = 64;

			if(strcmp(argv[1], "dict") == 0)
				dict_attack(argv[2], argv[3], infos);

			if(strcmp(argv[1], "brut") == 0)
				brut_attack(argv[2], atoi(argv[3]), infos);
		}

		if (strcmp(argv[4], "md5") == 0)
		{
			infos.hash_func = md5_hash_from_string;
			infos.hashLen = 32;

			if(strcmp(argv[1], "dict") == 0)
				dict_attack(argv[2], argv[3], infos);

			if(strcmp(argv[1], "brut") == 0)
				brut_attack(argv[2], atoi(argv[3]), infos);
		}
	else
		print_help();
	}
	return 0;
}
