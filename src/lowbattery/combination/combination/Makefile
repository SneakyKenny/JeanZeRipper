# Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 -O2
LDFLAGS =
LDLIBS = -lm

SRC = main.c combination.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ}   # remove object files
	${RM} ${DEP}   # remove dependency files
	${RM} main     # remove main program

-include ${DEP}

# END
