# include <stdio.h>

# include "md5.h"

# include <err.h>

int main (int argc, char **argv)
{
	if (argc != 2)
		errx(1, "Please specify a string to compute.");

	printf("original:  %s\n", argv[1]);
	
	char *enc = make_md5(argv[1]);
	printf("encrypted: %s\n", enc);

	free(enc);

	return 0;
}
