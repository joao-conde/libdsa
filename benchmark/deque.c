#include "benchmark.h"

void bc_deque_push_back() {
    deque *dq = deque_init(sizeof(size_t));
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_push_back(dq, &i);
    }
    deque_free(dq);
}

void bc_deque_push_front() {
    deque *dq = deque_init(sizeof(size_t));
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_push_front(dq, &i);
    }
    deque_free(dq);
}

void bc_deque_push_pop_back() {
    deque *dq = deque_init(sizeof(size_t));
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_push_back(dq, &i);
    }
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_pop_back(dq);
    }
    deque_free(dq);
}

void bc_deque_push_pop_front() {
    deque *dq = deque_init(sizeof(size_t));
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_push_front(dq, &i);
    }
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_pop_front(dq);
    }
    deque_free(dq);
}

void bc_deque_push_at() {
    deque *dq = deque_init(sizeof(size_t));
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_push_front(dq, &i);
        size_t *x = (size_t*) deque_at(dq, i);
    }
    deque_free(dq);
}

void bc_deque_push_clear() {
    deque *dq = deque_init(sizeof(size_t));
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_push_back(dq, &i);
    }
    deque_clear(dq);
    deque_free(dq);
}
