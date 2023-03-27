#include <assert.h>
#include <string.h>

#include "../include/map.h"

size_t hash_int(const void *key) {
    return *(int*)(key);
}

void test_map_init() {
    map *m = map_init(sizeof(int), sizeof(char*), hash_int);
    map_free(m);
}

void test_map_free() {
    map_free(NULL);

    map *m = map_init(sizeof(int), sizeof(char*), hash_int);
    map_free(m);
}

void test_map_find() {
    int key = 1;
    map *m = map_init(sizeof(int), sizeof(char*), hash_int);

    pair *entry = map_find(m, &key);
    assert(entry == NULL);

    map_insert(m, &key, "value");
    entry = map_find(m, &key);
    assert(*(int*) pair_first(entry) == 1);
    assert(strcmp(pair_second(entry), "value") == 0);

    map_free(m);
}

void test_map_get() {
    int key = 1;
    map *m = map_init(sizeof(int), sizeof(char*), hash_int);

    assert(map_get(m, &key) == NULL);

    map_insert(m, &key, "value");
    assert(strcmp(map_get(m, &key), "value") == 0);
    assert(map_get(m, &key) == map_get(m, &key));

    map_free(m);
}

void test_map_insert() {
    int keys[2] = {1, 2};
    map *m = map_init(sizeof(int), sizeof(char*), hash_int);
    assert(map_length(m) == 0);

    assert(map_find(m, &keys[0]) == NULL);

    pair *first_inserted = map_insert(m, &keys[0], "value");
    pair *entry = map_find(m, &keys[0]);
    assert(map_length(m) == 1);
    assert(first_inserted == entry);
    assert(*(int*) pair_first(first_inserted) == 1);
    assert(strcmp(pair_second(first_inserted), "value") == 0);

    pair *second_inserted = map_insert(m, &keys[0], "value");
    entry = map_find(m, &keys[0]);
    assert(map_length(m) == 1);
    assert(second_inserted == entry);
    assert(second_inserted == first_inserted);
    assert(*(int*) pair_first(second_inserted) == 1);
    assert(strcmp(pair_second(second_inserted), "value") == 0);

    pair *third_inserted = map_insert(m, &keys[1], "value");
    entry = map_find(m, &keys[1]);
    assert(map_length(m) == 2);
    assert(third_inserted != first_inserted);
    assert(third_inserted != second_inserted);
    assert(*(int*) pair_first(third_inserted) == 2);
    assert(strcmp(pair_second(third_inserted), "value") == 0);

    map_free(m);
}

void test_map() {
    test_map_init();
    test_map_free();
    test_map_find();
    test_map_get();
    test_map_insert();
}
