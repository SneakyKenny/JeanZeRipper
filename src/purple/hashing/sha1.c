# include "hash.h"

static
void sha1_hash_from_string(char *s, char *hash)
{
	int i;
	char unsigned sha1[SHA_DIGEST_LENGTH] = {0};

	SHA1((const unsigned char *)s, strlen(s), sha1);

	for (i = 0; i < SHA_DIGEST_LENGTH; i++)
		sprintf(hash + 2 * i, "%02x", sha1[i]);
}

char *make_sha1(char *s)
{
	char *sha1_hash = malloc(sizeof(char) * 40);
	
	sha1_hash_from_string(s, sha1_hash);

	return sha1_hash;
}
