#include "../include/list.h"
#include "../include/map.h"

#define CAPACITY 256

size_t hash_size_t(void *key) {
    return *(size_t*) key % CAPACITY;
}

struct map {
    size_t length;
    size_t key_size;
    size_t value_size;
    size_t nbuckets;
    list **buckets;
    hash_fn *hash_fn;
};

map* map_init(size_t key_size, size_t value_size, hash_fn *hash_fn) {
    map *m = malloc(sizeof(map));
    list **buckets = malloc(CAPACITY * sizeof(list*));
    if (m == NULL || buckets == NULL) {
        free(buckets);
        free(m);
        return NULL;
    }

    int i = 0;
    for (i = 0; i < CAPACITY; i++) {
        buckets[i] = list_init(value_size);
        if (buckets[i] == NULL) break;
    }
    if (i < CAPACITY) {
        for (int j = 0; j < i; j++) free(buckets[j]);
        free(buckets);
        free(m);
        return NULL;
    }

    m->length = 0;
    m->key_size = key_size;
    m->value_size = value_size;
    m->nbuckets = CAPACITY;
    m->buckets = buckets;
    m->hash_fn = hash_fn != NULL ? hash_fn : hash_size_t;
    return m;
}

void map_free(map *m) {
    if (m != NULL) {
        free(m->buckets);
    }
    free(m);
}

size_t map_length(const map *m) {
    return m->length;
}

bool map_is_empty(const map *m) {
    return m->length == 0;
}

bool map_has(const map *m, const void *key) {
    return false;
}

void map_clear(map *m) {
    return;
}

void* map_get(const map *m, const void *key) {
    return NULL;
}

void* map_insert(map *m, const void *key, const void *value) {
    return NULL;
}

void* map_erase(map *m, const void *key) {
    return NULL;
}

void rehash(map *m, size_t nbuckets) {
    return;
}
