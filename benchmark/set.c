#include "benchmark.h"

size_t c_set_hash(const void *value) {
    return *(size_t*) value;
}

void* c_set_init() {
    set *s = set_init(sizeof(size_t), c_set_hash);
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        set_insert(s, &i);
    }
    return s;
}

void c_set_free(void *data) {
    set_free((set*) data);
}

void c_set_insert(void *data) {
    set *s = (set*) data;
    for (size_t i = BENCH_LOAD; i < 2 * BENCH_LOAD; i++) {
        set_insert(s, &i);
    }
}

void c_set_erase(void *data) {
    set *s = (set*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        set_erase(s, &i);
    }
}

void c_set_has(void *data) {
    set *s = (set*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        bool x = set_has(s, &i);
    }
}

void c_set_clear(void *data) {
    set *s = (set*) data;
    set_clear(s);
}

void c_set_rehash(void *data) {
    set *s = (set*) data;
    set_rehash(s, 1);
}
