#include "benchmark.h"

size_t hash(const void *key) {
    return *(size_t*) key;
}

void* bc_map_init() {
    map *m = map_init(sizeof(size_t), sizeof(char*), hash);
    for (size_t i = 0; i < MAP_LOAD; i++) {
        char const *value = "value";
        map_insert(m, &i, &value);
    }
    return m;
}

void bc_map_free(void *data) {
    map_free((map*) data);
}

void bc_map_insert(void *data) {
    map *m = (map*) data;
    for (size_t i = MAP_LOAD; i < 2 * MAP_LOAD; i++) {
        char const *value = "value";
        map_insert(m, &i, &value);
    }
}

void bc_map_erase(void *data) {
    map *m = (map*) data;
    for (size_t i = 0; i < MAP_LOAD; i++) {
        map_erase(m, &i);
    }
}

void bc_map_get(void *data) {
    map *m = (map*) data;
    for (size_t i = 0; i < MAP_LOAD; i++) {
        char *x = (char*) map_get(m, &i);
    }
}

void bc_map_clear(void *data) {
    map *m = (map*) data;
    map_clear(m);
}

void bc_map_rehash(void *data) {
    map *m = (map*) data;
    map_rehash(m, 1);
}
