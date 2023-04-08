#include "benchmark.h"

void* bc_stack_init() {
    stack *s = stack_init(sizeof(size_t));
    for (size_t i = 0; i < STACK_LOAD; i++) {
        stack_push(s, &i);
    }
    return s;
}

void bc_stack_free(void *data) {
    stack_free((stack*) data);
}

void bc_stack_push(void *data) {
    stack *s = (stack*) data;
    for (size_t i = 0; i < STACK_LOAD; i++) {
        stack_push(s, &i);
    }
}

void bc_stack_pop(void *data) {
    stack *s = (stack*) data;
    for (size_t i = 0; i < STACK_LOAD; i++) {
        stack_pop(s);
    }
}
