#pragma once

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

int hash_str(const char *str);

hashmap_t *init_hm(int size);
void clean_hm(hashmap_t *hm);
int hm_insert(hashmap_t *hm, char *key, char *value);
char *hm_find(hashmap_t *hm, char *key);
void print_hm(const hashmap_t *hm);
