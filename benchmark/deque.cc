#include <deque>

#include "benchmark.h"

void bcc_deque_push_back() {
    std::deque<size_t> dq;
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        dq.push_back(i);
    }
}

void bcc_deque_push_front() {
    std::deque<size_t> dq;
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        dq.push_front(i);
    }
}

void bcc_deque_push_pop_back() {
    std::deque<size_t> dq;
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        dq.push_back(i);
    }
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        dq.pop_back();
    }
}

void bcc_deque_push_pop_front() {
    std::deque<size_t> dq;
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        dq.push_front(i);
    }
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        dq.pop_front();
    }
}

void bcc_deque_push_at() {
    std::deque<size_t> dq;
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        dq.push_front(i);
        size_t x = dq.at(i);
    }
}

void bcc_deque_push_clear() {
    std::deque<size_t> dq;
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        dq.push_back(i);
    }
    dq.clear();
}
