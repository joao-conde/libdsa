#include <vector>

#include "benchmark.h"

void bcc_vector_push() {
    std::vector<size_t> v;
    for (size_t i = 0; i < VECTOR_LOAD_PUSH; i++) {
        v.push_back(i);
    }
}

void bcc_vector_push_pop() {
    std::vector<size_t> v;
    for (size_t i = 0; i < VECTOR_LOAD_PUSH; i++) {
        v.push_back(i);
    }
    for (size_t i = 0; i < VECTOR_LOAD_PUSH; i++) {
        v.pop_back();
    }
}

void bcc_vector_push_set() {
    std::vector<size_t> v;
    for (size_t i = 0; i < VECTOR_LOAD_PUSH; i++) {
        v.push_back(i);
        v.at(i) = i;
    }
}

void bcc_vector_push_resize() {
    std::vector<size_t> v;
    for (size_t i = 0; i < VECTOR_LOAD_PUSH; i++) {
        v.push_back(i);
    }
    v.resize(1);
}

void bcc_vector_insert() {
    std::vector<size_t> v;
    for (size_t i = 0; i < VECTOR_LOAD_INSERT; i++) {
        v.insert(v.begin(), i);
    }
}

void bcc_vector_insert_erase() {
    std::vector<size_t> v;
    for (size_t i = 0; i < VECTOR_LOAD_INSERT; i++) {
        v.insert(v.begin(), i);
    }
    for (size_t i = 0; i < VECTOR_LOAD_INSERT; i++) {
        v.erase(v.begin());
    }
}

void bcc_vector_push_at() {
    std::vector<size_t> v;
    for (size_t i = 0; i < VECTOR_LOAD_PUSH; i++) {
        v.push_back(i);
        size_t x = v.at(i);
    }
}

void bcc_vector_push_clear() {
    std::vector<size_t> v;
    for (size_t i = 0; i < VECTOR_LOAD_PUSH; i++) {
        v.push_back(i);
    }
    v.clear();
}
