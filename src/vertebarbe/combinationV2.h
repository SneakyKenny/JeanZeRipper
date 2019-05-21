//
// Created by macos on 20/05/19.
//

#ifndef COMBINATION_COMBINATIONV2_H
#define COMBINATION_COMBINATIONV2_H

#include <stdio.h>

struct vector{
    size_t capacity;
    size_t size;
    char **data;
};

struct vector *CreateVec(FILE *fp);
void saveCombinations(const struct vector *vec, size_t max_len, ssize_t prevIndex, const char *str, FILE *fp);
void freeVector(struct vector *vec);

#endif //COMBINATION_COMBINATIONV2_H
