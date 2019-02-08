# Makefile

CC=gcc -fsanitize=address
CPPFLAGS=
CFLAGS= -Wall -Wextra -g3
LDFLAGS=
LDLIBS=

SRC=  dictionaries.c JTR.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: JTR

-include ${DEP}

JTR: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} JTR

# END
