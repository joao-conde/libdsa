#include <stdint.h>
#include <string.h>

#include "internal/map.h"

#include "../include/list.h"
#include "../include/map.h"

struct map {
    size_t size;
    size_t nbuckets;
    size_t key_size;
    size_t value_size;
    float max_load_factor;
    list **buckets;
    hash_fn *hasher;
};

map* map_init(size_t key_size, size_t value_size, hash_fn *hasher) {
    return map_with_buckets(key_size, value_size, hasher, NBUCKETS);
}

map* map_with_buckets(size_t key_size, size_t value_size, hash_fn *hasher, size_t nbuckets) {
    // checks for overflow of amount of requested memory
    if (key_size > PTRDIFF_MAX || value_size > PTRDIFF_MAX || nbuckets > PTRDIFF_MAX) return NULL;

    map *m = (map*) malloc(sizeof(map));
    list **buckets = (list**) malloc(nbuckets * sizeof(list*));
    if (m == NULL || buckets == NULL) {
        free(buckets);
        free(m);
        return NULL;
    }

    // initializes the requested number of buckets
    for (size_t i = 0; i < nbuckets; i++) {
        buckets[i] = list_init(PAIR_SIZE);
    }

    m->size = 0;
    m->nbuckets = nbuckets;
    m->key_size = key_size;
    m->value_size = value_size;
    m->max_load_factor = LOAD_FACTOR;
    m->buckets = buckets;
    m->hasher = hasher;
    return m;
}

void map_free(map *m) {
    if (m != NULL) _map_free_buckets(m);
    free(m);
}

float map_max_load_factor(const map *m) {
    return m->max_load_factor;
}

void map_set_max_load_factor(map *m, float factor) {
    m->max_load_factor = factor;

    // if the current load of the hashmap exceeds
    // the limit we resize and rehash every entry
    if (m->size * m->max_load_factor >= m->nbuckets) {
        map_rehash(m, m->nbuckets * ALLOC_FACTOR);
    }
}

float map_load_factor(const map *m) {
    return (float) m->size / (float) m->nbuckets;
}

size_t map_size(const map *m) {
    return m->size;
}

size_t map_buckets(const map *m) {
    return m->nbuckets;
}

bool map_empty(const map *m) {
    return m->size == 0;
}

void map_clear(map *m) {
    for (size_t i = 0; i < m->nbuckets; i++) {
        list *bucket = m->buckets[i];

        // free each key-value pair in the bucket
        list_node *cur = list_front(bucket);
        while (cur != NULL) {
            pair *entry = (pair*) cur->data;
            pair_free(entry);
            cur->data = NULL;
            cur = cur->next;
        }

        // clear the bucket
        list_clear(bucket);
    }

    m->size = 0;
}

bool map_has(const map *m, const void *key) {
    return map_find(m, key) != NULL;
}

pair* map_find(const map *m, const void *key) {
    list *bucket = _map_find_bucket(m, key);
    if (bucket == NULL) return NULL;

    list_node *cur = _map_find_bucket_node(m, bucket, key);
    if (cur == NULL) return NULL;

    return (pair*) cur->data;
}

void* map_get(const map *m, const void *key) {
    pair *entry = map_find(m, key);
    if (entry == NULL) return NULL;
    return pair_second(entry);
}

pair* map_insert(map *m, const void *key, const void *value) {
    // if the current load of the hashmap exceeds
    // the limit we resize and rehash every entry
    if (m->size * m->max_load_factor >= m->nbuckets) {
        map_rehash(m, m->nbuckets * ALLOC_FACTOR);
    }

    // if the key exists we update the value and return
    pair *entry = map_find(m, key);
    if (entry != NULL) {
        pair_set_second(entry, value);
        return entry;
    }

    list *bucket = _map_find_bucket(m, key);
    if (bucket == NULL) return NULL;

    // create the key-value pair, insert in the bucket
    // and free the original pair
    entry = pair_init(key, value, m->key_size, m->value_size);
    list_node *inserted = list_push_back(bucket, entry);
    free(entry);

    if (inserted == NULL) return NULL;

    m->size += 1;
    return (pair*) inserted->data;
}

void map_erase(map *m, const void *key) {
    list *bucket = _map_find_bucket(m, key);
    if (bucket == NULL) return;

    list_node *cur = _map_find_bucket_node(m, bucket, key);
    if (cur == NULL) return;

    // free the key-value pair
    pair_free((pair*) cur->data);
    cur->data = NULL;

    // remove the key-value node from the bucket
    list_erase(bucket, cur);

    m->size -= 1;
}

void map_rehash(map *m, size_t nbuckets) {
    // compute minimum number of buckets to rehash to
    size_t minbuckets = 1 + m->size / m->max_load_factor;
    nbuckets = nbuckets > minbuckets ? nbuckets : minbuckets;

    map *rehashed = map_with_buckets(m->key_size, m->value_size, m->hasher, nbuckets);
    if (rehashed == NULL) return;

    // insert the key-value pairs in a new map with nbuckets
    for (size_t i = 0; i < m->nbuckets; i++) {
        list *bucket = m->buckets[i];

        list_node *cur = list_front(bucket);
        while (cur != NULL) {
            pair *entry = (pair*) cur->data;
            void *key = pair_first(entry);
            void *value = pair_second(entry);
            map_insert(rehashed, key, value);
            cur = cur->next;
        }
    }

    // free the original buckets which are no longer valid
    _map_free_buckets(m);

    m->size = rehashed->size;
    m->nbuckets = rehashed->nbuckets;
    m->buckets = rehashed->buckets;

    free(rehashed);
}

void _map_free_buckets(map *m) {
    for (size_t i = 0; i < m->nbuckets; i++) {
        list *bucket = m->buckets[i];

        // free each key-value pair in the bucket
        list_node *cur = list_front(bucket);
        while (cur != NULL) {
            pair *entry = (pair*) cur->data;
            pair_free(entry);
            cur->data = NULL;
            cur = cur->next;
        }

        // free the bucket
        list_free(bucket);
    }

    free(m->buckets);
}

list* _map_find_bucket(const map *m, const void *key) {
    size_t hash = m->hasher(key) % m->nbuckets;
    list *bucket = m->buckets[hash];
    return bucket;
}

list_node* _map_find_bucket_node(const map *m, const list *bucket, const void *key) {
    list_node *cur = list_front(bucket);
    while (
        cur != NULL &&
        memcmp(pair_first((pair*) cur->data), key, m->key_size) != 0
    ) {
        cur = cur->next;
    }
    return cur;
}
