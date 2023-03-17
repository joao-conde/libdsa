#include "benchmark.h"

void bench_c_vector_push() {
    vector *v = vector_init(sizeof(int));
    for (size_t i = 0; i < ITER_VECTOR_PUSH; i++) {
        vector_push(v, &i);
    }
    vector_free(v);
}

void bench_c_vector_pop() {
    vector *v = vector_init(sizeof(int));
    for (size_t i = 0; i < ITER_VECTOR_PUSH; i++) {
        vector_push(v, &i);
    }
    for (size_t i = 0; i < ITER_VECTOR_POP; i++) {
        vector_pop(v);
    }
    vector_free(v);
}
