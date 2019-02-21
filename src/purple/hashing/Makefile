# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lssl -lcrypto
LDLIBS =

OBJ = md5.o sha1.o sha256.o main.o
DEP = ${OBJ:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} *.d *.o main

-include ${DEP}

# END
