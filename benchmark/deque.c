#include "benchmark.h"

void* bc_deque_init() {
    deque *dq = deque_init(sizeof(size_t));
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_push_back(dq, &i);
    }
    return dq;
}

void bc_deque_free(void *data) {
    deque_free((deque*) data);
}

void bc_deque_push_back(void *data) {
    deque *dq = (deque*) data;
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_push_back(dq, &i);
    }
}

void bc_deque_push_front(void *data) {
    deque *dq = (deque*) data;
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_push_front(dq, &i);
    }
}

void bc_deque_pop_back(void *data) {
    deque *dq = (deque*) data;
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_pop_back(dq);
    }
}

void bc_deque_pop_front(void *data) {
    deque *dq = (deque*) data;
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        deque_pop_front(dq);
    }
}

void bc_deque_at(void *data) {
    deque *dq = (deque*) data;
    for (size_t i = 0; i < DEQUE_LOAD; i++) {
        size_t *x = (size_t*) deque_at(dq, i);
    }
}

void bc_deque_clear(void *data) {
    deque *dq = (deque*) data;
    deque_clear(dq);
}
