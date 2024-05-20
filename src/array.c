#include <string.h>
#include <stdlib.h>

#include "array.h"

char *arr_find(entry_t **array, int size, char *key)
{
    for (int i = 0; i < size; i++)
    {
        if (!strcmp(array[i]->key, key))
        {
            return array[i]->value;
        }
    }
    return NULL;
}

void delete_array(entry_t **array, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(array[i]->key);
        free(array[i]->value);
        free(array[i]);
    }

    free(array);
}
