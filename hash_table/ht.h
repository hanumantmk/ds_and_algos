#ifndef HT_GUARD
#define HT_GUARD

#include <stdint.h>
#include <stddef.h>

typedef uint32_t (* ht_hash_t)(void * key, size_t len);
typedef int (* ht_iter_fun_t)(void * key, size_t len, void * value);

typedef struct ht_bucket {
    void * key;
    size_t len;

    void * value;

    struct ht_bucket * next;
} ht_bucket_t;

typedef struct ht {
    ht_bucket_t ** buckets;
    size_t num_buckets;

    ht_hash_t hash;
} ht_t;

ht_t * ht_new(ht_hash_t hash, size_t num_buckets);
int ht_add(ht_t * ht, void * key, size_t len, void * value);
int ht_delete(ht_t * ht, void * key, size_t len);
void ht_iter(ht_t * ht, ht_iter_fun_t fun);

#endif
