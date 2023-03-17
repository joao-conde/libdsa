#ifndef BENCHMARKS_BENCHMARK_H_
#define BENCHMARKS_BENCHMARK_H_

#define ITER_VECTOR_PUSH 1000000000UL

#include "../include/vector.h"

void bench_c_vector_push();
void bench_cc_vector_push();

#endif // BENCHMARKS_BENCHMARK_H_
