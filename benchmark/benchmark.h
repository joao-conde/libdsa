#ifndef BENCHMARK_BENCHMARK_H_
#define BENCHMARK_BENCHMARK_H_

#include <iostream>

#include "../include/dsa.h"

#define DEQUE_LOAD 1000000UL
#define LIST_LOAD 1000000UL
#define MAP_LOAD 1000000UL
#define PAIR_LOAD 1000000UL
#define QUEUE_LOAD 1000000UL
#define STACK_LOAD 1000000UL
#define VECTOR_LOAD 1000000UL

#define TABLE_WIDTH 20
#define SEPARATOR ","

int64_t benchmark(void* (init_fn)(), void (free_fn)(void*), void (fn)(void*));
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

void* bc_list_init();
void bc_list_free(void *data);
void bc_list_push_back(void *data);
void bc_list_push_front(void *data);
void bc_list_pop_back(void *data);
void bc_list_pop_front(void *data);
void bc_list_insert(void *data);
void bc_list_erase(void *data);
void bc_list_clear(void *data);

void* bc_map_init();
void bc_map_free(void *data);
void bc_map_insert(void *data);
void bc_map_erase(void *data);
void bc_map_get(void *data);
void bc_map_clear(void *data);
void bc_map_rehash(void *data);

void* bc_pair_init();
void bc_pair_free(void *data);
void bc_pair_first(void *data);
void bc_pair_second(void *data);
void bc_pair_set_first(void *data);
void bc_pair_set_second(void *data);

void* bc_queue_init();
void bc_queue_free(void *data);
void bc_queue_push(void *data);
void bc_queue_pop(void *data);
void bc_queue_clear(void *data);

void* bc_stack_init();
void bc_stack_free(void *data);
void bc_stack_push(void *data);
void bc_stack_pop(void *data);

void* bc_vector_init();
void bc_vector_free(void *data);
void bc_vector_push(void *data);
void bc_vector_pop(void *data);
void bc_vector_set(void *data);
void bc_vector_resize(void *data);
void bc_vector_insert(void *data);
void bc_vector_erase(void *data);
void bc_vector_at(void *data);
void bc_vector_clear(void *data);

void* bcc_deque_init();
void bcc_deque_free(void *data);
void bcc_deque_push_back(void *data);
void bcc_deque_push_front(void *data);
void bcc_deque_pop_back(void *data);
void bcc_deque_pop_front(void *data);
void bcc_deque_at(void *data);
void bcc_deque_clear(void *data);

void* bcc_list_init();
void bcc_list_free(void *data);
void bcc_list_push_back(void *data);
void bcc_list_push_front(void *data);
void bcc_list_pop_back(void *data);
void bcc_list_pop_front(void *data);
void bcc_list_insert(void *data);
void bcc_list_erase(void *data);
void bcc_list_clear(void *data);

void* bcc_map_init();
void bcc_map_free(void *data);
void bcc_map_insert(void *data);
void bcc_map_erase(void *data);
void bcc_map_get(void *data);
void bcc_map_clear(void *data);
void bcc_map_rehash(void *data);

void* bcc_pair_init();
void bcc_pair_free(void *data);
void bcc_pair_first(void *data);
void bcc_pair_second(void *data);
void bcc_pair_set_first(void *data);
void bcc_pair_set_second(void *data);

void* bcc_queue_init();
void bcc_queue_free(void *data);
void bcc_queue_push(void *data);
void bcc_queue_pop(void *data);
void bcc_queue_clear(void *data);

void* bcc_stack_init();
void bcc_stack_free(void *data);
void bcc_stack_push(void *data);
void bcc_stack_pop(void *data);

void* bcc_vector_init();
void bcc_vector_free(void *data);
void bcc_vector_push(void *data);
void bcc_vector_pop(void *data);
void bcc_vector_set(void *data);
void bcc_vector_resize(void *data);
void bcc_vector_insert(void *data);
void bcc_vector_erase(void *data);
void bcc_vector_at(void *data);
void bcc_vector_clear(void *data);

#endif // BENCHMARK_BENCHMARK_H_
