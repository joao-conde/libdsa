#ifndef BENCHMARK_BENCHMARK_H_
#define BENCHMARK_BENCHMARK_H_

#include <iostream>

#include "../include/dsa.h"

extern size_t BENCH_LOAD;

#define TABLE_WIDTH 20
#define TABLE_SEPARATOR ","

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

void* c_deque_init();
void c_deque_free(void *data);
void c_deque_push_back(void *data);
void c_deque_push_front(void *data);
void c_deque_pop_back(void *data);
void c_deque_pop_front(void *data);
void c_deque_at(void *data);
void c_deque_clear(void *data);

void* c_list_init();
void c_list_free(void *data);
void c_list_push_back(void *data);
void c_list_push_front(void *data);
void c_list_pop_back(void *data);
void c_list_pop_front(void *data);
void c_list_insert(void *data);
void c_list_erase(void *data);
void c_list_clear(void *data);

void* c_map_init();
void c_map_free(void *data);
void c_map_insert(void *data);
void c_map_erase(void *data);
void c_map_get(void *data);
void c_map_clear(void *data);
void c_map_rehash(void *data);

void* c_pair_init();
void c_pair_free(void *data);
void c_pair_first(void *data);
void c_pair_second(void *data);
void c_pair_set_first(void *data);
void c_pair_set_second(void *data);

void* c_queue_init();
void c_queue_free(void *data);
void c_queue_push(void *data);
void c_queue_pop(void *data);
void c_queue_clear(void *data);

void* c_stack_init();
void c_stack_free(void *data);
void c_stack_push(void *data);
void c_stack_pop(void *data);

void* c_vector_init();
void c_vector_free(void *data);
void c_vector_push(void *data);
void c_vector_pop(void *data);
void c_vector_set(void *data);
void c_vector_resize(void *data);
void c_vector_insert(void *data);
void c_vector_erase(void *data);
void c_vector_at(void *data);
void c_vector_clear(void *data);

void* cc_deque_init();
void cc_deque_free(void *data);
void cc_deque_push_back(void *data);
void cc_deque_push_front(void *data);
void cc_deque_pop_back(void *data);
void cc_deque_pop_front(void *data);
void cc_deque_at(void *data);
void cc_deque_clear(void *data);

void* cc_list_init();
void cc_list_free(void *data);
void cc_list_push_back(void *data);
void cc_list_push_front(void *data);
void cc_list_pop_back(void *data);
void cc_list_pop_front(void *data);
void cc_list_insert(void *data);
void cc_list_erase(void *data);
void cc_list_clear(void *data);

void* cc_map_init();
void cc_map_free(void *data);
void cc_map_insert(void *data);
void cc_map_erase(void *data);
void cc_map_get(void *data);
void cc_map_clear(void *data);
void cc_map_rehash(void *data);

void* cc_pair_init();
void cc_pair_free(void *data);
void cc_pair_first(void *data);
void cc_pair_second(void *data);
void cc_pair_set_first(void *data);
void cc_pair_set_second(void *data);

void* cc_queue_init();
void cc_queue_free(void *data);
void cc_queue_push(void *data);
void cc_queue_pop(void *data);
void cc_queue_clear(void *data);

void* cc_stack_init();
void cc_stack_free(void *data);
void cc_stack_push(void *data);
void cc_stack_pop(void *data);

void* cc_vector_init();
void cc_vector_free(void *data);
void cc_vector_push(void *data);
void cc_vector_pop(void *data);
void cc_vector_set(void *data);
void cc_vector_resize(void *data);
void cc_vector_insert(void *data);
void cc_vector_erase(void *data);
void cc_vector_at(void *data);
void cc_vector_clear(void *data);

#endif // BENCHMARK_BENCHMARK_H_
