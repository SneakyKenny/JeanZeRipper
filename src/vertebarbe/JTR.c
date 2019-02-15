#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
	if (argc == 1)
		print_help();

	if (strcmp(argv[1], "dict")==0)
	{
		if (argc == 5)
			dict_attack(argv[2], argv[3], atoi(argv[4]));

		else
			dict_attack(argv[2], argv[3], 32);
	}

	//print_help();
	return 0;
}
