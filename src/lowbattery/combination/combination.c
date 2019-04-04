#include "sort.h"

#define BUF_SIZE 50

// TEST

void swap(char *x, char *y, size_t n)
{
    char tmp;
    for (size_t i = 0; i < n; i++)
    {
        tmp = *(x + i);
        *(x + i) = *(y + i);
        *(y + i) = tmp;
    }
}

void permute(struct stab *st2, char *mdp, size_t length, size_t n, int* size2)
{
    size_t i;

    for(size_t j = 0; j < length/n; j++)
    {
        for (i = 1; i < length/n; i++)
        {
            swap((mdp), (mdp + (i * n)), n);
            printf("%s\n", mdp);
            //printf("%ld\n", length);
            stab_insert(st2, mdp, length);
            size2[length] += 1;
        }
        //printf("Here we go again!: %s\n", mdp);
    }
}

void all_c(struct stab *st, struct stab *st2, size_t max, int *size,
        int *size2, int words)
{
    size_t i, j, h, len_mdp;// variables useful for loops
    int c;

    // test:
    // stab_print(st);

    // Part 1: test all the mdp with the same length of what we want
    struct pair *tmp = stab_get(st, max);
    struct pair *tmp2;
    while(tmp != NULL)
    {
        printf("%s\n", tmp->mdp);
        tmp = tmp->next;
    }
    //test:
    //stab_print(st);

    c = 0;
    j = 0;
    char cat[BUF_SIZE];
    size_t mid = max / 2;
    // Part 2: allow the swap of all the mdp
    // with a length equals to the half of what we want
    char *s1, *s2;
    if (max % 2 == 0)
    {
        // test:
        //printf("I'm even!\n");
        while(c != size[mid])
        {
            memset(cat, '\0', BUF_SIZE);
            tmp = stab_get(st, mid);
            tmp = pair_next(tmp, c);
            s1 = tmp->mdp;
            while(tmp->next != NULL)
            {
                tmp = tmp->next;
                s2 = tmp->mdp;
                printf("%s%s\n", s1, s2);
                printf("%s%s\n", s2, s1);
                memset(cat, '\0', BUF_SIZE);
            }
            c++;
        }
    }
    else// if the length we want is not even, then we just have to find all
    // the combination between its half - 0,5 and its half + 0,5
    {
        // test:
        //printf("I'm not even (odd)!\n");
        for(tmp = stab_get(st, mid); tmp != NULL; tmp = tmp->next)
        {
            if(!size[mid + 1])
                break;
            memset(cat, '\0',BUF_SIZE);
            s1 = tmp->mdp;
            for(tmp2 = stab_get(st, mid + 1); tmp2 != NULL; tmp2 = tmp2->next)
            {
                s2 = tmp2->mdp;
                strcat(cat, s1);
                strcat(cat, s2);
                stab_insert(st2, cat, max);
                printf("%s\n", cat);
                memset(cat, '\0', max);
                strcat(cat, s2);
                strcat(cat, s1);
                stab_insert(st2, cat, max);
                printf("%s\n", cat);
                memset(cat, '\0', BUF_SIZE);
                size2[max] += 2;
            }
        }
    }

    size_t div;
    // Part 3: here, things begin to be a little more complicated!
    // We will test if we can combine all word of same length to have the same
    // as ours!
    mid = max / 2;

    for (j = 1; j < mid; j++)// let's go for multiplication "combination"
    {
        memset(cat, '\0', BUF_SIZE);
        div = max / j;
        if (max % j)
            continue;
        // if we have enought password to combine for our max length!
        if (size[j] == (int)div)
        {
            tmp = stab_get(st, j);//first mdp with a length of j
            //test:
            //printf("fisrt mdp: %s\r\n", tmp->mdp);
            tmp2 = pair_next(tmp, size[j] - 1);//last mdp
            //test:
            //printf("last mdp: %s\r\n", tmp2->mdp);
            len_mdp = 0;

            while (tmp != tmp2)
            {
                if (len_mdp == 0)
                {
                    s1 = tmp->mdp;
                    strcat(cat, s1);
                    len_mdp += j;
                }
                tmp = tmp->next;
                s2 = tmp->mdp;
                strcat(cat, s2);
                //test: printf("cat mult1: %s\n", cat);
                len_mdp += j;
                if (len_mdp == max)
                {
                    len_mdp = 0;
                    //printf("cat multi: %s, size: %ld\n", cat, max);
                    permute(st2, cat, max, j, size2);// here come our magic ;)
                    memset(cat, '\0', BUF_SIZE);// reset
                }
            }
        }
        // if the number of a same length pasword is higher than the
        // entire divisor of our max length, then we can make lots of
        // combinations...
        else if (size[j] > (int)div)
        {
            for (h = 0; h < (size_t)size[j]; h++)
            {
                tmp = stab_get(st, j);//first mdp with a size of j
                c = 0;
                tmp2 = pair_next(tmp, size[j] - 1);//last mdp
                len_mdp = 0;
                while (tmp != tmp2 && tmp->next != NULL)
                {
                    // the three conditions below are a NEED to manage
                    // all the combinations possible
                    if (!len_mdp)
                    {
                        tmp = stab_get(st, j);
                        tmp = pair_next(tmp, h);
                        s1 = tmp->mdp;
                        memset(cat, '\0', BUF_SIZE);
                        strcat(cat, s1);
                        len_mdp += j;
                        tmp = pair_next(tmp, c + 1);
                    }
                    else
                        tmp = tmp->next;

                    if (tmp == NULL)
                    {
                        memset(cat, '\0', BUF_SIZE);
                        break;
                    }

                    s2 = tmp->mdp;
                    //printf("s2: %s for size j: %ld \n", s2, j);
                    strcat(cat, s2);
                    len_mdp += j;

                    if (len_mdp == max)
                    {
                        len_mdp = 0;
                        //printf("cat multi2: %s, size: %ld\n", cat, max);
                        permute(st2, cat, max, j, size2);//Touch of magic
                        memset(cat, '\0', BUF_SIZE);
                        c++;// Number of combinations we already have
                        break;
                    }
                }
            }
        }
    }

    //test:
    // printf("count: %ld\n", count);
    // stab_print(st);;

    // Part 4: the final step! So the code behind managed all the combination
    // between sums of different length, which have a total size of max
    // test:
    //printf("Last step!\n");
    char *s3;
    memset(cat, '\0', BUF_SIZE);
    int even = (max % 2 == 0);
    if (even)
        mid = max / 2;
    else
        mid = max / 2 + 1;

    for (i = max - 1; i > 0; i--)
    {
        //printf("Hello\n");
        if (i == mid)
            break;
        memset(cat, '\0', BUF_SIZE);
        //printf("The problem came after the %ld loops\n", i);
        for(tmp = stab_get(st, i); tmp != NULL; tmp = tmp->next)
        {
            s1 = tmp->mdp;
            h = max - i;

            if (size[h])
            {
                for(tmp2 = stab_get(st, h); tmp2 != NULL; tmp2 = tmp2->next)
                {
                    s2 = tmp2->mdp;
                    strcat(cat, s1);
                    strcat(cat, s2);
                    printf("%s\n", cat);
                    stab_insert(st2, cat, max);
                    memset(cat, '\0', BUF_SIZE);
                    strcat(cat, s2);
                    strcat(cat, s1);
                    printf("%s\n", cat);
                    stab_insert(st2, cat, max);
                    size2[max] += 2;
                    memset(cat, '\0', BUF_SIZE);
                }
            }
            if (size2[h])
            {   for(tmp2 = stab_get(st2, h); tmp2 != NULL; tmp2 = tmp2->next)
                {
                    s2 = tmp2->mdp;
                    strcat(cat, s1);
                    strcat(cat, s2);
                    stab_insert(st2, cat, max);
                    printf("%s\n", cat);
                    memset(cat, '\0', BUF_SIZE);
                    strcat(cat, s2);
                    strcat(cat, s1);
                    stab_insert(st2, cat, max);
                    printf("%s\n", cat);
                    memset(cat, '\0', BUF_SIZE);
                    size2[max] += 2;
                }
                if (words < 13)
                {
                    for (j = 1; j < h; j++)
                    {
                        for (len_mdp = 0; len_mdp < h; len_mdp++)
                        {
                            if (j + len_mdp == h)
                            {
                                tmp = stab_get(st, j);
                                tmp2 = stab_get(st, len_mdp);
                                if (tmp == NULL || tmp2 == NULL)
                                    break;
                                s2 = tmp->mdp;
                                s3 = tmp2->mdp;
                                printf("%s%s%s\n", s2, s1, s3);
                                printf("%s%s%s\n", s3, s1, s2);
                                len_mdp = max;
                                break;
                            }
                        }
                        if (len_mdp == max)
                            break;
                    }
                }
            }
           //stab_print(st);
        }
    }
}
