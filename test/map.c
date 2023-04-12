#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "test.h"

#include "../include/map.h"

void test_map_init() {
    map *m = map_init(sizeof(int), sizeof(int), hash_terribly);
    map_free(m);
}

void test_map_init_fail() {
    map *m = map_init(SIZE_MAX, SIZE_MAX, hash_terribly);
    assert(m == NULL);
}

void test_map_with_buckets() {
    map *m = map_with_buckets(sizeof(int), sizeof(int), hash_terribly, 512);
    assert(map_buckets(m) == 512);
    map_free(m);
}

void test_map_with_buckets_fail() {
    map *m = map_with_buckets(sizeof(int), sizeof(int), hash_terribly, SIZE_MAX / 10000);
    assert(m == NULL);
}

void test_map_free() {
    map_free(NULL);

    map *m = map_init(sizeof(int), sizeof(int), hash_terribly);
    map_free(m);
}

void test_map_max_load_factor() {
    map *m = map_with_buckets(sizeof(int), sizeof(int), hash_terribly, 1);
    assert(map_max_load_factor(m) == 1.0);
    map_free(m);
}

void test_map_set_max_load_factor() {
    char *key1 = "key1", *value1 = "value1";
    char *key2 = "key2", *value2 = "value2";
    map *m = map_with_buckets(sizeof(char*), sizeof(char*), hash_terribly, 1);
    assert(map_max_load_factor(m) == 1.0);

    map_set_max_load_factor(m, 2.01);
    assert(fequals(map_max_load_factor(m), 2.01));

    map_insert(m, &key1, &value1);
    map_insert(m, &key2, &value2);
    assert(fequals(map_load_factor(m), 1.0));
    assert(fequals(map_max_load_factor(m), 2.01));

    map_set_max_load_factor(m, 1.0);
    assert(fequals(map_load_factor(m), 0.5));
    assert(fequals(map_max_load_factor(m), 1.0));

    map_free(m);
}

void test_load_factor() {
    char *key1 = "key1", *value1 = "value1";
    char *key2 = "key2", *value2 = "value2";
    char *key3 = "key3", *value3 = "value3";
    map *m = map_with_buckets(sizeof(char*), sizeof(char*), hash_terribly, 1);
    assert(map_buckets(m) == 1);
    assert(map_load_factor(m) == 0.0);

    map_insert(m, &key1, &value1);
    assert(map_size(m) == 1);
    assert(map_buckets(m) == 1);
    assert(map_load_factor(m) == 1.0);

    map_insert(m, &key2, &value2);
    assert(map_size(m) == 2);
    assert(map_buckets(m) == 2);
    assert(map_load_factor(m) == 1.0);

    map_insert(m, &key3, &value3);
    assert(map_size(m) == 3);
    assert(map_buckets(m) == 4);
    assert(map_load_factor(m) == 0.75);

    map_free(m);
}

void test_map_size() {
    char *key1 = "key1", *value1 = "value1";
    char *key2 = "key2", *value2 = "value2";
    char *key3 = "key3", *value3 = "value3";
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_size(m) == 0);

    map_insert(m, &key1, &value1);
    map_insert(m, &key1, &value2);
    map_insert(m, &key1, &value3);
    assert(map_size(m) == 1);

    map_insert(m, &key1, &value1);
    map_insert(m, &key2, &value2);
    map_insert(m, &key3, &value3);
    assert(map_size(m) == 3);

    map_free(m);
}

void test_map_buckets() {
    char *key1 = "key1", *value1 = "value1";
    char *key2 = "key2", *value2 = "value2";
    char *key3 = "key3", *value3 = "value3";
    map *m = map_with_buckets(sizeof(char*), sizeof(char*), hash_terribly, 1);
    assert(map_buckets(m) == 1);

    map_insert(m, &key1, &value1);
    assert(map_size(m) == 1);
    assert(map_buckets(m) == 1);

    map_insert(m, &key2, &value2);
    assert(map_size(m) == 2);
    assert(map_buckets(m) == 2);

    map_insert(m, &key3, &value3);
    assert(map_size(m) == 3);
    assert(map_buckets(m) == 4);

    map_free(m);
}

