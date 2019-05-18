#ifndef COMBI_H
#define COMBI_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <err.h>


void histogram(FILE *fp, int *hist, size_t len);
void print_histo(int *hist, size_t len);
void mix(FILE *fp, FILE *results, int *hist, size_t len);

#endif
