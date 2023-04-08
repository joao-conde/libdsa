#include <vector>

#include "benchmark.h"

void* bcc_vector_init() {
    std::vector<size_t> *v = new std::vector<size_t>();
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        v->push_back(i);
    }
    return v;
}

void bcc_vector_free(void *data) {
    delete ((std::vector<size_t>*) data);
}

void bcc_vector_push(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        v->push_back(i);
    }
}

void bcc_vector_pop(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        v->pop_back();
    }
}

void bcc_vector_set(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        v->at(i) = i;
    }
}

void bcc_vector_resize(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    v->resize(1);
}

void bcc_vector_insert(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    size_t size = v->size();
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        v->insert(v->begin() + size + i, i);
    }
}

void bcc_vector_erase(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    size_t size = v->size();
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        v->erase(v->begin() + size - 1 - i);
    }
}

void bcc_vector_at(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        size_t x = v->at(i);
    }
}

void bcc_vector_clear(void *data) {
    std::vector<size_t> *v = (std::vector<size_t>*) data;
    v->clear();
}
