#ifndef TEST_TEST_H_
#define TEST_TEST_H_

#include <stdbool.h>
#include <stdlib.h>

#define TEST_LOAD 100000UL

void test_deque();
void test_graph();
void test_heap();
void test_list();
void test_map();
void test_pair();
void test_queue();
void test_set();
void test_stack();
void test_vector();

bool fequals(float f1, float f2);

size_t hash_str(const void *value);
size_t hash_size_t(const void *value);
size_t hash_terribly(const void *value);

bool lt_int(const void *a, const void *b);
bool lt_float(const void *a, const void *b);
bool lt_size_t(const void *a, const void *b);

#endif // TEST_TEST_H_
