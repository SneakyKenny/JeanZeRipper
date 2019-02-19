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

void dict_attack(const char *targetPath, const char *dictPath, void (*hash_func) (char *, char *), unsigned char maxCheck, unsigned char hashLen);

#endif
