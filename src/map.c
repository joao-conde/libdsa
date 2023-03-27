#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "../include/list.h"
#include "../include/map.h"

#define CAPACITY 512
#define LOAD_FACTOR 1.0

struct map {
    size_t length;
    size_t capacity;
    size_t key_size;
    size_t value_size;
    size_t max_load_factor;
    list **buckets;
    hash_fn *hasher;
};

map* map_init(size_t key_size, size_t value_size, hash_fn *hasher) {
    // checks for overflow of amount of requested memory
    if (key_size > PTRDIFF_MAX || value_size > PTRDIFF_MAX) return NULL;

    map *m = (map*) malloc(sizeof(map));
    list **buckets = (list**) malloc(CAPACITY * sizeof(list*));
    if (m == NULL || buckets == NULL) {
        free(buckets);
        free(m);
        return NULL;
    }

    int i = 0;
    for (i = 0; i < CAPACITY; i++) {
        buckets[i] = list_init(PAIR_SIZE);
        if (buckets[i] == NULL) break;
    }
    if (i < CAPACITY) {
        for (int j = 0; j < i; j++) free(buckets[j]);
        free(buckets);
        free(m);
        return NULL;
    }

    m->length = 0;
    m->capacity = CAPACITY;
    m->key_size = key_size;
    m->value_size = value_size;
    m->max_load_factor = LOAD_FACTOR;
    m->buckets = buckets;
    m->hasher = hasher;
    return m;
}

void map_free(map *m) {
    if (m != NULL) {
        // free each allocated bucket
        for (size_t i = 0; i < m->capacity; i++) {
            list *bucket = (list *) m->buckets[i];
            while (list_length(bucket) > 0) {
                list_node *front = list_front(bucket);

                pair *entry = (pair*) front->data;
                pair_free(entry);
                front->data = NULL;

                list_pop_back(bucket);
            }
            list_free(bucket);
        }

        // free the buckets container
        free(m->buckets);
    }
    free(m);
}

pair* map_find(const map *m, const void *key) {
    size_t hash = m->hasher(key) % m->capacity;
    list *bucket = m->buckets[hash];
    if (bucket == NULL) return NULL;

    list_node *cur = list_front(bucket);
    while (cur->next != NULL && memcmp(pair_first(cur->data), key, m->key_size) != 0) {
        cur = cur->next;
    }
    if (cur == NULL) return NULL;
    return cur->data;
}

void* map_get(const map *m, const void *key) {
    pair *entry = map_find(m, key);
    if (entry == NULL) return NULL;
    return pair_second(entry);
}

pair* map_insert(map *m, const void *key, const void *value) {
    pair *entry = map_find(m, key);
    if (entry != NULL) {
        pair_set_second(entry, value);
        return entry;
    }

    size_t hash = m->hasher(key) % m->capacity;
    list *bucket = m->buckets[hash];
    if (bucket == NULL) return NULL;

    entry = pair_init(key, value, m->key_size, m->value_size);
    list_node *inserted = list_push_back(bucket, entry);
    return inserted->data;
}
