#include <err.h>
#include <string.h>

#include "htab.h"


/*
uint32_t hash(char *key)
{
	uint32_t tot = 0;
	while(*key != 0)
	{
		tot += *(key++);
		tot += tot << 10;
		tot ^= tot >> 6;
	}
	tot += tot << 3;
	tot ^= tot >> 11;
	tot += tot << 15;
	return tot;
}
*/

struct htab *htab_new()
{
	struct htab *h = malloc(sizeof(struct htab));
	if (h == NULL)
		errx(1,"Not enough memory!");
	h->capacity = 4;
	h->size = 0;
	h->data = calloc(4,sizeof(struct pair));
	if(h->data == NULL)
		errx(1,"Not enough memory!");
	return h;
}

void htab_clear(struct htab *ht)
{
	struct pair *t = ht->data;
	for (size_t i = 0; i< ht->capacity; i++)
	{
		struct pair *u = t->next;
		while(u!= NULL)
		{
			struct pair *temp = u;
			u = u->next;
			free(temp);
		}
		t->next = NULL;
		t+=1;
	}
	ht->size = 0;
}

void htab_free(struct htab *ht)
{
	htab_clear(ht);
	free(ht->data);
	free(ht);

}

struct pair *htab_get(struct htab *ht, char *key)
{
	uint32_t range = hash(key) % (ht->capacity);
	struct pair *line = ((ht->data) + range)->next;
	//while(line != NULL && *(line->key) != *key)
	while(line != NULL && strcmp(line->key,key) != 0)
		line = line->next;
	//if *(line->key) == *key
	if (line != NULL && strcmp(line->key,key) == 0)
		return line;
	return NULL;
}

int htab_insert(struct htab *ht, char *key, void *value)
{
	uint32_t hache = hash(key);
	uint32_t range = hache % (ht->capacity);
	struct pair *line = ((ht->data) + range)->next;
	struct pair *sentinelle = (ht->data) + range;
	//while(line != NULL && *(line->key) != *key)
	while(line != NULL && strcmp(line->key , key) != 0)
		line = line->next;
	//if *(line->key) != *key)

	if (line == NULL) //If we must add
	{	
		struct pair *new = calloc(1,sizeof(struct pair));
		new->key = key;
		new->value = value;
		new->next = sentinelle->next;
		new->hkey = hache;
		sentinelle->next = new;
		if(new->next == NULL) //If the element we added is the first in his case
		{
			ht->size += 1;
			if(ht->size * 100/ ht->capacity > 75) //If we must increase the cpcty
			{
				ht->size = 0;
				ht->capacity *= 2;
				struct pair *tab = ht->data;
				ht->data = calloc(ht->capacity,sizeof(struct pair));
				for(size_t i = 0 ; i < ht->capacity /2 ; i++)
				{
					struct pair *salut = (tab + i)->next;
					while (salut != NULL)
					{
						htab_insert(ht,salut->key,salut->value);
						struct pair *castor = salut;
						salut = salut->next;
						free(castor);
					}
				}
				free(tab);
				
			}
		}
		return 1;
	}
	return 0;
}

void htab_remove(struct htab *ht, char *key)
{
	uint32_t range = hash(key) % (ht->capacity);
	struct pair *line = ((ht->data) + range)->next;
	struct pair *papa = ht->data + range;
	struct pair *sentinelle = ht->data + range;
	while(line != NULL && strcmp(line->key,key) != 0)
	{
		papa = line;
		line = line->next;
	}
	if (line != NULL && strcmp(line->key,key) == 0)
	{
		papa->next = line->next;
		free(line);
		if(sentinelle->next == NULL)
			ht->size -= 1;
		
	}

}
