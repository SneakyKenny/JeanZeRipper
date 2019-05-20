#include <stdio.h>
#include <stdlib.h>
#include "../purple/hashing/hash.h"
#include "dictionaries.h"

#ifndef BRUT_ITE_H
#define BRUT_ITE_H

void concat(char *str1, char *str2);

char *brut_attack(const char *targetPath, int maxLen, struct BData infos, int num_threads, char *charset);

#endif
