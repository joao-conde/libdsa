#include <algorithm>
#include <vector>

#include "benchmark.h"

void* cc_heap_init() {
    std::vector<size_t> *h = new std::vector<size_t>();
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        h->push_back(i);
    }
    std::make_heap(h->begin(), h->end());
    return h;
}

void cc_heap_free(void *data) {
    delete ((std::vector<size_t>*) data);
}

void cc_heap_top(void *data) {
    std::vector<size_t> *h = (std::vector<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        size_t top = h->at(0);
    }
}

void cc_heap_push(void *data) {
    std::vector<size_t> *h = (std::vector<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        h->push_back(i);
        std::push_heap(h->begin(),  h->end());
    }
}

void cc_heap_pop(void *data) {
    std::vector<size_t> *h = (std::vector<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        std::pop_heap(h->begin(),  h->end());
        h->pop_back();
    }
}

void cc_heap_clear(void *data) {
    std::vector<size_t> *h = (std::vector<size_t>*) data;
    h->clear();
}
