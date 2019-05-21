//
// Created by macos on 20/05/19.
//
#define _GNU_SOURCE

#include "combinationV2.h"
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>

#define BUF_SIZE 50

struct vector *CreateVec(FILE *fp)
{
    //Create vector
    struct vector *vec = malloc(sizeof(struct vector));
    vec->capacity = BUF_SIZE;
    vec->size = 0;
    vec->data = malloc(vec->capacity * sizeof(char*));
    if (!vec->data)
        errx(EXIT_FAILURE, "Not enough memory.");

    char *line = NULL;
    size_t size = 0;
    ssize_t len = 0;
    while ((len = getline(&line, &size, fp)) != -1)
    {
        //Check if number of words exceed current buffer
        if (vec->size >= vec->capacity)
        {
            vec->capacity *= 2;
            vec->data = realloc(vec->data, vec->capacity * sizeof(char*));
        }

        //Replace \n at the end with a null byte and add to vector
        line[len-1] = '\0';
        vec->data[vec->size] = line;

        vec->size++;
        line = NULL;
    }

    return vec;
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    if (!result)
        err(EXIT_FAILURE, "Not enough memory.");

    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void saveCombinations(const struct vector *vec, size_t max_len, ssize_t prevIndex, const char *str, FILE *fp)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        if ((ssize_t)i == prevIndex)
            continue;

        char *word = vec->data[i];
        size_t len = strlen(word);

        if (len <= max_len)
        {
            char *newStr = concat(str, word);
            fprintf(fp, "%s\n", newStr);

            saveCombinations(vec, max_len - len, i, newStr, fp);
            free(newStr);
        }
    }
}

void freeVector(struct vector *vec)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        free(vec->data[i]);
    }
    free(vec->data);
    free(vec);
}
