#include "benchmark.h"

void bc_stack_push() {
    stack *s = stack_init(sizeof(size_t));
    for (size_t i = 0; i < STACK_LOAD; i++) {
        stack_push(s, &i);
    }
    stack_free(s);
}

void bc_stack_push_pop() {
    stack *s = stack_init(sizeof(size_t));
    for (size_t i = 0; i < STACK_LOAD; i++) {
        stack_push(s, &i);
    }
    for (size_t i = 0; i < STACK_LOAD; i++) {
        stack_pop(s);
    }
    stack_free(s);
}
