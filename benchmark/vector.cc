#include <vector>

#include "benchmark.h"

void* cc_vector_init() {
    std::vector<size_t> *v = new std::vector<size_t>();
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        v->push_back(i);
    }
    return v;
}

void cc_vector_free(void *data) {
    delete ((std::vector<size_t>*) data);
}

void cc_vector_push(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        v->push_back(i);
    }
}

void cc_vector_pop(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        v->pop_back();
    }
}

void cc_vector_set(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        v->at(i) = i;
    }
}

void cc_vector_resize(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    v->resize(1);
}

void cc_vector_insert(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    size_t size = v->size();
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        v->insert(v->begin() + size + i, i);
    }
}

void cc_vector_erase(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    size_t size = v->size();
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        v->erase(v->begin() + size - 1 - i);
    }
}

void cc_vector_at(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        size_t x = v->at(i);
    }
}

void cc_vector_clear(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    v->clear();
}
