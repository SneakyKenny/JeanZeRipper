#include "combination.h"


int main (int argc, char **argv)
{
    if (argc < 3)
        err(EXIT_FAILURE, "Check the path or the password's length!\n");

    size_t len = (size_t)atoi(argv[1]);
    if (len == 0)
        return 0;
    FILE *fp = fopen(argv[2], "r");
    FILE *results = fopen("results.txt", "w");
    if (!fp)
        err(EXIT_FAILURE, "Cannot open file.");

    int *hist = calloc(len, sizeof(int));
    histogram(fp, hist, len);
    print_histo(hist, len);
    mix(fp, results, hist, len);

    free(hist);
    fclose(fp);
    fclose(results);
}
