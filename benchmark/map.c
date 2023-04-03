#include "benchmark.h"

size_t hash(const void *key) {
    return *(size_t*) key;
}

void bc_map_insert() {
    map *m = map_init(sizeof(size_t), sizeof(char*), hash);
    for (size_t i = 0; i < MAP_LOAD; i++) {
        char const *value = "value";
        map_insert(m, &i, &value);
    }
    map_free(m);
}

void bc_map_insert_erase() {
    map *m = map_init(sizeof(size_t), sizeof(char*), hash);
    for (size_t i = 0; i < MAP_LOAD; i++) {
        char const *value = "value";
        map_insert(m, &i, &value);
    }
    for (size_t i = 0; i < MAP_LOAD; i++) {
        map_erase(m, &i);
    }
    map_free(m);
}

void bc_map_insert_get() {
    map *m = map_init(sizeof(size_t), sizeof(char*), hash);
    for (size_t i = 0; i < MAP_LOAD; i++) {
        char const *value = "value";
        map_insert(m, &i, &value);
        char *x = (char*) map_get(m, &i);
    }
    map_free(m);
}

void bc_map_insert_clear() {
    map *m = map_init(sizeof(size_t), sizeof(char*), hash);
    for (size_t i = 0; i < MAP_LOAD; i++) {
        char const *value = "value";
        map_insert(m, &i, &value);
    }
    map_clear(m);
    map_free(m);
}

void bc_map_insert_rehash() {
    map *m = map_init(sizeof(size_t), sizeof(char*), hash);
    for (size_t i = 0; i < MAP_LOAD; i++) {
        char const *value = "value";
        map_insert(m, &i, &value);
    }
    map_rehash(m, 1);
    map_free(m);
}
