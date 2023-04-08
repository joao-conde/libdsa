#include <stack>

#include "benchmark.h"

void* cc_stack_init() {
    std::stack<size_t> *s = new std::stack<size_t>();
    for (size_t i = 0; i < STACK_LOAD; i++) {
        s->push(i);
    }
    return s;
}

void cc_stack_free(void *data) {
    delete ((std::stack<size_t>*) data);
}

void cc_stack_push(void *data) {
    std::stack<size_t> *s = (std::stack<size_t>*) data;
    for (size_t i = 0; i < STACK_LOAD; i++) {
        s->push(i);
    }
}

void cc_stack_pop(void *data) {
    std::stack<size_t> *s = (std::stack<size_t>*) data;
    for (size_t i = 0; i < STACK_LOAD; i++) {
        s->pop();
    }
}
