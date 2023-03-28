#include <stdint.h>
#include <string.h>

#include "internal/map.h"

#include "../include/list.h"
#include "../include/map.h"

map* map_init(size_t key_size, size_t value_size, hash_fn *hasher) {
    return map_with_capacity(key_size, value_size, hasher, CAPACITY);
}

map* map_with_capacity(size_t key_size, size_t value_size, hash_fn *hasher, size_t capacity) {
    // checks for overflow of amount of requested memory
    if (key_size > PTRDIFF_MAX || value_size > PTRDIFF_MAX) return NULL;

    map *m = (map*) malloc(sizeof(map));
    list **buckets = (list**) malloc(capacity * sizeof(list*));
    if (m == NULL || buckets == NULL) {
        free(buckets);
        free(m);
        return NULL;
    }

    for (size_t i = 0; i < capacity; i++) {
        buckets[i] = list_init(PAIR_SIZE);
    }

    m->length = 0;
    m->capacity = capacity;
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

size_t map_length(const map *m) {
    return m->length;
}

size_t map_capacity(const map *m) {
    return m->capacity;
}

bool map_is_empty(const map *m) {
    return m->length == 0;
}

bool map_has(const map *m, const void *key) {
    return map_get(m, key) != NULL;
}

pair* map_find(const map *m, const void *key) {
    size_t hash = m->hasher(key) % m->capacity;
    list *bucket = m->buckets[hash];
    if (bucket == NULL) return NULL;

    list_node *cur = list_front(bucket);
    while (
        cur != NULL &&
        memcmp(pair_first((pair*) cur->data), key, m->key_size) != 0
    ) {
        cur = cur->next;
    }
    if (cur == NULL) return NULL;
    return (pair*) cur->data;
}

void* map_get(const map *m, const void *key) {
    pair *entry = map_find(m, key);
    if (entry == NULL) return NULL;
    return pair_second(entry);
}

pair* map_insert(map *m, const void *key, const void *value) {
    // if the current percentual load of the hashmap exceeds
    // our limit we resize and rehash every entry
    if (m->length * m->max_load_factor >= m->capacity) {
        map_rehash(m, m->capacity * ALLOC_FACTOR);
    }

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
    if (inserted == NULL) return NULL;

    m->length += 1;
    return (pair*) inserted->data;
}

void map_erase(map *m, const void *key) {
    size_t hash = m->hasher(key) % m->capacity;
    list *bucket = m->buckets[hash];
    if (bucket == NULL) return;

    list_node *cur = list_front(bucket);
    while (
        cur != NULL &&
        memcmp(pair_first((pair*) cur->data), key, m->key_size) != 0
    ) {
        cur = cur->next;
    }
    if (cur == NULL) return;

    m->length -= 1;
    list_erase(bucket, cur);
}

void map_rehash(map *m, size_t capacity) {
    size_t min = m->length / m->max_load_factor;
    capacity = capacity > min ? capacity : min;

    map *rehashed = map_with_capacity(m->key_size, m->value_size, m->hasher, capacity);
    if (rehashed == NULL) return;

    for (size_t i = 0; i < m->length; i++) {
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

    m->length = rehashed->length;
    m->capacity = rehashed->capacity;
    m->buckets = rehashed->buckets;
}
