#include <list>

#include "benchmark.h"

void* cc_list_init() {
    std::list<size_t> *l = new std::list<size_t>();
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        l->push_back(i);
    }
    return l;
}

void cc_list_free(void *data) {
    delete ((std::list<size_t>*) data);
}

void cc_list_push_back(void *data) {
    std::list<size_t> *l = (std::list<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        l->push_back(i);
    }
}

void cc_list_push_front(void *data) {
    std::list<size_t> *l = (std::list<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        l->push_front(i);
    }
}

void cc_list_pop_back(void *data) {
    std::list<size_t> *l = (std::list<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        l->pop_back();
    }
}

void cc_list_pop_front(void *data) {
    std::list<size_t> *l = (std::list<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        l->pop_front();
    }
}

void cc_list_insert(void *data) {
    std::list<size_t> *l = (std::list<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        l->insert(l->begin(), i);
    }
}

void cc_list_erase(void *data) {
    std::list<size_t> *l = (std::list<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        l->erase(l->begin());
    }
}

void cc_list_clear(void *data) {
    std::list<size_t> *l = (std::list<size_t>*) data;
    l->clear();
}
