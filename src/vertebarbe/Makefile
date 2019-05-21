# Makefile

CFLAGS= -Wall -Wextra -std=c99 -fopenmp
SRC=  dictionaries.c brute_ite.c ../purple/hashing/md5.c ../purple/hashing/sha1.c ../purple/hashing/sha256.c main.c 
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

main: main.o dictionaries.o brute_ite.o ../purple/hashing/md5.o ../purple/hashing/sha1.o ../purple/hashing/sha256.o ../purple/mask/mask.o combinationV2.o
	gcc -Wall -Wextra -std=c99 -O3 $(shell pkg-config --cflags gtk+-3.0) *.o -o main $(shell pkg-config --libs gtk+-3.0) -rdynamic -lcrypto -lssl -fopenmp -rdynamic

main.o: main.c
	gcc -c -g main.c $(shell pkg-config --cflags --libs gtk+-3.0) -rdynamic -fopenmp

dictionaries.o: dictionaries.c
	gcc -c -g dictionaries.c -fopenmp

brute_ite.o: brute_ite.c
	gcc -c brute_ite.c -fopenmp

../purple/hashing/sha1.o: ../purple/hashing/sha1.c
	gcc -c ../purple/hashing/sha1.c

../purple/hashing/sha256.o: ../purple/hashing/sha256.c
	gcc -c ../purple/hashing/sha256.c

../purple/hashing/md5.o: ../purple/hashing/md5.c
	gcc -c ../purple/hashing/md5.c

../purple/mask/mask.o: ../purple/mask/mask.c
	gcc -c ../purple/mask/mask.c

combinationV2: combinationV2.c
	gcc -c combinationV2.c

clean:
	rm -f ${OBJ} ${DEP} *.o main

# END
