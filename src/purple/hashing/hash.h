# include <stdio.h>
# include <string.h>
# include <err.h>

# include "openssl/conf.h"
# include "openssl/evp.h"
# include "openssl/err.h"

# include "openssl/md5.h"
# include "openssl/sha.h"

# ifndef HASH_H
# define HASH_H

void md5_hash_from_string(char *s, char *hash);
void sha1_hash_from_string(char *s, char *hash);
void sha256_hash_from_string(char *s, char *hash);
char *make_md5(char *src);
char *make_sha1(char *src);
char *make_sha256(char *src);

# endif
