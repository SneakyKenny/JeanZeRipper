# ifndef MD5_H
# define MD5_H

# include <stdio.h>
# include <string.h>
# include <err.h>

# include <openssl/conf.h>
# include <openssl/evp.h>
# include <openssl/err.h>
# include <openssl/sha.h>

char *make_sha1(char *s);

# endif
