# include <stdio.h>
# include <stdlib.h>

# include <string.h>

# include <err.h>

# define alphabet "abcdefghijkmnopqrstuvwxyz"

void *malloc_wrapper(size_t num_bytes)
{
	void *ret = malloc(num_bytes);

	if (!ret)
		errx(1, "Malloc failed.");
	
	return ret;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		errx(1, "Usage: max number of chars");
	
	int max_len = strtoul(argv[1], NULL, 10);

	if (max_len){}

	int alpha_size = strlen(alphabet);

	char *s = malloc_wrapper(sizeof(char) * alpha_size * 2);

	for (int i = 0; i < alpha_size  * 2; i += 2)
	{
		s[i] = alphabet[i / 2];
		s[i + 1] = '\n';
	}

	printf("Created:\n%s\n", s);

	free(s);

	return 0;
}
