#start Makefile

CC=gcc -fsanitize=address

CPPFLAGS=
CFLAGS= -Wall -Wextra -Werror -std=c99 -lssl -lcrypto

LDFLAGS=
LDLIBS=

SRC= md5.c

DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

all: ${PRG}

-include ${DEP}

clean:
	rm -rf *.o
	rm -rf ${DEP}
	rm -rf ${PRG}

#end Makefile