void test_map_empty() {
    char *key = "key", *value = "value";
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_empty(m));

    map_insert(m, &key, &value);
    assert(!map_empty(m));

    map_erase(m, &key);
    assert(map_empty(m));

    map_free(m);
}

void test_map_clear() {
    char *key1 = "key1", *value1 = "value1";
    char *key2 = "key2", *value2 = "value2";
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_empty(m));

    map_insert(m, &key1, &value1);
    map_insert(m, &key2, &value2);
    assert(map_size(m) == 2);
    assert(strcmp(*(char**) map_get(m, &key1), "value1") == 0);
    assert(strcmp(*(char**) map_get(m, &key2), "value2") == 0);

    map_clear(m);
    assert(map_size(m) == 0);
    assert(map_get(m, &key1) == NULL);
    assert(map_get(m, &key2) == NULL);

    map_free(m);
}

void test_map_has() {
    char *key1 = "key1", *value1 = "value1";
    char *key2 = "key2", *value2 = "value2";
    char *key3 = "key3", *value3 = "value3";
    char *key4 = "key4";
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(!map_has(m, &key1));
    assert(!map_has(m, &key2));
    assert(!map_has(m, &key3));
    assert(!map_has(m, &key4));

    map_insert(m, &key1, &value1);
    map_insert(m, &key2, &value2);
    map_insert(m, &key3, &value3);

    assert(map_has(m, &key1));
    assert(map_has(m, &key2));
    assert(map_has(m, &key3));
    assert(!map_has(m, &key4));

    map_free(m);
}

void test_map_find() {
    char *key = "key", *value = "value";
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_find(m, &key) == NULL);

    map_insert(m, &key, &value);
    pair *entry = map_find(m, &key);
    assert(strcmp(*(char**) pair_first(entry), "key") == 0);
    assert(strcmp(*(char**) pair_second(entry), "value") == 0);

    map_free(m);
}

void test_map_get() {
    char *key = "key", *value = "value";
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_get(m, &key) == NULL);

    map_insert(m, &key, &value);
    assert(strcmp(*(char**) map_get(m, &key), "value") == 0);

    map_free(m);
}

void test_map_insert() {
    char *key1 = "key1";
    char *key2 = "key2";
    char *value = "value";
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_size(m) == 0);

    pair *entry = map_find(m, &key1);
    assert(entry == NULL);

    pair *first_inserted = map_insert(m, &key1, &value);
    entry = map_find(m, &key1);
    assert(map_size(m) == 1);
    assert(first_inserted == entry);
    assert(strcmp(*(char**) pair_first(first_inserted), "key1") == 0);
    assert(strcmp(*(char**) pair_second(first_inserted), "value") == 0);

    pair *second_inserted = map_insert(m, &key1, &value);
    entry = map_find(m, &key1);
    assert(map_size(m) == 1);
    assert(second_inserted == entry);
    assert(second_inserted == first_inserted);
    assert(strcmp(*(char**) pair_first(second_inserted), "key1") == 0);
    assert(strcmp(*(char**) pair_second(second_inserted), "value") == 0);

    pair *third_inserted = map_insert(m, &key2, &value);
    entry = map_find(m, &key2);
    assert(map_size(m) == 2);
    assert(third_inserted != first_inserted);
    assert(third_inserted != second_inserted);
    assert(strcmp(*(char**) pair_first(third_inserted), "key2") == 0);
    assert(strcmp(*(char**) pair_second(third_inserted), "value") == 0);

    map_free(m);
}

void test_map_erase() {
    char *key1 = "key1", *value1 = "value1";
    char *key2 = "key2", *value2 = "value2";
    char *key3 = "key3";
    char *key4 = "key4";
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_size(m) == 0);

    map_insert(m, &key1, &value1);
    map_insert(m, &key2, &value2);
    map_erase(m, &key3);
    map_erase(m, &key4);
    pair *first_entry = map_find(m, &key1);
    pair *second_entry = map_find(m, &key2);
    assert(map_size(m) == 2);
    assert(strcmp(*(char**) pair_first(first_entry), "key1") == 0);
    assert(strcmp(*(char**) pair_second(first_entry), "value1") == 0);
    assert(strcmp(*(char**) pair_first(second_entry), "key2") == 0);
    assert(strcmp(*(char**) pair_second(second_entry), "value2") == 0);

    map_erase(m, &key1);
    first_entry = map_find(m, &key1);
    second_entry = map_find(m, &key2);
    assert(map_size(m) == 1);
    assert(first_entry == NULL);
    assert(strcmp(*(char**) pair_first(second_entry), "key2") == 0);
    assert(strcmp(*(char**) pair_second(second_entry), "value2") == 0);

    map_erase(m, &key2);
    first_entry = map_find(m, &key1);
    second_entry = map_find(m, &key2);
    assert(map_size(m) == 0);
    assert(first_entry == NULL);
    assert(second_entry == NULL);

    map_erase(m, &key1);
    map_erase(m, &key2);
    map_erase(m, &key3);
    map_erase(m, &key4);
    assert(map_size(m) == 0);

    map_free(m);
}

