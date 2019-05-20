#include "combination.h"

#define BUF_SIZE 32

void swap(FILE *fp, FILE *results, int nb, size_t wlen, size_t len);
void find_lines(FILE *fp, char *words, size_t wlen, int nb);
void rotate(FILE *results, char *words, size_t wlen, int nb, size_t len);
void reverse(char *words, size_t wlen, int nb);
void add_file(FILE *fp, FILE *results, int *hist, size_t len);
void two_parts(FILE *fp, FILE *results, int *hist, size_t check, size_t i);
void get_word(FILE *fp, char *word, int n, int wlen);
void complete(char *words, char *word1, char *word2, int len1, int len2);

void histogram(FILE *fp, int *hist, size_t len)
{
    /*int count, c, j = 0;
    char *buffer = NULL;
    size_t i = (size_t)BUF_SIZE;
    while((c = fgetc(fp)) != EOF)
    {
        count = getline(&buffer, &i, fp);
        if (count == -1)
            err(EXIT_FAILURE, "Cannot read the line, at hist build.");
        count -= 1;// remove the count of '\n'
        if (count <= (int)len)
            hist[count - 1] += 1;
        else
            break;
        memset(buffer, '\0', i);
        j += 1;
    }
    printf("%i\n", j);
    fseek(fp, 0, SEEK_SET);
*/
    int j = 0;
    size_t i = 0;
    //read line by line
    const size_t line_size = len + 1;
    char* line = malloc(line_size);
    while (fgets(line, line_size, fp) != NULL && fgetc(fp) != EOF)
    {
        i = strlen(line);
        if (i > len)
            break;
        hist[i - 1] += 1;
        j += 1;
    }
    //printf("%d\n", j);
    free(line);
    fseek(fp, 0, SEEK_SET);
}

void print_histo(int *hist, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("length of %ld: %i words \n", i + 1, hist[i]);
    }
}

void mix(FILE *fp, FILE *results, int *hist, size_t len)
{
    size_t mult, i, check;

    for(i = 1; i < len; i++)
    {
        if (len % i == 0)
        {
            mult = len / i;
            if (hist[i - 1] >= (int)mult)
            {
                swap(fp, results, hist[i - 1], i, len);
            }
        }
    }
    for (i = 1; i < len / 2 + (len % 2); i++)
    {
        check = len - i;
        if (hist[check] && hist[i])
        {
            two_parts(fp, results, hist, check, i);
        }
    }
    add_file(fp, results, hist, len);
}

void two_parts(FILE *fp, FILE *results, int *hist, size_t len1, size_t len2)
{
    size_t len = len1 + len2;// len2 should be less than len1
    int i, j;
    char *words = calloc(len, sizeof(char));
    char *word1 = calloc(len1, sizeof(char));
    char *word2 = calloc(len2, sizeof(char));

    if (words == NULL)
        err(EXIT_FAILURE, "Not enough memory :(");

    for (i = 1; i <= hist[len1 - 1]; i++)
    {
        get_word(fp, word1, i, (int)len1);
        //printf("get that: %s\n", word1);
        for (j = 1; j <= hist[len2 - 1]; j++)
        {
            get_word(fp, word2, j, (int)len2);
            complete(words, word1, word2, (int)len1, (int)len2);
            //printf("words: %s\n", words);
            fprintf(results, "%s\n", words);
            complete(words, word2, word1, (int)len2, (int)len1);
            //printf("words: %s\n", words);
            fprintf(results, "%s\n", words);
            word2 = realloc(word2, len2);
        }
        word1 = realloc(word1, len1);
    }
    free(words);
    free(word1);
    free(word2);
}

void complete(char *words, char *word1, char *word2, int len1, int len2)
{
    int i, j, k;
    for (i = 0; i < len1; i++)
        words[i] = word1[i];
    k = i;
    for (j = 0; j < len2; j++, k++)
        words[k] = word2[j];
}

void get_word(FILE *fp, char *word, int n, int wlen)
{
    size_t i = (size_t)BUF_SIZE;
    int count, c = 0;
    char *buffer = NULL;
    fseek(fp, 0, SEEK_SET);

    for(;;)
    {
        count = getline(&buffer, &i, fp);
        if (count == -1)
            err(EXIT_FAILURE, "Cannot read the lines at get words.");
        count -= 1;
        //printf("%s and its len is %i\n", buffer, wlen);
        if (count == (int)wlen && c < n)
        {
            c += 1;
            if (c == n)
            {
                strncpy(word, buffer, wlen);
                break;
            }
        }
        memset(buffer, '\0', i);
    }
}

void add_file(FILE *fp, FILE *results, int *hist, size_t len)
{
    size_t i = (size_t)BUF_SIZE;
    char *buffer = NULL;
    int count, c = 0, nb = hist[len - 1];
    fseek(results, 0, SEEK_SET);

    if (nb > 0)
    {
        for(;;)
        {
            count = getline(&buffer, &i, fp);
            //printf("word: %s\n", buffer);
            if (count == -1)
                err(EXIT_FAILURE, "Cannot read the lines at final adds.");
            count -= 1;
            if (count == (int)len && c < nb)
            {
                c += 1;
                fprintf(results, "%s", buffer);
                if (c == nb)
                    break;
            }
            memset(buffer, '\0', i);
        }
    }
}

void swap(FILE *fp, FILE *results, int nb, size_t wlen, size_t len)
{
    char words[nb * wlen];
    memset(words, '\0', nb * wlen);
    find_lines(fp, words, wlen, nb);
    rotate(results, words, wlen, nb, len);
    reverse(words, wlen, nb);
    rotate(results, words, wlen, nb, len);
}

void find_lines(FILE *fp, char *words, size_t wlen, int nb)
{
    size_t j, i = (size_t)BUF_SIZE;
    char *buffer = NULL;
    int count, k = 0, c = 0;

    for(;;)
    {
        count = getline(&buffer, &i, fp);
        if (count == -1)
            err(EXIT_FAILURE, "Cannot read the lines at find lines.");
        count -= 1;
        if (count == (int)wlen && c < nb)
        {
            c += 1;
            for (j = 0; j < wlen + 1; j++)
            {
                if (buffer[j] == '\n')
                    continue;
                else
                {
                    words[k] = buffer[j];
                    k += 1;
                }
            }
            if (c == nb)
                break;
            continue;
        }
        else
            memset(buffer, '\0', i);
    }

    //printf("all words: %s\n", words);
    fseek(fp, 0, SEEK_SET);
}

void rotate(FILE *results, char *words, size_t wlen, int nb, size_t len)
{
    size_t i, j, h = (size_t)nb * wlen;
    char *word, tmp[h];
    word = calloc(len, sizeof(char));

    for (int k = 0; k <= nb; k++)
    {
        for(j = 0; j < len; j++)
            word[j] = words[j];
        //printf("%s\n", word);
        fprintf(results, "%s\n", word);
        word = realloc(word, len);
        i = 0;
        strcpy(tmp, words);

        for(j = h - wlen; j < h; j++)
        {
            words[i] = tmp[j];
            i += 1;
        }
        j = 0;
        for(i = wlen; i < h; i++)
        {
            words[i] = tmp[j];
            j += 1;
        }
        //printf("%s\n", words);
    }
    free(word);
}

void reverse(char *words, size_t wlen, int nb)
{
    size_t len = (size_t)nb * wlen;
    char tmp[len];
    strcpy(tmp, words);
    for(size_t i = 0; i < len; i++)
        words[i] = tmp[len - i - 1];
}
