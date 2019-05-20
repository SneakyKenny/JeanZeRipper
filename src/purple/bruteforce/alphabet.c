#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

const char *alphabet = "abcdefghijklmnopqrstuvwxyz0123456789";

static void generate(int maxlen)
{
    int alphaLen = strlen(alphabet);
    char *buffer = malloc((maxlen + 1) * alphaLen * alphaLen);
    int *letters = malloc(maxlen * sizeof(int));

    if (!buffer || !letters)
        errx(1, "Malloc failed");

    int j = 0;
    int buflen = 2 * alphaLen;
    for (int i = 0; i < alphaLen; i++)
    {
        buffer[j++] = alphabet[i];
        buffer[j++] = '\n';
    }

    write(STDOUT_FILENO, buffer, buflen);

    for (int len = 2; len <= maxlen; len++)
    {
        int stride = len + 1;
        int bufLen = stride * alphaLen * alphaLen;

        memset(buffer, alphabet[0], bufLen);

        {
            int let0 = 0;
            int let1 = 0;

	    for (int i = len - 2; i < bufLen; i += stride)
            {
                buffer[i] = alphabet[let0];
                buffer[i+1] = alphabet[let1++];
                buffer[i+2] = ' ';
                if (let1 == alphaLen)
                {
                    let1 = 0;
                    let0++;
                    if (let0 == alphaLen)
                        let0 = 0;
                }
            }
        }

        write(STDOUT_FILENO, buffer, bufLen);

        if (len == 2)
            continue;

        for (int i = 0; i < len; i++)
            letters[i] = 0;

        int i = len - 3;
        do
        {
            letters[i]++;

            if (letters[i] >= alphaLen)
                letters[i] = 0;

            char c = alphabet[letters[i]];
            for (int j = i; j < bufLen; j += stride)
                buffer[j] = c;

            if (letters[i] != 0)
            {
                write(STDOUT_FILENO, buffer, bufLen);
                i = len - 3;
                continue;
            }

            i--;
            if (i < 0)
                break;
        } while(1);
    }

    free(letters);
    free(buffer);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        errx(1, "Usage: %s length", argv[0]);

    generate(atoi(argv[1]));
    return 0;
}
