#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "../purple/hashing/hash.h"

#ifndef DICT_ATTACK_H
#define DICT_ATTACK_H
struct DData
{
        struct stat St;
        char *map;
};

struct BData
{
        char *hashbuf;
        void (*hash_func)(char*, char*);
        char *(*func_make_hash) (char *);
        unsigned char maxCheck;
        unsigned char hashLen;
        size_t nbTargets;
        struct DData targets;
};

struct DData get_data(const char *path);
int is_same(char *target, char *hash, unsigned char len, unsigned char hashLen);
void dict_attack(const char *targetPath, const char *dictPath, struct BData infos);

#endif
