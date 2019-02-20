#include "brute_rec.h"
#include <omp.h>

static
void bruteImpl(char* str, int index, int maxDepth, struct BData infos)
{
    for (int i = 0; i < alphabetSize; ++i)
    {
        str[index] = alphabet[i];

        if (index == maxDepth - 1)
		{
			infos.hash_func(str, infos.hashbuf);
			for (off_t k = 0; k < infos.targets.St.st_size && infos.nbTargets > 0; k+=infos.hashLen)
			{
				if (is_same(infos.targets.map + k, infos.hashbuf, infos.maxCheck, infos.hashLen))
				{
					printf("%s:%s\n", infos.hashbuf, str);
					infos.nbTargets--;
				}
				k++;
			}
		}
        else
		{
			if(infos.nbTargets > 0)
				bruteImpl(str, index + 1, maxDepth, infos);
		}
    }
}

void bruteSequential(int maxLen, struct BData infos)
{

	int chunk = maxLen / 4;
	#pragma omp parallel num_threads(4)
	{
		int tid = omp_get_thread_num();
		int lim = (tid + 1) * chunk;
		char *buf = calloc(1, maxLen + 1);
		char *hashbuf = calloc(1, infos.hashLen + 1);
		infos.hashbuf = hashbuf;

    	for (int i = 1 + tid * chunk; i <= lim && i <= maxLen; ++i)
    	{
    		memset(buf, 0, maxLen + 1);
    		bruteImpl(buf, 0, i, infos);
    	}

    	free(buf);
		free(hashbuf);
	}
}

void brut_attack(const char *targetPath, int maxLen, struct BData infos)
{
	printf("Loading hashes...\n");

	struct DData targets = get_data(targetPath);
	infos.targets = targets;
	infos.nbTargets = targets.St.st_size / (infos.hashLen + 1);
	bruteSequential(maxLen, infos);
}

