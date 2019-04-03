#include "sort.h"


struct stab *stab_new(size_t len)
{
    struct stab *st = malloc(sizeof(struct stab));
    if(st == NULL)
        errx(1, "Not enough memory!");
    st->capacity = len;
    st->data = calloc(sizeof(struct pair), len);

    return st;
}

void stab_clear(struct stab *st)
{
    struct pair *p;
    for(size_t i = 0; i < st->capacity; i++)
    {
        p = st->data[i].next;
        while(p != NULL)
        {
            struct pair *curr = p;
            free(curr->mdp);
            p = p->next;
            free(curr);
        }
        st->data[i].next = NULL;
    }
}

void stab_free(struct stab *st)
{
    stab_clear(st);
    free(st->data);
    st->capacity = 0;
    free(st);
}

struct pair *stab_get(struct stab *st, size_t len)
{
    // len = length of the password we want to get
    if (len > st->capacity)
        return NULL;
    struct pair *p = st->data[len].next;
    return p;
}

void stab_insert(struct stab *st, char *mdp, size_t len)
{
    struct pair *pnew = malloc(sizeof(struct pair));
    char *t = calloc(sizeof(char), len);
    strcpy(t, mdp);
    // to see what it stores each time:
    // printf("mdp: %s\n", t);
    pnew->mdp = t;
    struct pair *cur = st->data[len].next;
    pnew->next = cur;
    st->data[len].next = pnew;
}

int stab_remove(struct stab *st, char *mdp, size_t len)
{
    struct pair *tmp = &(st->data[len]);
    struct pair *cur = tmp->next;
    if (cur == NULL)
        return -1;

    while(cur != NULL && strcmp(cur->mdp, mdp) != 0)
    {
        tmp = cur;
        cur = cur->next;
    }
    if(cur != NULL)
    // remove 'cur' and link previous pair 'tmp' to the next
    {
        tmp->next = cur->next;
        // to see it removes what:
        // printf("str to remove: %s\n", cur->mdp);
        free(cur->mdp);
        free(cur);
    }

    return 0;
}

struct pair *pair_next(struct pair *p, int n)
{
    if (!n)
        return p;

    while (n > 0 && p != NULL)
    {
        //printf("next: %s\n", p->mdp);
        p = p->next;
        n--;
    }
    return p;
}

void stab_print(struct stab *st)
{
    size_t capacity = st->capacity;
    struct pair *tmp;
    int j;
    printf("capacity: %ld", st->capacity);
    for (size_t i = 0; i < capacity; i++)
    {
        j = 1;
        struct pair *cur = st->data[i].next;
        printf("\n   size %ld: \n\n", i);
        for (tmp = cur; tmp != NULL; tmp = tmp->next)
        {
            printf("       %i: %s \n", j, tmp->mdp);
            j++;
        }
    }
}
