# include <stdio.h>

# include <string.h>

# include <openssl/conf.h>
# include <openssl/evp.h>
# include <openssl/err.h>
# include <openssl/md5.h>

# define TEXT_1 "ThisIsSomeReallyLongTextWithNoSpaces"
# define TEXT_2 "This is another long text but this one has spaces."

void md5_hash_from_string(char *s, char *hash)
{
	int i;
	char unsigned md5[MD5_DIGEST_LENGTH] = {0};

	MD5((const unsigned char *)s, strlen(s), md5);

	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
		sprintf(hash + 2 * i, "%02x", md5[i]);
}

int main(void)
{
	char *s = TEXT_1;
	char md5_hash[2 * MD5_DIGEST_LENGTH + 1] = "";
	md5_hash_from_string(s, md5_hash);
	printf("original: %s\n", s);
	printf("encoded:  %s\n", md5_hash);
	return 0;
}
