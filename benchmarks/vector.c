#include "benchmark.h"

void bench_c_vector_push() {
    vector *v = vector_init(sizeof(int));
    for (size_t i = 0; i < ITER_VECTOR_PUSH; i++) {
        vector_push(v, &i);
    }
    vector_free(v);
}
