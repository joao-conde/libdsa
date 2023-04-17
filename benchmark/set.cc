#include <unordered_set>

#include "benchmark.h"

void* cc_set_init() {
    std::unordered_set<size_t> *s = new std::unordered_set<size_t>();
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        s->insert(i);
    }
    return s;
}

void cc_set_free(void *data) {
    delete ((std::unordered_set<size_t>*) data);
}

void cc_set_insert(void *data) {
    std::unordered_set<size_t> *s = (std::unordered_set<size_t>*) data;
    for (size_t i = BENCH_LOAD; i < 2 * BENCH_LOAD; i++) {
        s->insert(i);
    }
}

void cc_set_erase(void *data) {
    std::unordered_set<size_t> *s = (std::unordered_set<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        s->erase(i);
    }
}

void cc_set_has(void *data) {
    std::unordered_set<size_t> *s = (std::unordered_set<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        bool x = s->find(i) != s->end();
    }
}

void cc_set_clear(void *data) {
    std::unordered_set<size_t> *s = (std::unordered_set<size_t>*) data;
    s->clear();
}

void cc_set_rehash(void *data) {
    std::unordered_set<size_t> *s = (std::unordered_set<size_t>*) data;
    s->rehash(1);
}
