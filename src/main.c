#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
typedef struct entry
{
    char *key;
    char *value;
} entry_t;

typedef struct hashmap
{
    int size;
    entry_t **buckets;
} hashmap_t;

hashmap_t *create_hashmap(int size)
{
    hashmap_t *hm = (hashmap_t *)malloc(sizeof(hashmap_t));
    hm->size = size;
    hm->buckets = (entry_t **)malloc(hm->size * sizeof(entry_t));
    return hm;
}

void delete_hashmap(hashmap_t *hm)
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

int hashmap_insert(hashmap_t *hm, char *key, char *value)
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

void print_hashmap(const hashmap_t *hm)
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

int main()
{
    hashmap_t *hm = create_hashmap(3);
    hashmap_insert(hm, "hello", "world");
    print_hashmap(hm);
    delete_hashmap(hm);
    return 0;
}