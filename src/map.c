#include "../include/map.h"

struct map {
    size_t key_size;
    size_t value_size;
};

map* map_init(size_t key_size, size_t value_size) {
    map *m = malloc(sizeof(map));
    return m;
}

void map_free(map *m) {
    return;
}

size_t map_length(const map *m) {
    return 0;
}

bool map_is_empty(const map *m) {
    return false;
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
