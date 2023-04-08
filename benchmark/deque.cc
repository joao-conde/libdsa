#include <deque>

#include "benchmark.h"

void* cc_deque_init() {
    std::deque<size_t> *dq = new std::deque<size_t>();
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        dq->push_back(i);
    }
    return dq;
}

void cc_deque_free(void *data) {
    delete ((std::deque<size_t>*) data);
}

void cc_deque_push_back(void *data) {
    std::deque<size_t> *dq = (std::deque<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        dq->push_back(i);
    }
}

void cc_deque_push_front(void *data) {
    std::deque<size_t> *dq = (std::deque<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        dq->push_front(i);
    }
}

void cc_deque_pop_back(void *data) {
    std::deque<size_t> *dq = (std::deque<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        dq->pop_back();
    }
}

void cc_deque_pop_front(void *data) {
    std::deque<size_t> *dq = (std::deque<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        dq->pop_front();
    }
}

void cc_deque_at(void *data) {
    std::deque<size_t> *dq = (std::deque<size_t>*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        size_t x = dq->at(i);
    }
}

void cc_deque_clear(void *data) {
    std::deque<size_t> *dq = (std::deque<size_t>*) data;
    dq->clear();
}
