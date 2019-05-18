# Makefile

CC = gcc
CFLAGS = -I -Wall -Wextra -g -lssl -lcrypto -fopenmp -g
DEPS = ../hashing/*.h ../../vertebarbe/dictionaries.h mask.h
OBJ = main.o mask.o ../hashing/md5.o ../hashing/sha1.o ../hashing/sha256.o ../../vertebarbe/dictionaries.o
NAME = mask

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(NAME) $^ $(CFLAGS)

clean:
	${RM} ${OBJ} *.o *.d ../../vertebarbe/*.d ../hashing/*.d mask

# END
