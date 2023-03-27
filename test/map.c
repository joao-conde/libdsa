#include <assert.h>

#include "../include/map.h"

size_t hash_size_t(const void *key) {
    return *(size_t*)(key);
}

void test_map_init() {
    map *m = map_init(sizeof(size_t), sizeof(size_t), hash_size_t);
    map_free(m);
}

void test_map_free() {
    map_free(NULL);

    map *m = map_init(sizeof(size_t), sizeof(size_t), hash_size_t);
    map_free(m);
}

void test_map() {
    test_map_init();
    test_map_free();
}
