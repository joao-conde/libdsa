#include "benchmark.h"

void bc_pair_first() {
    pair *p = pair_init("first", "second", sizeof(char*), sizeof(char*));
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        char *first = (char*) pair_first(p);
    }
    pair_free(p);
}

void bc_pair_second() {
    pair *p = pair_init("first", "second", sizeof(char*), sizeof(char*));
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        char *second = (char*) pair_second(p);
    }
    pair_free(p);
}

void bc_pair_set_first() {
    pair *p = pair_init("first", "second", sizeof(char*), sizeof(char*));
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        pair_set_first(p, "key");
    }
    pair_free(p);
}

void bc_pair_set_second() {
    pair *p = pair_init("first", "second", sizeof(char*), sizeof(char*));
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        pair_set_second(p, "value");
    }
    pair_free(p);
}
