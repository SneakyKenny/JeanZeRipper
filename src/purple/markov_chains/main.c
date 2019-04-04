# include <stdio.h>
# include <stdlib.h>

# include <time.h>

# include <fcntl.h>

# include <unistd.h>

# include <err.h>

# define separators     " \n\r"
# define numSep         2
# define TOTAL_STATES   256

typedef struct State
{
    char character;                 // currently represented char
    int numSucc;                    // number of successor this state has
    struct State **nextState;       // list of successors
    int           *nf;              // for each successor in nextState, indicate the number of times this successor has be found
} State;

void *xcalloc(int n)
{
    void *p = calloc(1, n);
    if (!p)
        errx(1, "Calloc failed");
    return p;
}

void *xrealloc(void *p, int n)
{
    p = realloc(p, n);
    if (!p)
        errx(1, "Realloc failed");
    return p;
}

int xread(int fd, char *buf, int n)
{
    int r = read(fd, buf, n);
    if (r < 0)
        errx(1, "Read failed");
    return r;
}

void xwrite(int fd, char *buf, int n)
{
    if (write(fd, buf, n) < 0)
        errx(1, "Write failed");
}

int randint(int n)
{
    if (n - 1 >= RAND_MAX)
        return rand();

    int end = RAND_MAX / n;
    end *= n;
    int r;
    while ((r = rand()) >= end);

    return r % n;
}

State *newState(char c)
{
    State *s = xcalloc(sizeof(struct State));
    s->character = c;

    s->nextState = xcalloc(sizeof(struct State *));
    s->nf = xcalloc(sizeof(int));

    return s;
}

void freeAllStates(State **allStates, int numStates)
{
    for (int i = 0; i < numStates; i++)
    {
        if (allStates[i])
        {
            if (allStates[i]->nf)
                free(allStates[i]->nf);
			if (allStates[i]->nextState)
				free(allStates[i]->nextState);
            free(allStates[i]);
        }
    }
    free(allStates);
}

int isCharFollowingState(State *s, char c, int *ind)
{
    for (int i = 0; i < s->numSucc; i++)
    {
        if (s->nextState[i]->character == c)
        {
            *ind = i;
            return 1;
        }
    }
    return 0;
}

int isSeparator(char c)
{
    for (int i = 0; i < numSep; i++)
        if (c == separators[i])
            return 1;
    return 0;
}

int findState(State **allStates, int numStates, char c)
{
    for (int i = 0; i < numStates; i++)
    {
        if (allStates[i] && allStates[i]->character == c)
        {
            return i;
        }
    }
    return -1;
}

int addState(State **allStates, int numStates, State *s, char c, State **ns)
{
    if (isSeparator(c))
        return -2;

    int ind = findState(allStates, numStates, c);

    int ret = -1;

    if (ind < 0)
    {
        *ns = newState(c);
        allStates[numStates] = *ns;
        numStates++;
        ret = numStates;
    }
    else
    {
        *ns = allStates[ind];
    }

    if (s->numSucc == 0)
    {
        s->nextState[0] = *ns;
        s->nf[0]        = 1;
        s->numSucc      = 1;
    }
    else
    {
        int succInd = 0;
        int isSucc = isCharFollowingState(s, c, &succInd);
        if (isSucc)
        {
            s->nf[succInd]++;
        }
        else
        {
            s->nextState = xrealloc(s->nextState, sizeof(struct State *) * (s->numSucc + 1));
            s->nf = xrealloc(s->nf, sizeof(int) * (s->numSucc + 1));

            s->nextState[s->numSucc] = *ns;
            s->nf[s->numSucc]        = 1;
            s->numSucc++;
        }
    }

    return ret;
}

char *createAppearenceList(State *s, int *total)
{
    int n = 0;
    for (int i = 0; i < s->numSucc; i++)
    {
        n += s->nf[i];
    }
    char *l = xcalloc(sizeof(char) * (n + 1));
    int tot = 0;
    for (int i = 0; i < s->numSucc; i++)
    {
        for (int j = 0; j < s->nf[i]; j++)
        {
            l[tot + j] = s->nextState[i]->character;
        }
        tot += s->nf[i];
    }

    l[n] = 0;
    *total = n;

    return l;
}

char *generateWord(State **allStates, int numStates, int maxLen)
{
    char *word = xcalloc(sizeof(char) * (maxLen + 1));
    State *s = allStates[0];
    for (int i = 0; i < maxLen; i++)
    {
        int numChars;
        char *chars = createAppearenceList(s, &numChars);
        if (numChars == 0)
        {
            //printf("wtf ??\n");
        }
        else
        {
            int rngbois = randint(numChars);
            char c = chars[rngbois];
            word[i] = c;
            int ind = findState(allStates, numStates, c);
            s = allStates[ind];
        }
        free(chars);
    }
    word[maxLen] = 0;
    return word;
}

int openFileToRead(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        errx(1, "Open failed");
    return fd;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    int fd, maxLen = 5;
    switch (argc)
    {
        case 2: fd = openFileToRead(argv[1]); break;
        case 3: fd = openFileToRead(argv[1]); maxLen = atoi(argv[2]); break;
        default: errx(1, "Usage: %s [file] [maxLen (optionnal)]", argv[0]); break;
    }

    int r;
    char buf[1];

    char c;
    r = xread(fd, &c, 1);
    if (r == 0)
        errx(1, "given an empty file");

    State *s = newState(c);
    State *origin = s;

    State **allStates = xcalloc(sizeof(struct State *) * TOTAL_STATES);
    allStates[0] = origin;
    int numStates = 1;

    while ((r = xread(fd, buf, 1)) != 0)
    {
        State *new = NULL;
        int added = addState(allStates, numStates, s, buf[0], &new);
        if (added == -1)
        {
            s = new;
        }
        else if (added >= 0)
        {
            numStates = added;
            s = new;
        }
    }

    char *word = generateWord(allStates, numStates, maxLen);
    printf("%s\n", word);

    free(word);
    freeAllStates(allStates, numStates);

    return 0;
}
