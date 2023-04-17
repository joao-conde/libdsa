#include "internal/set.h"

#include "../include/map.h"
#include "../include/set.h"

struct set {
    map *data;
};

set* set_init(size_t type_size, hash_fn *hasher) {
    return set_with_buckets(type_size, hasher, NBUCKETS);
}

set* set_with_buckets(size_t type_size, hash_fn *hasher, size_t nbuckets) {
    set *s = (set*) malloc(sizeof(set));
    map *data = map_with_buckets(type_size, type_size, hasher, nbuckets);
    if (s == NULL || data == NULL) {
        map_free(data);
        free(s);
        return NULL;
    }

    s->data = data;
    return s;
}

void set_free(set *s) {
    if (s != NULL) map_free(s->data);
    free(s);
}

float set_max_load_factor(const set *s) {
    return map_max_load_factor(s->data);
}

void set_set_max_load_factor(set *s, float factor) {
    map_set_max_load_factor(s->data, factor);
}

float set_load_factor(const set *s) {
    return map_load_factor(s->data);
}

size_t set_size(const set *s) {
    return map_size(s->data);
}

size_t set_buckets(const set *s) {
    return map_buckets(s->data);
}

bool set_empty(const set *s) {
    return map_empty(s->data);
}

void set_clear(set *s) {
    map_clear(s->data);
}

bool set_has(const set *s, const void *value) {
    return map_has(s->data, value);
}

void* set_insert(set *s, const void *value) {
    pair *inserted = map_insert(s->data, value, value);
    if (inserted == NULL) return NULL;
    return pair_first(inserted);
}

void set_erase(set *s, const void *value) {
    map_erase(s->data, value);
}

void set_rehash(set *s, size_t nbuckets) {
    map_rehash(s->data, nbuckets);
}
