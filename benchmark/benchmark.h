#ifndef BENCHMARK_BENCHMARK_H_
#define BENCHMARK_BENCHMARK_H_

#define ITER_VECTOR_PUSH 100000000UL
#define ITER_VECTOR_POP 100000000UL

#include "../include/vector.h"

void bench_c_vector_push();
void bench_c_vector_pop();

void bench_cc_vector_push();
void bench_cc_vector_pop();

#endif // BENCHMARK_BENCHMARK_H_
