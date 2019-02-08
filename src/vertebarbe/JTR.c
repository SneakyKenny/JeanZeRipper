#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "dictionaries.h"

int print_help()
{
	char help_buffer[]="Usage: ./JTR [mode] [hashfile] [dictionary] [para]\n";
	if (write(STDOUT_FILENO, help_buffer, strlen(help_buffer))==-1)
		exit(1);
	exit(0);
}

int main (int argc, char **argv)
{
	if (argc==1)
		print_help();

	if (strcmp(argv[1], "dict")==0)
	{
		/*if (argv[4]=="para")
			printf("Result from dictionary (OpenMP): %s\n", dict_attack_omp(argv[2], argv[3]));

		else*/
		printf("Result from dictionary : %s\n", dict_attack(argv[2], argv[3]));
	}

	//print_help();
	return 0;
}
