#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "../include/map.h"

size_t hash_str(const void *key) {
    size_t hash = 0;
    char *str = (char*) key;
    for (int i = 0; str[i] != 0; i++) hash += (i + 1) * (uint8_t) str[i];
    return hash;
}

size_t hash_terribly(const void *key) {
    return hash_str(key) % 4;
}

bool fequals(float f1, float f2) {
    return fabs(f1 - f2) <= FLT_EPSILON;
}

void test_map_init() {
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    map_free(m);
}

void test_map_init_fail() {
    map *m = map_init(SIZE_MAX, SIZE_MAX, hash_terribly);
    assert(m == NULL);
}

void test_map_with_buckets() {
    map *m = map_with_buckets(sizeof(char*), sizeof(char*), hash_terribly, 512);
    assert(map_buckets(m) == 512);
    map_free(m);
}

void test_map_with_buckets_fail() {
    map *m = map_with_buckets(sizeof(char*), sizeof(char*), hash_terribly, SIZE_MAX);
    assert(m == NULL);
}

void test_map_free() {
    map_free(NULL);

    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    map_free(m);
}

void test_map_max_load_factor() {
    map *m = map_with_buckets(sizeof(char*), sizeof(char*), hash_terribly, 1);
    assert(map_max_load_factor(m) == 1.0);
    map_free(m);
}

void test_map_set_max_load_factor() {
    map *m = map_with_buckets(sizeof(char*), sizeof(char*), hash_terribly, 1);
    assert(map_max_load_factor(m) == 1.0);

    map_set_max_load_factor(m, 2.01);
    assert(fequals(map_max_load_factor(m), 2.01));

    map_insert(m, "key1", "value1");
    map_insert(m, "key2", "value2");
    assert(fequals(map_load_factor(m), 1.0));
    assert(fequals(map_max_load_factor(m), 2.01));

    map_set_max_load_factor(m, 1.0);
    assert(fequals(map_load_factor(m), 0.5));
    assert(fequals(map_max_load_factor(m), 1.0));

    map_free(m);
}

void test_map_load_factor() {
    map *m = map_with_buckets(sizeof(char*), sizeof(char*), hash_terribly, 1);
    assert(map_buckets(m) == 1);
    assert(map_load_factor(m) == 0.0);

    map_insert(m, "key1", "value1");
    assert(map_length(m) == 1);
    assert(map_buckets(m) == 1);
    assert(map_load_factor(m) == 1.0);

    map_insert(m, "key2", "value2");
    assert(map_length(m) == 2);
    assert(map_buckets(m) == 2);
    assert(map_load_factor(m) == 1.0);

    map_insert(m, "key3", "value3");
    assert(map_length(m) == 3);
    assert(map_buckets(m) == 4);
    assert(map_load_factor(m) == 0.75);

    map_free(m);
}

void test_map_length() {
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_length(m) == 0);

    map_insert(m, "key1", "value1");
    map_insert(m, "key1", "value2");
    map_insert(m, "key1", "value3");
    assert(map_length(m) == 1);

    map_insert(m, "key1", "value1");
    map_insert(m, "key2", "value2");
    map_insert(m, "key3", "value3");
    assert(map_length(m) == 3);

    map_free(m);
}

void test_map_buckets() {
    map *m = map_with_buckets(sizeof(char*), sizeof(char*), hash_terribly, 1);
    assert(map_buckets(m) == 1);

    map_insert(m, "key1", "value1");
    assert(map_length(m) == 1);
    assert(map_buckets(m) == 1);

    map_insert(m, "key2", "value2");
    assert(map_length(m) == 2);
    assert(map_buckets(m) == 2);

    map_insert(m, "key3", "value3");
    assert(map_length(m) == 3);
    assert(map_buckets(m) == 4);

    map_free(m);
}

void test_map_is_empty() {
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_is_empty(m));

    map_insert(m, "key", "value");
    assert(!map_is_empty(m));

    map_erase(m, "key");
    assert(map_is_empty(m));

    map_free(m);
}

void test_map_clear() {
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_is_empty(m));

    map_insert(m, "key1", "value1");
    map_insert(m, "key2", "value2");
    assert(map_length(m) == 2);
    assert(strcmp(map_get(m, "key1"), "value1") == 0);
    assert(strcmp(map_get(m, "key2"), "value2") == 0);

    map_clear(m);
    assert(map_length(m) == 0);
    assert(map_get(m, "key1") == NULL);
    assert(map_get(m, "key2") == NULL);

    map_free(m);
}

void test_map_has() {
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(!map_has(m, "key1"));
    assert(!map_has(m, "key2"));
    assert(!map_has(m, "key3"));
    assert(!map_has(m, "key4"));

    map_insert(m, "key1", "value1");
    map_insert(m, "key2", "value2");
    map_insert(m, "key3", "value3");

    assert(map_has(m, "key1"));
    assert(map_has(m, "key2"));
    assert(map_has(m, "key3"));
    assert(!map_has(m, "key4"));

    map_free(m);
}

