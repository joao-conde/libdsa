#ifndef TEST_TEST_H_
#define TEST_TEST_H_

#include <assert.h>
#include <math.h>
#include <float.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "../include/deque.h"
#include "../include/list.h"
#include "../include/map.h"
#include "../include/pair.h"
#include "../include/queue.h"
#include "../include/stack.h"
#include "../include/vector.h"

#define TEST_LOAD 100000UL

void test_deque();
void test_list();
void test_map();
void test_pair();
void test_queue();
void test_stack();
void test_vector();

#endif // TEST_TEST_H_
