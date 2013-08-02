#include "ht.h"
#include <malloc.h>
#include <string.h>

ht_t * ht_new(ht_hash_t hash, size_t num_buckets)
{
    ht_t * ht = calloc(sizeof(*ht), 1);

    ht->buckets = calloc(sizeof(ht_bucket_t), num_buckets);
    ht->num_buckets = num_buckets;

    ht->hash = hash;

    return ht;
}

ht_bucket_t * ht__bucket_new(void * key, size_t len, void * value)
{
    ht_bucket_t * bucket = calloc(sizeof(*bucket), 1);

    bucket->key = malloc(len);

    memcpy(bucket->key, key, len);

    bucket->len = len;
    bucket->value = value;

    return bucket;
}

int ht_add(ht_t * ht, void * key, size_t len, void * value)
{
    int entry = ht->hash(key, len) % ht->num_buckets;

    ht_bucket_t * list = ht->buckets[entry];

    if (list) {
        ht_bucket_t * ele;

        for (ele = list; ele->next; ele = ele->next) {
            if (ele->len == len && (memcmp(ele->key, key, len) == 0)) {
                return 1;
            }
        }

        ele->next = ht__bucket_new(key, len, value);
    } else {
        ht->buckets[entry] = ht__bucket_new(key, len, value);
    }

    return 0;
}

void ht__bucket_delete(ht_bucket_t * bucket)
{
    free(bucket->key);
    free(bucket);
}

int ht_delete(ht_t * ht, void * key, size_t len)
{
    int entry = ht->hash(key, len) % ht->num_buckets;

    ht_bucket_t * list = ht->buckets[entry];

    if (list) {
        ht_bucket_t * ele, * prev = NULL;

        for (ele = list; ele; prev = ele, ele = ele->next) {
            if (ele->len == len && (memcmp(ele->key, key, len) == 0)) {
                if (prev) {
                    prev->next = ele->next;
                } else {
                    ht->buckets[entry] = NULL;
                }

                ht__bucket_delete(ele);

                return 0;
            }
        }
    }

    return 1;
}

void ht_iter(ht_t * ht, ht_iter_fun_t fun)
{
    for (int i = 0; i < ht->num_buckets; i++) {
        ht_bucket_t * ele;

        for (ele = ht->buckets[i]; ele; ele = ele->next) {
            if (fun(ele->key, ele->len, ele->value)) break;
        }
    }
}