void test_map_find() {
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_find(m, "key") == NULL);

    map_insert(m, "key", "value");
    pair *entry = map_find(m, "key");
    assert(strcmp(pair_first(entry), "key") == 0);
    assert(strcmp(pair_second(entry), "value") == 0);

    map_free(m);
}

void test_map_get() {
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_get(m, "key") == NULL);

    map_insert(m, "key", "value");
    char *value = map_get(m, "key");
    assert(strcmp(value, "value") == 0);

    map_free(m);
}

void test_map_insert() {
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_length(m) == 0);

    pair *entry = map_find(m, "key1");
    assert(entry == NULL);

    pair *first_inserted = map_insert(m, "key1", "value");
    entry = map_find(m, "key1");
    assert(map_length(m) == 1);
    assert(first_inserted == entry);
    assert(strcmp(pair_first(first_inserted), "key1") == 0);
    assert(strcmp(pair_second(first_inserted), "value") == 0);

    pair *second_inserted = map_insert(m, "key1", "value");
    entry = map_find(m, "key1");
    assert(map_length(m) == 1);
    assert(second_inserted == entry);
    assert(second_inserted == first_inserted);
    assert(strcmp(pair_first(second_inserted), "key1") == 0);
    assert(strcmp(pair_second(second_inserted), "value") == 0);

    pair *third_inserted = map_insert(m, "key2", "value");
    entry = map_find(m, "key2");
    assert(map_length(m) == 2);
    assert(third_inserted != first_inserted);
    assert(third_inserted != second_inserted);
    assert(strcmp(pair_first(third_inserted), "key2") == 0);
    assert(strcmp(pair_second(third_inserted), "value") == 0);

    map_free(m);
}

void test_map_erase() {
    map *m = map_init(sizeof(char*), sizeof(char*), hash_terribly);
    assert(map_length(m) == 0);

    map_insert(m, "key1", "value1");
    map_insert(m, "key2", "value2");
    map_erase(m, "key3");
    map_erase(m, "key4");
    pair *first_entry = map_find(m, "key1");
    pair *second_entry = map_find(m, "key2");
    assert(map_length(m) == 2);
    assert(strcmp(pair_first(first_entry), "key1") == 0);
    assert(strcmp(pair_second(first_entry), "value1") == 0);
    assert(strcmp(pair_first(second_entry), "key2") == 0);
    assert(strcmp(pair_second(second_entry), "value2") == 0);

    map_erase(m, "key1");
    first_entry = map_find(m, "key1");
    second_entry = map_find(m, "key2");
    assert(map_length(m) == 1);
    assert(first_entry == NULL);
    assert(strcmp(pair_first(second_entry), "key2") == 0);
    assert(strcmp(pair_second(second_entry), "value2") == 0);

    map_erase(m, "key2");
    first_entry = map_find(m, "key1");
    second_entry = map_find(m, "key2");
    assert(map_length(m) == 0);
    assert(first_entry == NULL);
    assert(second_entry == NULL);

    map_erase(m, "key1");
    map_erase(m, "key2");
    map_erase(m, "key3");
    map_erase(m, "key4");
    assert(map_length(m) == 0);

    map_free(m);
}

void test_map_rehash() {
    map *m = map_with_buckets(sizeof(char*), sizeof(char*), hash_terribly, 10);
    assert(map_buckets(m) == 10);
    assert(map_length(m) == 0);

    map_rehash(m, 1);
    assert(map_buckets(m) == 1);
    assert(map_length(m) == 0);

    map_insert(m, "key1", "value1");
    assert(map_buckets(m) == 1);
    assert(map_length(m) == 1);

    map_insert(m, "key2", "value2");
    assert(map_buckets(m) == 2);
    assert(map_length(m) == 2);

    map_insert(m, "key3", "value3");
    assert(map_buckets(m) == 4);
    assert(map_length(m) == 3);

    map_rehash(m, 0);
    assert(map_buckets(m) == 3);
    assert(map_length(m) == 3);
    assert(strcmp(map_get(m, "key1"), "value1") == 0);
    assert(strcmp(map_get(m, "key2"), "value2") == 0);
    assert(strcmp(map_get(m, "key3"), "value3") == 0);

    map_rehash(m, 512);
    assert(map_buckets(m) == 512);
    assert(map_length(m) == 3);
    assert(strcmp(map_get(m, "key1"), "value1") == 0);
    assert(strcmp(map_get(m, "key2"), "value2") == 0);
    assert(strcmp(map_get(m, "key3"), "value3") == 0);

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
    test_map_load_factor();
    test_map_length();
    test_map_buckets();
    test_map_is_empty();
    test_map_clear();
    test_map_has();
    test_map_find();
    test_map_get();
    test_map_insert();
    test_map_erase();
    test_map_rehash();
}