void test_map_rehash() {
    char *key1 = "key1", *value1 = "value1";
    char *key2 = "key2", *value2 = "value2";
    char *key3 = "key3", *value3 = "value3";
    map *m = map_with_buckets(sizeof(char*), sizeof(char*), hash_terribly, 10);
    assert(map_buckets(m) == 10);
    assert(map_size(m) == 0);

    map_rehash(m, 1);
    assert(map_buckets(m) == 1);
    assert(map_size(m) == 0);

    map_insert(m, &key1, &value1);
    assert(map_buckets(m) == 1);
    assert(map_size(m) == 1);

    map_insert(m, &key2, &value2);
    assert(map_buckets(m) == 2);
    assert(map_size(m) == 2);

    map_insert(m, &key3, &value3);
    assert(map_buckets(m) == 4);
    assert(map_size(m) == 3);

    map_rehash(m, 0);
    assert(map_buckets(m) == 4);
    assert(map_size(m) == 3);
    assert(strcmp(*(char**) map_get(m, &key1), "value1") == 0);
    assert(strcmp(*(char**) map_get(m, &key2), "value2") == 0);
    assert(strcmp(*(char**) map_get(m, &key3), "value3") == 0);

    map_rehash(m, 512);
    assert(map_buckets(m) == 512);
    assert(map_size(m) == 3);
    assert(strcmp(*(char**) map_get(m, &key1), "value1") == 0);
    assert(strcmp(*(char**) map_get(m, &key2), "value2") == 0);
    assert(strcmp(*(char**) map_get(m, &key3), "value3") == 0);

    map_free(m);
}

void test_map_load() {
    bool has, empty;
    size_t size;
    float max_load_factor, load_factor;
    pair *inserted;

    map *m = map_init(sizeof(size_t), sizeof(size_t), hash_int);

    for (size_t i = 0; i < TEST_LOAD; i++) {
        inserted = map_insert(m, &i, &i);
        size = map_size(m);
        empty = map_empty(m);
        has = map_has(m, &i);
        load_factor = map_load_factor(m);
        max_load_factor = map_max_load_factor(m);
        assert(*(size_t*) pair_first(inserted) == i);
        assert(*(size_t*) pair_second(inserted) == i);
        assert(size == i + 1);
        assert(!empty);
        assert(has);
        assert(load_factor <= max_load_factor);
    }

    for (size_t i = 0; i < TEST_LOAD / 2; i++) {
        map_erase(m, &i);
        size = map_size(m);
        empty = map_empty(m);
        has = map_has(m, &i);
        load_factor = map_load_factor(m);
        max_load_factor = map_max_load_factor(m);
        assert(size == TEST_LOAD - i - 1);
        assert(!empty);
        assert(!has);
        assert(load_factor <= max_load_factor);
    }

    map_clear(m);
    size = map_size(m);
    empty = map_empty(m);
    assert(size == 0);
    assert(empty);

    map_free(m);
}

void test_map() {
    test_map_init();
    test_map_init_fail();
    test_map_with_buckets();
    test_map_with_buckets_fail();
    test_map_free();
    test_map_max_load_factor();
    test_map_set_max_load_factor();
    test_load_factor();
    test_map_size();
    test_map_buckets();
    test_map_empty();
    test_map_clear();
    test_map_has();
    test_map_find();
    test_map_get();
    test_map_insert();
    test_map_erase();
    test_map_rehash();
    test_map_load();
}
