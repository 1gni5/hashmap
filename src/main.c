#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main()
{
    printf("hello, world!\n");
    return 0;
}