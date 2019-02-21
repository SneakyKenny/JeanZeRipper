#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>

static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
//"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//"0123456789";

static const int alphabetSize = sizeof(alphabet) - 1;

int PRINT_RES = 0;

static
void bruteImpl(char* str, int index, int maxDepth)
{
    for (int i = 0; i < alphabetSize; i++)
    {
        str[index] = alphabet[i];

        if (index == maxDepth - 1)
	{
		if (PRINT_RES)
			printf("%s\n", str);
	}
        else bruteImpl(str, index + 1, maxDepth);
    }
}

void bruteSequential(int maxLen)
{
    char* buf = malloc(maxLen + 1);

    for (int i = 1; i <= maxLen; ++i)
    {
        memset(buf, 0, maxLen + 1);
        bruteImpl(buf, 0, i);
    }

    free(buf);
}

int parse_args(int argc, char **argv)
{
	int len = -1;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'p')
				PRINT_RES = 1;
		}
		else
		{
			len = atoi(argv[i]);
		}
	}

	if (len <= 0)
		errx(1, "Please provide a valid positive integer length");

	return len;
}

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		errx(1, "Usage: %s [-p] length\n"
			"	-p: if provided, the program will print the generated sequences.\n"
			"	length: the length of the longest words to be generated."
			, argv[0]);

	int len = parse_args(argc, argv);

	bruteSequential(len);
	return 0;
}
