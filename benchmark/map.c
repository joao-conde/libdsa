#include "benchmark.h"

size_t hash(const void *key) {
    return *(size_t*) key;
}

void* c_map_init() {
    map *m = map_init(sizeof(size_t), sizeof(char*), hash);
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        char const *value = "value";
        map_insert(m, &i, &value);
    }
    return m;
}

void c_map_free(void *data) {
    map_free((map*) data);
}

void c_map_insert(void *data) {
    map *m = (map*) data;
    for (size_t i = BENCH_LOAD; i < 2 * BENCH_LOAD; i++) {
        char const *value = "value";
        map_insert(m, &i, &value);
    }
}

void c_map_erase(void *data) {
    map *m = (map*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        map_erase(m, &i);
    }
}

void c_map_get(void *data) {
    map *m = (map*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        char *x = (char*) map_get(m, &i);
    }
}

void c_map_clear(void *data) {
    map *m = (map*) data;
    map_clear(m);
}

void c_map_rehash(void *data) {
    map *m = (map*) data;
    map_rehash(m, 1);
}
