# Makefile

CC = gcc -fsanitize=address -g3
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =
LDLIBS =

OBJ = brute_rec.o main.o

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} *.d main

# END
