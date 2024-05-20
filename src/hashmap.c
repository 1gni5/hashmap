#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hashmap.h"

int hash_str(const char *str)
{
    char const *current = str;
    const char *end = str + strlen(str);
    int hash = 0;
    while (current < end)
    {
        hash += (int)*current;
        current++;
    }
    return hash;
}

hashmap_t *init_hm(int size)
{
    hashmap_t *hm = (hashmap_t *)malloc(sizeof(hashmap_t));
    hm->size = size;
    hm->buckets = (entry_t **)malloc(hm->size * sizeof(entry_t));
    return hm;
}

void clean_hm(hashmap_t *hm)
{

    for (int i = 0; i < hm->size; i++)
    {
        if (hm->buckets[i] != NULL)
        {
            free(hm->buckets[i]);
        }
    }
    free(hm->buckets);
    free(hm);
}

int hm_insert(hashmap_t *hm, char *key, char *value)
{
    const int hash = hash_str(key);
    int index = hash % hm->size;

    // bucket not empty and different value -> collision
    while (hm->buckets[index] != NULL && strcmp(hm->buckets[index]->key, key))
    {
        index = (index + 1) % hm->size;
        if (index == (hash % hm->size))
            return -1;
    }
    hm->buckets[index] = (entry_t *)malloc(sizeof(entry_t));
    hm->buckets[index]->key = key;
    hm->buckets[index]->value = value;

    return 0;
}

char *hm_find(hashmap_t *hm, char *key)
{
    const int hash = hash_str(key);
    int index = hash % hm->size;

    if (hm->buckets[index] == NULL)
    {
        return NULL;
    }

    // bucket not empty and different value -> collision
    while (strcmp(hm->buckets[index]->key, key))
    {
        index = (index + 1) % hm->size;
        if (index == (hash % hm->size))
            return NULL;
    }

    return hm->buckets[index]->value;
}

void print_hm(const hashmap_t *hm)
{
    printf("{");
    for (int i = 0; i < hm->size; i++)
    {
        bool is_last = i == hm->size - 1;
        if (hm->buckets[i] != NULL)
        {
            printf("%s->%s", hm->buckets[i]->key, hm->buckets[i]->value);
        }
        else
        {
            printf(" ");
        }
        if (!is_last)
            printf(",");
    }
    printf("}\n");
}