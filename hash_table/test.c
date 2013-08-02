#include "ht.h"
#include <stdio.h>

uint32_t hash_fun(void * key, size_t len)
{
    uint32_t h = 0;

    uint8_t * p = key;

    for (int i = 0; i < len; i++) {
        h = h * 33 + p[i];
    }

    return h;
}

int hash_iter(void * key, size_t len, void * value)
{
    printf("\t%s:\t%s,\n", (char *)key, (char *)value);

    return 0;
}

void hash_dump(ht_t * ht)
{
    printf("{\n");
    ht_iter(ht, &hash_iter);
    printf("}\n");
}

int main(int argc, char ** argv)
{
    ht_t * ht = ht_new(&hash_fun, 1024);

    ht_add(ht, "foo", 3, "bar");
    ht_add(ht, "bar", 3, "baz");

    hash_dump(ht);

    ht_delete(ht, "bar", 3);

    hash_dump(ht);
}
