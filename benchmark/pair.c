#include "benchmark.h"

void* c_pair_init() {
    char const *first = "first";
    char const *second = "second";
    pair *p = pair_init(&first, &second, sizeof(char*), sizeof(char*));
    return p;
}

void c_pair_free(void *data) {
    pair_free((pair*) data);
}

void c_pair_first(void *data) {
    pair *p = (pair*) data;
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        char *first = (char*) pair_first(p);
    }
}

void c_pair_second(void *data) {
    pair *p = (pair*) data;
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        char *second = (char*) pair_second(p);
    }
}

void c_pair_set_first(void *data) {
    pair *p = (pair*) data;
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        char const *key = "key";
        pair_set_first(p, &key);
    }
}

void c_pair_set_second(void *data) {
    pair *p = (pair*) data;
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        char const *value = "value";
        pair_set_second(p, &value);
    }
}
