# Makefile

CC=gcc -fsanitize=address -g3
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99 -fopenmp
LDFLAGS=
LDLIBS= -lcrypto -lssl -fopenmp

SRC=  dictionaries.c JTR.c ../purple/hashing/md5.c ../purple/hashing/sha1.c ../purple/hashing/sha256.c ../purple/bruteforce/para_rec/brute_rec.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: JTR

-include ${DEP}

JTR: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} JTR

# END
