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
    hash_fn *hash;
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

map* map_init(size_t key_size, size_t value_size, hash_fn *hash) {
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
    m->key_size = key_size;
    m->value_size = value_size;
    m->nbuckets = CAPACITY;
    m->buckets = buckets;
    m->hash = hash != NULL ? hash : &hash_int;
    return m;
}

void map_free(map *m) {
    if (m != NULL) {
        // free each allocated bucket
        for (size_t i = 0; i < m->nbuckets; i++) {
            list *bucket = (list *) m->buckets[i];
            while (list_length(bucket) > 0) {
                node *front = list_front(bucket);

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

bool map_is_empty(const map *m) {
    return m->length == 0;
}

bool map_has(const map *m, const void *key) {
    return map_find(m, key) != NULL;
}

void map_clear(map *m) {
    m->length = 0;
}

node* map_find(const map *m, const void *key) {
    size_t bucket_i = m->hash(key) % m->nbuckets;
    list *bucket = m->buckets[bucket_i];
    node* current = list_front(bucket);
    while (current != NULL) {
        pair *entry = (pair*) current->data;
        if (memcmp(pair_first(entry), key, m->key_size) == 0) break;
        current = current->next;
    }
    return current;
}

void* map_get(const map *m, const void *key) {
    node *n = map_find(m, key);
    if (n == NULL) return NULL;

    pair *entry = (pair*) n->data;
    if (entry == NULL) return NULL;

    return pair_second(entry);
}

pair* map_insert(map *m, const void *key, const void *value) {
    size_t bucket_i = m->hash(key) % m->nbuckets;
    list *bucket = m->buckets[bucket_i];
    pair *entry = pair_init(key, value, m->key_size, m->value_size);
    if (entry == NULL) return NULL;

    node *pushed = list_push_back(bucket, entry);
    if (pushed == NULL) return NULL;

    m->length += 1;
    return entry;
}

void map_erase(map *m, const void *key) {
    size_t bucket_i = m->hash(key) % m->nbuckets;
    list *bucket = m->buckets[bucket_i];

    node *n = map_find(m, key);
    if (n == NULL) return;

    list_erase(bucket, n);
    m->length -= 1;
}

void rehash(map *m, size_t nbuckets) {
    m->nbuckets = nbuckets;
    return;
}
