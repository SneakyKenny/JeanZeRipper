# Makefile

CC = gcc
CFLAGS = -I -Wall -Wextra -lssl -lcrypto -fopenmp -g
DEPS = ../hashing/*.h ../../vertebarbe/dictionaries.h
OBJ = main.o ../hashing/md5.o ../hashing/sha1.o ../hashing/sha256.o ../../vertebarbe/dictionaries.o
NAME = markov

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(NAME) $^ $(CFLAGS)

clean:
	${RM} ${OBJ} *.o *.d ../../vertebarbe/*.d ../hashing/*.d markov

# END
