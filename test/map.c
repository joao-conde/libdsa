#include <assert.h>

#include "../include/map.h"

void test_map_init() {
    map *m = map_init(sizeof(int), sizeof(int));
    map_free(m);
}

void test_map_free() {
    map_free(NULL);

    map *m = map_init(sizeof(int), sizeof(int));
    map_free(m);
}

void test_map() {
    test_map_init();
    test_map_free();
}
