#include "benchmark.h"

void* c_stack_init() {
    stack *s = stack_init(sizeof(size_t));
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        stack_push(s, &i);
    }
    return s;
}

void c_stack_free(void *data) {
    stack_free((stack*) data);
}

void c_stack_push(void *data) {
    stack *s = (stack*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        stack_push(s, &i);
    }
}

void c_stack_pop(void *data) {
    stack *s = (stack*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        stack_pop(s);
    }
}
