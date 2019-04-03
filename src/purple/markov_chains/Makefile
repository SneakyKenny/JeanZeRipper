CC=gcc
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99 -g
LDFLAGS=
LDLIBS=

SRC= main.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

-include ${DEP}

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main
