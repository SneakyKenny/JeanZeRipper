#ifndef SORT_H
#define SORT_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <err.h>


struct stab{
    size_t capacity;
    struct pair *data;
};


struct pair{
    char *mdp;
    struct pair *next;
};

struct stab *stab_new(size_t len);

void stab_clear(struct stab *st);

void stab_free(struct stab *st);

struct pair *stab_get(struct stab *st, size_t len);

void stab_insert(struct stab *st, char *mdp, size_t len);

int stab_remove(struct stab *st, char *mdp, size_t len);

struct pair *pair_next(struct pair *p, int n);

void stab_print(struct stab *st);

#endif
