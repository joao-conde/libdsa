#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "test.h"

#include "../include/set.h"

void test_set_init() {
    set *s = set_init(sizeof(int), hash_terribly);
    set_free(s);
}

void test_set_init_fail() {
    set *s = set_init(SIZE_MAX, hash_terribly);
    assert(s == NULL);
}

void test_set_with_buckets() {
    set *s = set_with_buckets(sizeof(int), hash_terribly, 512);
    assert(set_buckets(s) == 512);
    set_free(s);
}

void test_set_with_buckets_fail() {
    set *s = set_with_buckets(sizeof(int), hash_terribly, SIZE_MAX / 10000);
    assert(s == NULL);
}

void test_set_free() {
    set_free(NULL);

    set *s = set_init(sizeof(int), hash_terribly);
    set_free(s);
}

void test_set_max_load_factor() {
    set *s = set_init(sizeof(int), hash_terribly);
    assert(set_max_load_factor(s) == 1.0);
    set_free(s);
}

void test_set_set_max_load_factor() {
    char *value1 = "value1";
    char *value2 = "value2";
    set *s = set_with_buckets(sizeof(char*), hash_terribly, 1);
    assert(set_max_load_factor(s) == 1.0);

    set_set_max_load_factor(s, 2.01);
    assert(fequals(set_max_load_factor(s), 2.01));

    set_insert(s, &value1);
    set_insert(s, &value2);
    assert(fequals(set_load_factor(s), 1.0));
    assert(fequals(set_max_load_factor(s), 2.01));

    set_set_max_load_factor(s, 1.0);
    assert(fequals(set_load_factor(s), 0.5));
    assert(fequals(set_max_load_factor(s), 1.0));

    set_free(s);
}

void test_set_load_factor() {
    char *value1 = "value1";
    char *value2 = "value2";
    char *value3 = "value3";
    set *s = set_with_buckets(sizeof(char*), hash_terribly, 1);
    assert(set_buckets(s) == 1);
    assert(set_load_factor(s) == 0.0);

    set_insert(s, &value1);
    assert(set_size(s) == 1);
    assert(set_buckets(s) == 1);
    assert(set_load_factor(s) == 1.0);

    set_insert(s, &value2);
    assert(set_size(s) == 2);
    assert(set_buckets(s) == 2);
    assert(set_load_factor(s) == 1.0);

    set_insert(s, &value3);
    assert(set_size(s) == 3);
    assert(set_buckets(s) == 4);
    assert(set_load_factor(s) == 0.75);

    set_free(s);
}

void test_set_size() {
    char *value1 = "value1";
    char *value2 = "value2";
    char *value3 = "value3";
    set *s = set_init(sizeof(char*), hash_terribly);
    assert(set_size(s) == 0);

    set_insert(s, &value1);
    set_insert(s, &value1);
    set_insert(s, &value1);
    assert(set_size(s) == 1);

    set_insert(s, &value1);
    set_insert(s, &value2);
    set_insert(s, &value3);
    assert(set_size(s) == 3);

    set_free(s);
}

void test_set_buckets() {
    char *value1 = "value1";
    char *value2 = "value2";
    char *value3 = "value3";
    set *s = set_with_buckets(sizeof(char*), hash_terribly, 1);
    assert(set_buckets(s) == 1);

    set_insert(s, &value1);
    assert(set_size(s) == 1);
    assert(set_buckets(s) == 1);

    set_insert(s, &value2);
    assert(set_size(s) == 2);
    assert(set_buckets(s) == 2);

    set_insert(s, &value3);
    assert(set_size(s) == 3);
    assert(set_buckets(s) == 4);

    set_free(s);
}

void test_set_empty() {
    char *value = "value";
    set *s = set_init(sizeof(char*), hash_terribly);
    assert(set_empty(s));

    set_insert(s, &value);
    assert(!set_empty(s));

    set_erase(s, &value);
    assert(set_empty(s));

    set_free(s);
}

void test_set_clear() {
    char *value1 = "value1";
    char *value2 = "value2";
    set *s = set_init(sizeof(char*), hash_terribly);
    assert(set_empty(s));

    set_insert(s, &value1);
    set_insert(s, &value2);
    assert(set_size(s) == 2);
    assert(set_has(s, &value1));
    assert(set_has(s, &value2));

    set_clear(s);
    assert(set_size(s) == 0);
    assert(!set_has(s, &value1));
    assert(!set_has(s, &value2));

    set_free(s);
}

void test_set_has() {
    char *value1 = "value1";
    char *value2 = "value2";
    char *value3 = "value3";
    char *value4 = "value4";
    set *s = set_init(sizeof(char*), hash_terribly);
    assert(!set_has(s, &value1));
    assert(!set_has(s, &value2));
    assert(!set_has(s, &value3));
    assert(!set_has(s, &value4));

    set_insert(s, &value1);
    set_insert(s, &value2);
    set_insert(s, &value3);

    assert(set_has(s, &value1));
    assert(set_has(s, &value2));
    assert(set_has(s, &value3));
    assert(!set_has(s, &value4));

    set_free(s);
}

