#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashmap.h"
#include "array.h"

entry_t **gen_data(int sample_size)
{
    entry_t **data = (entry_t **)malloc(sizeof(entry_t) * sample_size);
    for (int i = 0; i < sample_size; i++)
    {
        int buffer_size = 8;
        char *key = (char *)malloc(buffer_size), *value = (char *)malloc(buffer_size);

        snprintf(key, sizeof(key), "key%d", i);
        snprintf(value, sizeof(value), "%d", rand() % 10000);

        data[i] = (entry_t *)malloc(sizeof(entry_t));
        data[i]->key = key;
        data[i]->value = value;
    }
    return data;
}

int main(int argc, char **argv)
{
    int size = 10000;
    int lookup_no = 20000;

    entry_t **data = gen_data(size);
    hashmap_t *hm = init_hm(size);

    for (int i = 0; i < size; i++)
    {
        entry_t *entry = data[i];
        hm_insert(hm, entry->key, entry->value);
    }

    for (int i = 0; i < lookup_no; i++)
    {
        char key[8], *value;
        snprintf(key, sizeof(key), "key%d", rand() % size);
        // value = arr_find(data, size, key);
        value = hm_find(hm, key);
    }

    delete_array(data, size);
    clean_hm(hm);
}