# include "hash.h"

//static
void md5_hash_from_string(char *s, char *hash)
{
	int i;
	char unsigned md5[MD5_DIGEST_LENGTH] = {0};

	MD5((const unsigned char *)s, strlen(s), md5);

	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
		sprintf(hash + 2 * i, "%02x", md5[i]);
}

char *make_md5(char *s)
{
	char *md5_hash = malloc(sizeof(char) * 32);
	
	md5_hash_from_string(s, md5_hash);

	return md5_hash;
}
