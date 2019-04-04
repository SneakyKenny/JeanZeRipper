#include "sort.h"
#include "combination.h"

#define BUF_SIZE 50


// TEST

int main (int argc, char **argv)
{
    if (argc < 3)
        err(EXIT_FAILURE, "Check the path or the password's length!\n");

    size_t max = (size_t)atoi(argv[1]);
    FILE *fp;// the file we'll read (its content = the most used passwords)
    int c;// useful variable
    char buffer[BUF_SIZE];// string in which we'll store temporally each line
    memset(buffer, '\0', BUF_SIZE);// initialize our string to null byte
    char *mdp;// string in which we'll store temporally a password
    size_t len_mdp = 0;// size of each password we'll find in the file fp
    size_t count = 0;

    fp = fopen(argv[2], "r");

    if (fp == NULL)// if we can't open the file :(
        err(EXIT_FAILURE, "Error in opening file");

    if (max < 1) // all the password have at least 1 character
        err(EXIT_FAILURE, "The length size is too short.\n");

    struct stab *st = stab_new(max + 1);// we create our storage
    struct stab *st2 = stab_new(max + 1);
    // for a better comprehension -> check the structure in 'sort.h'!
    int *size = calloc(sizeof(size_t), max); // create a size array
    int *size2 = calloc(sizeof(size_t), max);
    // the size array allow us to know very easily and quickly how many
    // password we have stored of EACH length!
    int words = 0;

    while(1)// infinite loop
    {
        c = fgetc(fp);// we got ONE character stored in c for now

        if (feof(fp))// if we have read entirely our file fp, we can leave
            break;

        if (c == '\n')// REMINDER: each line has one password
        {
            mdp = buffer;// collect the password we have for the moment
            // is mdp useful for us ? its length must be equal to what we want
            // or less than that (because we can sum it!)
            if (len_mdp <= max)
            {
                stab_insert(st, mdp, len_mdp);// store mdp
                //printf("mdp stored: %s with size %ld\n", mdp, len_mdp);
                size[len_mdp] += 1;// add one of this mdp length in size
                count += len_mdp;
                words++;
            }
            memset(buffer, '\0', BUF_SIZE);
            len_mdp = 0;
        }
        else
        {
            buffer[len_mdp] = c;
            len_mdp++;
        }
    }

    if (max > count)
        max = count;

    count  = 1;
    while (count <= max)
    {
        //printf("here we go with this size: %ld\n", count);
        all_c(st, st2, count, size, size2, words);
        count++;
    }

    // test:$
    //stab_print(st);
    stab_free(st);
    stab_free(st2);
    free(size);
    free(size2);
    fclose(fp);

    return 0;
}
