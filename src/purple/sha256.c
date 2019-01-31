# include "hash.h"

static
void sha256_hash_from_string(char *s, char *hash)
{
	int i;
	char unsigned sha256[SHA256_DIGEST_LENGTH] = {0};

	SHA256((const unsigned char *)s, strlen(s), sha256);

	for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
		sprintf(hash + 2 * i, "%02x", sha256[i]);
}

char *make_sha256(char *s)
{
	char *sha256_hash = malloc(sizeof(char) * 64);
	
	sha256_hash_from_string(s, sha256_hash);

	return sha256_hash;
}
