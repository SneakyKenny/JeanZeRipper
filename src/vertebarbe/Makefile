# Makefile

CC=gcc -fsanitize=address -g3
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99
LDFLAGS=
LDLIBS= -lcrypto -lssl

SRC=  dictionaries.c JTR.c ../purple/hashing/md5.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: JTR

-include ${DEP}

JTR: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} JTR

# END
