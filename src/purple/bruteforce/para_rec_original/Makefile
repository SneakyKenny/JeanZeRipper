# Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =
LDLIBS =

OBJ = brute_rec.o

all: brute_rec

brute_rec: ${OBJ}

clean:
	${RM} ${OBJ} *.d brute_rec

# END
