#ifndef TEST_TEST_H_
#define TEST_TEST_H_

#include <stdbool.h>
#include <stdlib.h>

#define TEST_LOAD 100000UL

void test_deque();
void test_list();
void test_map();
void test_pair();
void test_queue();
void test_set();
void test_stack();
void test_vector();

size_t hash_str(const void *key);
size_t hash_int(const void *key);
size_t hash_terribly(const void *key);
bool fequals(float f1, float f2);

#endif // TEST_TEST_H_
