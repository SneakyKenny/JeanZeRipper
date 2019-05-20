# include "../../vertebarbe/dictionaries.h"

# include "mask.h"

int main (int argc, char **argv)
{
    if (argc != 4)
        errx(1, "usage: %s [%s] [%s] [%s]\n%s\n%s\n%s",
        argv[0],
        "pattern: str",
        "file_path: str",
        "hash type",
        "pattern: The pattern to generate from.",
        "file_path: The file to try crack passwords from.",
        "hash type: the type of hash function to use."
    );

    char *pattern = argv[1];

    char *file_path = argv[2];

    struct BData infos;
    char *hash_type = argv[3];

    if (strcmp(hash_type, "sha1") == 0)
    {
        infos.func_make_hash = make_sha1;
        infos.hashLen = 40;
    } else if (strcmp(hash_type, "sha256") == 0)
    {
        infos.func_make_hash = make_sha256;
        infos.hashLen = 64;
    } else if (strcmp(hash_type, "md5") == 0)
    {
        infos.func_make_hash = make_md5;
        infos.hashLen = 32;
    } else
    {
        errx(1, "Supported hash functions are sha1, sha256 and md5.");
    }
    infos.maxCheck = infos.hashLen;

    struct DData file_data = get_data(file_path);

    int found = 0;
    char *pass = process(pattern, &found, file_data.map, file_data.St.st_size, infos);

    if (found)
        printf("found: %s\n", pass);

    free(file_data.map);
    free(pass);
}
