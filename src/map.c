#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "../include/list.h"
#include "../include/map.h"
#include "../include/pair.h"

#define CAPACITY 512
#define LOAD_FACTOR 1.0

struct map {
    size_t length;
    size_t capacity;
    size_t key_size;
    size_t value_size;
    size_t max_load_factor;
    list **buckets;
};

map* map_init(size_t key_size, size_t value_size) {
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

void* map_get(const map *m, const void *key) {
    return NULL;
}

void map_insert(map *m, const void *key, const void *value) { }
