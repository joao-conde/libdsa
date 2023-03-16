#include <assert.h>
#include <stdint.h>

#include "../include/map.h"
#include "../include/pair.h"

void test_hash_int() {
    int key = 3;
    size_t hash = hash_int(&key);
    assert(key == hash);
    assert(hash == hash_int(&key));
}


void test_hash_str() {
    char *key = "hello world";
    size_t hash = hash_str(key);
    assert(hash == 6736);
    assert(hash == hash_str(key));
}


void test_map_init() {
    map *m = map_init(sizeof(int), sizeof(int), NULL);
    assert(map_is_empty(m));
    map_free(m);
}


void test_map_free() {
    map_free(NULL);

    map *m = map_init(sizeof(int), sizeof(int), NULL);
    map_free(m);
}


void test_map_length() {
    float value = 3.5;
    map *m = map_init(sizeof(float), sizeof(float), NULL);
    assert(map_length(m) == 0);

    map_insert(m, &value, &value);
    map_insert(m, &value, &value);
    map_insert(m, &value, &value);
    assert(map_length(m) == 3);

    map_free(m);
}


void test_map_is_empty() {
    map *m = map_init(sizeof(int), sizeof(int), NULL);
    assert(map_is_empty(m));

    int value = -10;
    map_insert(m, &value, &value);
    assert(!map_is_empty(m));

    map_erase(m, &value);
    assert(map_is_empty(m));

    map_free(m);
}


void test_map_has() {
    map *m = map_init(sizeof(char*), sizeof(char*), NULL);
    map_insert(m, "key1", "value1");
    map_insert(m, "key2", "value2");
    map_insert(m, "key3", "value3");

    assert(map_has(m, "key1"));
    assert(map_has(m, "key2"));
    assert(map_has(m, "key3"));
    assert(!map_has(m, "key4"));

    map_free(m);
}


void test_map_clear() {
    float value = 3.5;
    map *m = map_init(sizeof(float), sizeof(float), NULL);
    map_insert(m, &value, &value);
    map_insert(m, &value, &value);
    map_insert(m, &value, &value);
    assert(map_length(m) == 3);

    map_clear(m);
    assert(map_length(m) == 0);

    map_free(m);
}


void test_map_get() {
    map *m = map_init(sizeof(char*), sizeof(char*), NULL);
    map_insert(m, "key1", "value1");
    map_insert(m, "key2", "value2");
    map_insert(m, "key3", "value3");

    assert(strcmp(map_get(m, "key1"), "value1") == 0);
    assert(strcmp(map_get(m, "key2"), "value2") == 0);
    assert(strcmp(map_get(m, "key3"), "value3") == 0);
    assert(map_get(m, "key4") == NULL);

    map_free(m);
}


void test_map_insert() {
    pair *inserted;
    char *first, *second;
    map *m = map_init(sizeof(char*), sizeof(char*), NULL);
    assert(map_length(m) == 0);
    assert(!map_has(m, "key1"));
    assert(!map_has(m, "key2"));
    assert(!map_has(m, "key3"));

    inserted = map_insert(m, "key1", "value1");
    first = pair_first(inserted);
    second = pair_second(inserted);
    assert(strcmp(first, "key1") == 0);
    assert(strcmp(second, "value1") == 0);

    inserted = map_insert(m, "key2", "value2");
    first = pair_first(inserted);
    second = pair_second(inserted);
    assert(strcmp(first, "key2") == 0);
    assert(strcmp(second, "value2") == 0);

    assert(map_length(m) == 2);
    assert(map_has(m, "key1"));
    assert(map_has(m, "key2"));
    assert(!map_has(m, "key3"));

    map_free(m);
}


void test_map_erase() {
    map *m = map_init(sizeof(char*), sizeof(char*), NULL);
    map_insert(m, "key1", "value1");
    map_insert(m, "key2", "value2");
    map_insert(m, "key3", "value3");
    assert(map_length(m) == 3);
    assert(map_has(m, "key1"));
    assert(map_has(m, "key2"));
    assert(map_has(m, "key3"));

    map_erase(m, "key1");
    map_erase(m, "key2");
    map_erase(m, "unknown");
    assert(map_length(m) == 1);
    assert(!map_has(m, "key1"));
    assert(!map_has(m, "key2"));
    assert(map_has(m, "key3"));

    map_free(m);
}

void test_map() {
    test_hash_int();
    test_hash_str();
    test_map_init();
    test_map_free();
    test_map_length();
    test_map_is_empty();
    test_map_has();
    test_map_clear();
    test_map_get();
    test_map_insert();
    test_map_erase();
}
