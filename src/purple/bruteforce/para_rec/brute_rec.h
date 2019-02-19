#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>

static const char alphabet[] =
"abcdefghijklmnopqrstuvwxyz";
//"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//"0123456789";

static const int alphabetSize = sizeof(alphabet) - 1;

void bruteSequential(int maxLen);
