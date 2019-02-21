# include "hash.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		errx(1, "Usage: %s str", argv[0]);

	char *src = argv[1];
	char *md5 = make_md5(src);
	char *sha1 = make_sha1(src);
	char *sha256 = make_sha256(src);

	printf("Original string: %s\nmd5: %s\nsha1: %s\nsha256: %s\n", src, md5, sha1, sha256);

	free(md5);
	free(sha1);
	free(sha256);
}
