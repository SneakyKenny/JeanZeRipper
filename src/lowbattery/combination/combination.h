#ifndef COMB_H
#define COMB_H


void swap(char *x, char *y, size_t n);

void permute(struct stab *st2, char *mdp, size_t length, size_t n, int* size2);

void all_c(struct stab* st, struct stab *st2, size_t max, int *size,
        int *size2, int words);

#endif
