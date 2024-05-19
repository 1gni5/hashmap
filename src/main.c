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
typedef struct hashmap
{
    int size;
    char **buckets;
} hashmap_t;

hashmap_t *create_hashmap(int s)
{
    hashmap_t *hm = (hashmap_t *)malloc(sizeof(hashmap_t));
    hm->size = s;
    hm->buckets = (char **)malloc(hm->size * sizeof(hashmap_t));
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

void hashmap_insert(hashmap_t *hm, const char *value)
{
    const int hash = hash_str(value);
    const int index = hash % hm->size;
    hm->buckets[index] = (char *)malloc(strlen(value));
    strcpy(hm->buckets[index], value);
}

void print_hashmap(const hashmap_t *hm)
{
    printf("{");
    for (int i = 0; i < hm->size; i++)
    {
        bool is_last = i == hm->size - 1;
        printf(is_last ? "%s" : "%s,", hm->buckets[i]);
    }
    printf("}\n");
}

int main()
{
    hashmap_t *hm = create_hashmap(10);
    hashmap_insert(hm, "hello");
    print_hashmap(hm);
    delete_hashmap(hm);
    return 0;
}