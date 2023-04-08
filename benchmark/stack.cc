#include <stack>

#include "benchmark.h"

void* bcc_stack_init() {
    std::stack<size_t> *s = new std::stack<size_t>();
    for (size_t i = 0; i < STACK_LOAD; i++) {
        s->push(i);
    }
    return s;
}

void bcc_stack_free(void *data) {
    free((std::stack<size_t>*) data);
}

void bcc_stack_push(void *data) {
    std::stack<size_t> *s = (std::stack<size_t>*) data;
    for (size_t i = 0; i < STACK_LOAD; i++) {
        s->push(i);
    }
}

void bcc_stack_pop(void *data) {
    std::stack<size_t> *s = (std::stack<size_t>*) data;
    for (size_t i = 0; i < STACK_LOAD; i++) {
        s->pop();
    }
}
