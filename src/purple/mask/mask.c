# include "mask.h"

static char *lower = "abcdefghijklmnopqrstuvwxyz";
static char *upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static char *decimal = "0123456789";
static char *special = " !-_.";
//" !\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~"; //(hashcat)

// "lamuir27" ../../vertebarbe/data/hashes/rockyou10000_md5.txt "md5"

void *xcalloc(size_t n)
{
    void *p = calloc(n, 1);

    if (!p)
        errx(1, "calloc failed");

    return p;
}

void init_from_str(char *s, size_t *pass_len, size_t *num_pattern)
{
    for (size_t i = 0; s[i]; i++)
    {
        if (s[i] == '%')
        {
            char c = s[i + 1];
            if (c == 0)
                errx(1, "Please provide a pattern that doesn't end with '%%'.");

            if (c != 'l' && c != 'u' && c != 'd' && c != 's')
                errx(1, "undefined pattern: %c", s[i]);

            *num_pattern = *num_pattern + 1;
        }
        else
            *pass_len = *pass_len + 1;
    }
}

void fill_tabs(char *pattern, size_t tot_len, char *password, size_t *pattern_num_to_pass_ind)
{
    size_t ind_in_pass = 0;
    size_t ind_in_pattern = 0;

    for (size_t i = 0; i < tot_len; i++)
    {
        if (pattern[i] == '%')
        {
            pattern_num_to_pass_ind[ind_in_pattern] = i - ind_in_pattern;
            ind_in_pattern++;
        }
        else
        {
            password[ind_in_pass++] = pattern[i];
        }
    }
}

int generate_rec(char *password, size_t pass_len, size_t *pattern_num_to_pass_ind, size_t num_pattern, size_t cur_pass_index, size_t cur_pattern_index, char *all_passwords, size_t file_size, struct BData infos)
{
    // we went all the way down, test if password is correct
    if (cur_pass_index >= pass_len || cur_pattern_index > num_pattern)
    {
        if (all_passwords && file_size) {infos.hashLen*=2;}

        char *hashed_pass = infos.func_make_hash(password);

        for (size_t i = 0; i < file_size; i++)
        {
            if (strncmp(hashed_pass, all_passwords + i, infos.hashLen) == 0)
            {
                free(hashed_pass);
                return 1;
            }
            i += infos.hashLen;
        }

        free(hashed_pass);

        return 0;
    }

    char *charset = NULL;
    if (cur_pass_index == pattern_num_to_pass_ind[cur_pattern_index])
    {
        char c = password[cur_pass_index];
        switch (c)
        {
            case 'l': charset = lower;      break;
            case 'u': charset = upper;      break;
            case 'd': charset = decimal;    break;
            case 's': charset = special;    break;
            default: break; // this should never occur as we already check for it init_from_str
        }

        for (size_t i = 0; charset[i]; i++)
        {
            password[cur_pass_index] = charset[i];
            if (generate_rec(password, pass_len, pattern_num_to_pass_ind, num_pattern, cur_pass_index + 1, cur_pattern_index + 1, all_passwords, file_size, infos))
                return 1;
        }

        password[cur_pass_index] = c; // reset the character to what it used to be for the next tests
    }
    else
    {
        if (generate_rec(password, pass_len, pattern_num_to_pass_ind, num_pattern, cur_pass_index + 1, cur_pattern_index, all_passwords, file_size, infos))
            return 1;
    }

    return 0;
}

int generate(char *password, size_t pass_len, size_t *pattern_num_to_pass_ind, size_t num_pattern, char *all_passwords, size_t file_size, struct BData infos)
{
    return generate_rec(password, pass_len, pattern_num_to_pass_ind, num_pattern, 0, 0, all_passwords, file_size, infos);
}

char *process(char *pattern, int *found, char *all_passwords, size_t file_size, struct BData infos)
{
    size_t pass_len = 0; // length of the password to test (excluding '%')
    size_t num_pattern = 0; // contains the number of '%' founds

    init_from_str(pattern, &pass_len, &num_pattern);

    if (num_pattern == 0)
    {
        // no pattern to test for, just test the given password
        return 0;
    }

    size_t tot_len = pass_len + num_pattern;

    char *password = xcalloc(pass_len + 1);  //this contains the string
                                        // that we'll modify using the different patterns
                                        // and in the end the password, if found

    size_t pattern_num_to_pass_ind[num_pattern];

    fill_tabs(pattern, tot_len, password, pattern_num_to_pass_ind);

    *found = generate(password, pass_len, pattern_num_to_pass_ind, num_pattern, all_passwords, file_size, infos);

    return password;
}
