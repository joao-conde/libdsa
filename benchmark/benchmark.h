#ifndef BENCHMARK_BENCHMARK_H_
#define BENCHMARK_BENCHMARK_H_

#include <iostream>

#include "../include/dsa.h"

#define DEQUE_LOAD 10000000UL
#define LIST_LOAD 1000000UL
#define MAP_LOAD 1000000UL
#define PAIR_LOAD 1000000UL
#define QUEUE_LOAD 1000000UL
#define STACK_LOAD 1000000UL
#define VECTOR_LOAD_PUSH 1000000UL
#define VECTOR_LOAD_INSERT 100000UL

#define TABLE_WIDTH 20
#define SEPARATOR ","

int64_t benchmark(void* (init)(), void (free)(void*), void (fn)(void*));
void print_benchmark_header();
void print_benchmark(
    std::string name,
    void* (c_init)(),
    void (c_free)(void*),
    void (c_fn)(void*),
    void* (cc_init)(),
    void (cc_free)(void*),
    void (cc_fn)(void*));

void* bc_deque_init();
void bc_deque_free(void *data);
void bc_deque_push_back(void *data);
void bc_deque_push_front(void *data);
void bc_deque_pop_back(void *data);
void bc_deque_pop_front(void *data);
void bc_deque_at(void *data);
void bc_deque_clear(void *data);
void bc_list_push_back();
void bc_list_push_front();
void bc_list_push_pop_back();
void bc_list_push_pop_front();
void bc_list_insert();
void bc_list_insert_erase();
void bc_list_push_clear();
void bc_map_insert();
void bc_map_insert_erase();
void bc_map_insert_get();
void bc_map_insert_clear();
void bc_map_insert_rehash();
void bc_pair_first();
void bc_pair_second();
void bc_pair_set_first();
void bc_pair_set_second();
void bc_queue_push();
void bc_queue_push_pop();
void bc_queue_push_clear();
void bc_stack_push();
void bc_stack_push_pop();
void bc_vector_push();
void bc_vector_push_pop();
void bc_vector_push_set();
void bc_vector_push_resize();
void bc_vector_insert();
void bc_vector_insert_erase();
void bc_vector_push_at();
void bc_vector_push_clear();

void* bcc_deque_init();
void bcc_deque_free(void *data);
void bcc_deque_push_back(void *data);
void bcc_deque_push_front(void *data);
void bcc_deque_pop_back(void *data);
void bcc_deque_pop_front(void *data);
void bcc_deque_at(void *data);
void bcc_deque_clear(void *data);
void bcc_list_push_back();
void bcc_list_push_front();
void bcc_list_push_pop_back();
void bcc_list_push_pop_front();
void bcc_list_insert();
void bcc_list_insert_erase();
void bcc_list_push_clear();
void bcc_map_insert();
void bcc_map_insert_erase();
void bcc_map_insert_get();
void bcc_map_insert_clear();
void bcc_map_insert_rehash();
void bcc_pair_first();
void bcc_pair_second();
void bcc_pair_set_first();
void bcc_pair_set_second();
void bcc_queue_push();
void bcc_queue_push_pop();
void bcc_queue_push_clear();
void bcc_stack_push();
void bcc_stack_push_pop();
void bcc_vector_push();
void bcc_vector_push_pop();
void bcc_vector_push_set();
void bcc_vector_push_resize();
void bcc_vector_insert();
void bcc_vector_insert_erase();
void bcc_vector_push_at();
void bcc_vector_push_clear();

#endif // BENCHMARK_BENCHMARK_H_
