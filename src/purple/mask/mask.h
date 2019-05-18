# ifndef MASK_H
# define MASK_H

# include <stdio.h>
# include <stdlib.h>
# include <err.h>
# include "../../vertebarbe/dictionaries.h"

char *process(char *pattern, int *found, char *all_passwords, size_t file_size, struct BData infos);

# endif
