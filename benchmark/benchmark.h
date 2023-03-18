#ifndef BENCHMARK_BENCHMARK_H_
#define BENCHMARK_BENCHMARK_H_

#define VECTOR_PUSHES 100000000UL
#define VECTOR_INSERTS 100000UL

#define TABLE_WIDTH 20

#include <iostream>

#include "../include/vector.h"

int64_t benchmark(void (fn)());
void print_benchmark_header();
void print_benchmark(std::string name, void (c_fn)(), void (cc_fn)());

void bc_vector_push();
void bc_vector_push_pop();
void bc_vector_push_clear();
void bc_vector_push_at();
void bc_vector_push_set();
void bc_vector_push_resize();
void bc_vector_insert();
void bc_vector_insert_erase();

void bcc_vector_push();
void bcc_vector_push_pop();
void bcc_vector_push_clear();
void bcc_vector_push_at();
void bcc_vector_push_set();
void bcc_vector_push_resize();
void bcc_vector_insert();
void bcc_vector_insert_erase();

#endif // BENCHMARK_BENCHMARK_H_
