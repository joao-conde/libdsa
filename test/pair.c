#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "../include/pair.h"

#define MAX_VAL_SIZE 10
#define TEST_LOAD 100000

void test_pair_size() {
    assert(PAIR_SIZE == 32);
}

void test_pair_init() {
    int first = 1;
    char *second = "value";

    pair *p = pair_init(&first, second, sizeof(int), MAX_VAL_SIZE);
    assert(p != NULL);

    pair_free(p);
}

void test_pair_init_fail() {
    int x = 1;
    pair *p = pair_init(&x, &x, PTRDIFF_MAX, PTRDIFF_MAX);
    assert(p == NULL);
}

void test_pair_free() {
    pair_free(NULL);

    int first = 1;
    char *second = "value";
    pair *p = pair_init(&first, second, sizeof(int), MAX_VAL_SIZE);
    pair_free(p);
}

void test_pair_first() {
    int first = 1;
    char *second = "value";
    pair *p = pair_init(&first, second, sizeof(int), MAX_VAL_SIZE);

    assert(*(int*)pair_first(p) == first);

    pair_free(p);
}

void test_pair_second() {
    int first = 1;
    char *second = "value";
    pair *p = pair_init(&first, second, sizeof(int), MAX_VAL_SIZE);
    assert(strcmp(pair_second(p), "value") == 0);

    pair_free(p);
}

void test_pair_set_first() {
    pair *p = pair_init("first", "second", MAX_VAL_SIZE, MAX_VAL_SIZE);
    assert(strcmp(pair_first(p), "first") == 0);

    pair_set_first(p, "changed");
    assert(strcmp(pair_first(p), "changed") == 0);

    pair_free(p);
}

void test_pair_set_second() {
    pair *p = pair_init("first", "second", MAX_VAL_SIZE, MAX_VAL_SIZE);
    assert(strcmp(pair_second(p), "second") == 0);

    pair_set_second(p, "changed");
    assert(strcmp(pair_second(p), "changed") == 0);

    pair_free(p);
}

void test_pair_load() {
    int *first, *second;
    for (int i = 0; i < TEST_LOAD; i++) {
        pair *p = pair_init(&i, &i, sizeof(int), sizeof(int));
        first = pair_first(p);
        second = pair_second(p);
        assert(*first == i);
        assert(*second == i);
        pair_free(p);
    }
}

void test_pair() {
    test_pair_size();
    test_pair_init();
    test_pair_init_fail();
    test_pair_free();
    test_pair_first();
    test_pair_second();
    test_pair_set_first();
    test_pair_set_second();
    test_pair_load();
}
