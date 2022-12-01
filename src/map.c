#include <stdint.h>
#include <string.h>

#include "../include/list.h"
#include "../include/map.h"
#include "../include/pair.h"

#define CAPACITY 256

struct map {
    size_t length;
    size_t key_size;
    size_t value_size;
    size_t nbuckets;
    list **buckets;
    hash_fn *hash_fn;
};

size_t hash_int(const void *key) {
    size_t hash = *(int*) key;
    return hash;
}

size_t hash_str(const void *key) {
    size_t hash = 0;
    char *str = (char*) key;
    for (int i = 0; str[i] != 0; i++) hash += (i + 1) * (uint8_t) str[i];
    return hash;
}

node* map_find(const map *m, const void *key) {
    size_t hash = m->hash_fn(key) % m->nbuckets;
    list *bucket = m->buckets[hash];
    node* current = list_front(bucket);
    while (current != NULL) {
        pair *entry = current->data;
        if (memcmp(pair_first(entry), key, m->key_size) == 0) break;
        current = current->next;
    }
    return current;
}

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
    m->key_size = key_size;
    m->value_size = value_size;
    m->nbuckets = CAPACITY;
    m->buckets = buckets;
    m->hash_fn = hash_fn != NULL ? hash_fn : hash_int;
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
    return map_find(m, key) != NULL;
}

void map_clear(map *m) {
    m->length = 0;
}

void* map_get(const map *m, const void *key) {
    node *node = map_find(m, key);
    if (node == NULL) return NULL;

    pair *entry = node->data;
    if (entry == NULL) return NULL;

    return pair_second(entry);
}

pair* map_insert(map *m, const void *key, const void *value) {
    size_t hash = m->hash_fn(key) % m->nbuckets;
    list *bucket = m->buckets[hash];
    pair *entry = pair_init(key, value, m->key_size, m->value_size);
    if (entry == NULL) return NULL;

    node *pushed = list_push_back(bucket, entry);
    if (pushed == NULL) return NULL;

    m->length += 1;
    return entry;
}

void map_erase(map *m, const void *key) {
    size_t hash = m->hash_fn(key) % m->nbuckets;
    list *bucket = m->buckets[hash];

    node *node = map_find(m, key);
    if (node == NULL) return;

    list_erase(bucket, node);
    m->length -= 1;
}

void rehash(map *m, size_t nbuckets) {
    return;
}
