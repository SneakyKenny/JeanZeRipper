# ifndef MD5_H
# define MD5_H

# include <stdio.h>
# include <string.h>
# include <err.h>

# include <openssl/conf.h>
# include <openssl/evp.h>
# include <openssl/err.h>
# include <openssl/md5.h>

char *make_md5(char *s);

# endif
