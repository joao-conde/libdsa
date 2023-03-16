#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "../include/pair.h"

void test_pair_size() {
    assert(PAIR_SIZE);
}


void test_pair_init() {
    int first = 1;
    char *second = "value";

    pair *p = pair_init(&first, second, sizeof(int), sizeof(char*));
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
    pair *p = pair_init(&first, second, sizeof(int), sizeof(char*));
    pair_free(p);
}


void test_pair_first() {
    int first = 1;
    char *second = "value";
    pair *p = pair_init(&first, second, sizeof(int), sizeof(char*));

    assert(*(int*)pair_first(p) == first);

    pair_free(p);
}


void test_pair_second() {
    int first = 1;
    char *second = "value";
    pair *p = pair_init(&first, second, sizeof(int), sizeof(char*));
    assert(strcmp(pair_second(p), "value") == 0);

    pair_free(p);
}


void test_pair_stress() {
    int nelements = 100000;
    int *first, *second;
    for (int i = 0; i < nelements; i++) {
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
    test_pair_stress();
}