void test_set_insert() {
    char *value1 = "value1";
    char *value2 = "value2";
    set *s = set_init(sizeof(char*), hash_terribly);
    assert(set_size(s) == 0);
    assert(!set_has(s, &value1));
    assert(!set_has(s, &value2));

    void *first_inserted = set_insert(s, &value1);
    assert(set_size(s) == 1);
    assert(strcmp(*(char**) first_inserted, "value1") == 0);

    void *second_inserted = set_insert(s, &value1);
    assert(set_size(s) == 1);
    assert(second_inserted == first_inserted);
    assert(strcmp(*(char**) second_inserted, "value1") == 0);

    void *third_inserted = set_insert(s, &value2);
    assert(set_size(s) == 2);
    assert(third_inserted != first_inserted);
    assert(third_inserted != second_inserted);
    assert(strcmp(*(char**) third_inserted, "value2") == 0);

    set_free(s);
}

void test_set_erase() {
    char *value1 = "value1";
    char *value2 = "value2";
    char *value3 = "value3";
    char *value4 = "value4";
    set *s = set_init(sizeof(char*), hash_terribly);
    assert(set_size(s) == 0);

    set_insert(s, &value1);
    set_insert(s, &value2);
    set_erase(s, &value3);
    set_erase(s, &value4);
    assert(set_size(s) == 2);

    set_erase(s, &value1);
    assert(set_size(s) == 1);
    assert(!set_has(s, &value1));

    set_erase(s, &value2);
    assert(set_size(s) == 0);
    assert(!set_has(s, &value1));
    assert(!set_has(s, &value2));

    set_erase(s, &value1);
    set_erase(s, &value2);
    set_erase(s, &value3);
    set_erase(s, &value4);
    assert(set_size(s) == 0);

    set_free(s);
}

void test_set_rehash() {
    char *value1 = "value1";
    char *value2 = "value2";
    char *value3 = "value3";
    set *s = set_with_buckets(sizeof(char*), hash_terribly, 10);
    assert(set_buckets(s) == 10);
    assert(set_size(s) == 0);

    set_rehash(s, 1);
    assert(set_buckets(s) == 1);
    assert(set_size(s) == 0);

    set_insert(s, &value1);
    assert(set_buckets(s) == 1);
    assert(set_size(s) == 1);

    set_insert(s, &value2);
    assert(set_buckets(s) == 2);
    assert(set_size(s) == 2);

    set_insert(s, &value3);
    assert(set_buckets(s) == 4);
    assert(set_size(s) == 3);

    set_rehash(s, 0);
    assert(set_buckets(s) == 4);
    assert(set_size(s) == 3);
    assert(set_has(s, &value1));
    assert(set_has(s, &value2));
    assert(set_has(s, &value3));

    set_rehash(s, 512);
    assert(set_buckets(s) == 512);
    assert(set_size(s) == 3);
    assert(set_has(s, &value1));
    assert(set_has(s, &value2));
    assert(set_has(s, &value3));

    set_free(s);
}

void test_set_load() {
    bool has, empty;
    size_t size;
    float max_load_factor, load_factor;
    size_t *inserted;

    set *s = set_init(sizeof(size_t), hash_int);

    for (size_t i = 0; i < TEST_LOAD; i++) {
        inserted = set_insert(s, &i);
        size = set_size(s);
        empty = set_empty(s);
        has = set_has(s, &i);
        load_factor = set_load_factor(s);
        max_load_factor = set_max_load_factor(s);
        assert(*(size_t*) inserted == i);
        assert(size == i + 1);
        assert(!empty);
        assert(has);
        assert(load_factor <= max_load_factor);
    }

    for (size_t i = 0; i < TEST_LOAD / 2; i++) {
        set_erase(s, &i);
        size = set_size(s);
        empty = set_empty(s);
        has = set_has(s, &i);
        load_factor = set_load_factor(s);
        max_load_factor = set_max_load_factor(s);
        assert(size == TEST_LOAD - i - 1);
        assert(!empty);
        assert(!has);
        assert(load_factor <= max_load_factor);
    }

    set_clear(s);
    size = set_size(s);
    empty = set_empty(s);
    assert(size == 0);
    assert(empty);

    set_free(s);
}

void test_set() {
    test_set_init();
    test_set_init_fail();
    test_set_with_buckets();
    test_set_with_buckets_fail();
    test_set_free();
    test_set_max_load_factor();
    test_set_set_max_load_factor();
    test_set_load_factor();
    test_set_size();
    test_set_buckets();
    test_set_empty();
    test_set_clear();
    test_set_has();
    test_set_insert();
    test_set_erase();
    test_set_rehash();
    test_set_load();
}
