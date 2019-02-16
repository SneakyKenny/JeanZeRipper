#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dictionaries.h"
#include "../purple/hashing/hash.h"

int print_help()
{
	char help_buffer[]="Usage: ./JTR [mode] [hashfile] [dictionary] [hash_function] [maxcheck]\n";
	if (write(STDOUT_FILENO, help_buffer, strlen(help_buffer))==-1)
		exit(1);
	exit(0);
}

int main (int argc, char **argv)
{
	if (argc < 5)
		print_help();

	if (strcmp(argv[1], "dict")==0)
	{
		if (argc == 6)
		{
			if (strcmp(argv[4], "sha1") == 0)
			{
				dict_attack(argv[2], argv[3], sha1_hash_from_string, atoi(argv[5]), 40);
			}

			if (strcmp(argv[4], "sha256") == 0)
			{
				dict_attack(argv[2], argv[3], sha256_hash_from_string, atoi(argv[5]), 64);
			}

			if (strcmp(argv[4], "md5") == 0)
			{
				dict_attack(argv[2], argv[3], md5_hash_from_string, atoi(argv[5]), 32);
			}

		}
		else
			print_help();
	}

	//print_help();
	return 0;
}
