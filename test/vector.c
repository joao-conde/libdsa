#include <assert.h>
#include <stdint.h>
#include <time.h>

#include "test.h"

#include "../include/vector.h"

void test_vector_init() {
    vector *v = vector_init(sizeof(int));
    assert(vector_size(v) == 0);
    assert(vector_capacity(v) == 512);
    vector_free(v);
}

void test_vector_init_fail() {
    vector *v = vector_init(SIZE_MAX);
    assert(v == NULL);

    v = vector_init(SIZE_MAX / 10000);
    assert(v == NULL);
}

void test_vector_with_capacity() {
    vector *v = vector_with_capacity(sizeof(int), 10);
    assert(vector_size(v) == 0);
    assert(vector_capacity(v) == 10);
    vector_free(v);
}

void test_vector_with_capacity_fail() {
    vector *v = vector_with_capacity(SIZE_MAX, 1000);
    assert(v == NULL);

    v = vector_with_capacity(SIZE_MAX / 1000, 512);
    assert(v == NULL);
}

void test_vector_void_ptrs() {
    void *d1 = malloc(10 * sizeof(void*));
    void *d2 = malloc(10 * sizeof(void*));
    void *d3 = malloc(10 * sizeof(void*));

    vector *v = vector_init(sizeof(void*));
    vector_push(v, &d1);
    vector_push(v, &d2);
    vector_push(v, &d3);
    assert(*(void**)vector_at(v, 0) == d1);
    assert(*(void**)vector_at(v, 1) == d2);
    assert(*(void**)vector_at(v, 2) == d3);

    vector_free(v);
    free(d3);
    free(d2);
    free(d1);
}

void test_vector_free() {
    vector_free(NULL);

    vector *v = vector_init(sizeof(int));
    vector_free(v);
}

void test_vector_size() {
    float value = 3.5;
    vector *v = vector_init(sizeof(float));
    assert(vector_size(v) == 0);

    vector_push(v, &value);
    vector_push(v, &value);
    vector_push(v, &value);
    assert(vector_size(v) == 3);

    vector_free(v);
}

void test_vector_capacity() {
    vector *v = vector_with_capacity(sizeof(int), 10);
    assert(vector_capacity(v) == 10);
    vector_free(v);
}

void test_vector_empty() {
    vector *v = vector_init(sizeof(int));
    assert(vector_empty(v));

    int value = -10;
    vector_push(v, &value);
    assert(!vector_empty(v));

    vector_pop(v);
    assert(vector_empty(v));

    vector_free(v);
}

void test_vector_clear() {
    double values[7] = {15.5, 21.7, 30.1, 69.10, -1.56, 10.0, 28.2};
    vector *v = vector_init(sizeof(double));
    for (int i = 0; i < 7; i++) vector_push(v, values + i);
    assert(!vector_empty(v));
    assert(vector_size(v) == 7);
    assert(vector_capacity(v) == 512);

    vector_clear(v);
    assert(vector_empty(v));
    assert(vector_size(v) == 0);
    assert(vector_capacity(v) == 512);

    vector_free(v);
}

void test_vector_at() {
    unsigned int values[4] = {15, 21, 30, 69};
    vector *v = vector_init(sizeof(int));
    for (int i = 0; i < 4; i++) vector_push(v, values + i);
    assert(*(unsigned int*)vector_at(v, 0) == 15);
    assert(*(unsigned int*)vector_at(v, 1) == 21);
    assert(*(unsigned int*)vector_at(v, 2) == 30);
    assert(*(unsigned int*)vector_at(v, 3) == 69);
    assert(vector_at(v, 4) == NULL);
    vector_free(v);
}

void test_vector_at_fail() {
    vector *v = vector_init(sizeof(int));
    assert(vector_at(v, 0) == NULL);
    vector_free(v);
}

void test_vector_set() {
    unsigned int values[4] = {15, 21, 30, 69};
    vector *v = vector_with_capacity(sizeof(int), 260);
    for (int i = 0; i < 4; i++) vector_push(v, values + i);
    assert(*(unsigned int*)vector_at(v, 0) == 15);
    assert(*(unsigned int*)vector_at(v, 1) == 21);
    assert(*(unsigned int*)vector_at(v, 2) == 30);
    assert(*(unsigned int*)vector_at(v, 3) == 69);

    void *result = vector_set(v, 0, values + 3);
    assert(*(unsigned int*)result == 69);

    result = vector_set(v, 1, values);
    assert(*(unsigned int*)result == 15);

    result = vector_set(v, 2, values + 2);
    assert(*(unsigned int*)result == 30);

    result = vector_set(v, 3, values + 1);
    assert(*(unsigned int*)result == 21);

    assert(*(unsigned int*)vector_at(v, 0) == 69);
    assert(*(unsigned int*)vector_at(v, 1) == 15);
    assert(*(unsigned int*)vector_at(v, 2) == 30);
    assert(*(unsigned int*)vector_at(v, 3) == 21);

    vector_free(v);
}

void test_vector_set_fail() {
    int value = 3;
    vector *v = vector_init(sizeof(int));
    assert(vector_set(v, 0, &value) == NULL);
    vector_free(v);
}

void test_vector_begin() {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_init(sizeof(int));
    for (int i = 0; i < 4; i++) vector_push(v, values + i);
    assert(*(int*)vector_begin(v) == 15);
    assert(vector_begin(v) == vector_at(v, 0));
    vector_free(v);
}

void test_vector_back() {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_init(sizeof(int));
    for (int i = 0; i < 4; i++) vector_push(v, values + i);
    assert(vector_back(v) == vector_at(v, 3));
    vector_free(v);
}

void test_vector_end() {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_init(sizeof(int));
    for (int i = 0; i < 4; i++) vector_push(v, values + i);
    assert((uint8_t*) vector_at(v, 3) + sizeof(int) == vector_end(v));
    vector_free(v);
}

void test_vector_pointers() {
    vector *v = vector_init(sizeof(int));
    assert(vector_begin(v) == vector_back(v));
    assert((uint8_t*) vector_back(v) + sizeof(int) == vector_end(v));
    vector_free(v);
}

void test_vector_push() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    vector *v = vector_init(sizeof(int));

    result = vector_push(v, &values[0]);
    assert(*result == 51);

    result = vector_push(v, &values[1]);
    assert(*result == 12);

    result = vector_push(v, &values[2]);
    assert(*result == -123);

    result = vector_push(v, &values[3]);
    assert(*result == 1000);

    result = vector_push(v, &values[4]);
    assert(*result == -1);

    assert(vector_size(v) == 5);
    assert(*(int*)vector_at(v, 0) == 51);
    assert(*(int*)vector_at(v, 1) == 12);
    assert(*(int*)vector_at(v, 2) == -123);
    assert(*(int*)vector_at(v, 3) == 1000);
    assert(*(int*)vector_at(v, 4) == -1);
    assert(vector_at(v, 5) == NULL);

    vector_free(v);
}

void test_vector_push_void_ptrs() {
    void *d1 = malloc(10 * sizeof(void*));
    void *d2 = malloc(10 * sizeof(void*));
    void *d3 = malloc(10 * sizeof(void*));

    vector *v = vector_init(sizeof(void*));
    vector_push(v, &d1);
    vector_push(v, &d2);
    vector_push(v, &d3);
    assert(*(void**)vector_at(v, 0) == d1);
    assert(*(void**)vector_at(v, 1) == d2);
    assert(*(void**)vector_at(v, 2) == d3);

    vector_free(v);
    free(d3);
    free(d2);
    free(d1);
}

void test_vector_push_resize() {
    int values[5] = {0, -10, 50, 30, -57};

    vector *v = vector_with_capacity(sizeof(int), 1);
    assert(vector_size(v) == 0);
    assert(vector_capacity(v) == 1);

    vector_push(v, &values[0]);
    assert(vector_size(v) == 1);
    assert(vector_capacity(v) == 1);
    assert(*(int*)vector_at(v, 0) == 0);

    vector_push(v, &values[1]);
    assert(vector_size(v) == 2);
    assert(vector_capacity(v) == 2);
    assert(*(int*)vector_at(v, 0) == 0);
    assert(*(int*)vector_at(v, 1) == -10);

    vector_push(v, &values[2]);
    assert(vector_size(v) == 3);
    assert(vector_capacity(v) == 4);
    assert(*(int*)vector_at(v, 0) == 0);
    assert(*(int*)vector_at(v, 1) == -10);
    assert(*(int*)vector_at(v, 2) == 50);

    vector_push(v, &values[3]);
    assert(vector_size(v) == 4);
    assert(vector_capacity(v) == 4);
    assert(*(int*)vector_at(v, 0) == 0);
    assert(*(int*)vector_at(v, 1) == -10);
    assert(*(int*)vector_at(v, 2) == 50);
    assert(*(int*)vector_at(v, 3) == 30);

    vector_push(v, &values[4]);
    assert(vector_size(v) == 5);
    assert(vector_capacity(v) == 8);
    assert(*(int*)vector_at(v, 0) == 0);
    assert(*(int*)vector_at(v, 1) == -10);
    assert(*(int*)vector_at(v, 2) == 50);
    assert(*(int*)vector_at(v, 3) == 30);
    assert(*(int*)vector_at(v, 4) == -57);

    vector_free(v);
}

void test_vector_pop() {
    int *result, values[4] = {15, 21, 30, 69};
    vector *v = vector_init(sizeof(int));
    for (int i = 0; i < 4; i++) vector_push(v, values + i);
    assert(vector_size(v) == 4);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(*(int*)vector_at(v, 1) == 21);
    assert(*(int*)vector_at(v, 2) == 30);
    assert(*(int*)vector_at(v, 3) == 69);

    result = vector_pop(v);
    assert(*result == 69);
    assert(vector_size(v) == 3);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(*(int*)vector_at(v, 1) == 21);
    assert(*(int*)vector_at(v, 2) == 30);
    assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    assert(*result == 30);
    assert(vector_size(v) == 2);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(*(int*)vector_at(v, 1) == 21);
    assert(vector_at(v, 2) == NULL);
    assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    assert(*result == 21);
    assert(vector_size(v) == 1);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(vector_at(v, 1) == NULL);
    assert(vector_at(v, 2) == NULL);
    assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    assert(*result == 15);
    assert(vector_size(v) == 0);
    assert(vector_at(v, 0) == NULL);
    assert(vector_at(v, 1) == NULL);
    assert(vector_at(v, 2) == NULL);
    assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    assert(result == NULL);
    assert(vector_size(v) == 0);
    assert(vector_at(v, 0) == NULL);
    assert(vector_at(v, 1) == NULL);
    assert(vector_at(v, 2) == NULL);
    assert(vector_at(v, 3) == NULL);

    vector_free(v);
}

void test_vector_insert() {
    int *result, values[4] = {15, 21, 30, 69};
    vector *v = vector_init(sizeof(int));
    for (int i = 0; i < 4; i++) vector_push(v, values + i);
    assert(vector_size(v) == 4);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(*(int*)vector_at(v, 1) == 21);
    assert(*(int*)vector_at(v, 2) == 30);
    assert(*(int*)vector_at(v, 3) == 69);

    result = vector_insert(v, 2, &values[3]);
    assert(*result == 69);
    assert(vector_size(v) == 5);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(*(int*)vector_at(v, 1) == 21);
    assert(*(int*)vector_at(v, 2) == 69);
    assert(*(int*)vector_at(v, 3) == 30);
    assert(*(int*)vector_at(v, 4) == 69);

    result = vector_insert(v, 0, &values[2]);
    assert(*result == 30);
    assert(vector_size(v) == 6);
    assert(*(int*)vector_at(v, 0) == 30);
    assert(*(int*)vector_at(v, 1) == 15);
    assert(*(int*)vector_at(v, 2) == 21);
    assert(*(int*)vector_at(v, 3) == 69);
    assert(*(int*)vector_at(v, 4) == 30);
    assert(*(int*)vector_at(v, 5) == 69);

    result = vector_insert(v, 6, &values[0]);
    assert(*result == 15);
    assert(vector_size(v) == 7);
    assert(*(int*)vector_at(v, 0) == 30);
    assert(*(int*)vector_at(v, 1) == 15);
    assert(*(int*)vector_at(v, 2) == 21);
    assert(*(int*)vector_at(v, 3) == 69);
    assert(*(int*)vector_at(v, 4) == 30);
    assert(*(int*)vector_at(v, 5) == 69);
    assert(*(int*)vector_at(v, 6) == 15);

    result = vector_insert(v, 1000, &values[0]);
    assert(result == NULL);
    assert(vector_size(v) == 7);
    assert(*(int*)vector_at(v, 0) == 30);
    assert(*(int*)vector_at(v, 1) == 15);
    assert(*(int*)vector_at(v, 2) == 21);
    assert(*(int*)vector_at(v, 3) == 69);
    assert(*(int*)vector_at(v, 4) == 30);
    assert(*(int*)vector_at(v, 5) == 69);
    assert(*(int*)vector_at(v, 6) == 15);

    vector_free(v);
}

void test_vector_insert_void_ptrs() {
    void *d1 = malloc(10 * sizeof(void*));
    void *d2 = malloc(10 * sizeof(void*));
    void *d3 = malloc(10 * sizeof(void*));

    vector *v = vector_init(sizeof(void*));
    vector_insert(v, 0, &d1);
    vector_insert(v, 0, &d2);
    vector_insert(v, 0, &d3);
    assert(*(void**)vector_at(v, 0) == d3);
    assert(*(void**)vector_at(v, 1) == d2);
    assert(*(void**)vector_at(v, 2) == d1);

    vector_free(v);
    free(d3);
    free(d2);
    free(d1);
}

void test_vector_insert_resize() {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_with_capacity(sizeof(int), 1);
    assert(vector_size(v) == 0);
    assert(vector_capacity(v) == 1);

    vector_insert(v, 0, &values[0]);
    assert(vector_size(v) == 1);
    assert(vector_capacity(v) == 1);

    vector_insert(v, 0, &values[1]);
    assert(vector_size(v) == 2);
    assert(vector_capacity(v) == 2);

    vector_insert(v, 0, &values[2]);
    assert(vector_size(v) == 3);
    assert(vector_capacity(v) == 4);

    vector_insert(v, 0, &values[3]);
    assert(vector_size(v) == 4);
    assert(vector_capacity(v) == 4);

    vector_insert(v, 0, &values[0]);
    assert(vector_size(v) == 5);
    assert(vector_capacity(v) == 8);

    assert(*(int*)vector_at(v, 0) == 15);
    assert(*(int*)vector_at(v, 1) == 69);
    assert(*(int*)vector_at(v, 2) == 30);
    assert(*(int*)vector_at(v, 3) == 21);
    assert(*(int*)vector_at(v, 4) == 15);

    vector_free(v);
}

void test_vector_erase() {
    double *result, values[7] = {15.5, 21.7, 30.1, 69.10, -1.56, 10.0, 28.2};
    vector *v = vector_init(sizeof(double));
    for (int i = 0; i < 7; i++) vector_push(v, values + i);
    assert(vector_size(v) == 7);
    assert(*(double*)vector_at(v, 0) == 15.5);
    assert(*(double*)vector_at(v, 1) == 21.7);
    assert(*(double*)vector_at(v, 2) == 30.1);
    assert(*(double*)vector_at(v, 3) == 69.10);
    assert(*(double*)vector_at(v, 4) == -1.56);
    assert(*(double*)vector_at(v, 5) == 10.0);
    assert(*(double*)vector_at(v, 6) == 28.2);

    result = vector_erase(v, 3);
    assert(*result == -1.56);
    assert(vector_size(v) == 6);
    assert(*(double*)vector_at(v, 0) == 15.5);
    assert(*(double*)vector_at(v, 1) == 21.7);
    assert(*(double*)vector_at(v, 2) == 30.1);
    assert(*(double*)vector_at(v, 3) == -1.56);
    assert(*(double*)vector_at(v, 4) == 10.0);
    assert(*(double*)vector_at(v, 5) == 28.2);
    assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 4);
    assert(*result == 28.2);
    assert(vector_size(v) == 5);
    assert(*(double*)vector_at(v, 0) == 15.5);
    assert(*(double*)vector_at(v, 1) == 21.7);
    assert(*(double*)vector_at(v, 2) == 30.1);
    assert(*(double*)vector_at(v, 3) == -1.56);
    assert(*(double*)vector_at(v, 4) == 28.2);
    assert(vector_at(v, 5) == NULL);
    assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 0);
    assert(*result == 21.7);
    assert(vector_size(v) == 4);
    assert(*(double*)vector_at(v, 0) == 21.7);
    assert(*(double*)vector_at(v, 1) == 30.1);
    assert(*(double*)vector_at(v, 2) == -1.56);
    assert(*(double*)vector_at(v, 3) == 28.2);
    assert(vector_at(v, 4) == NULL);
    assert(vector_at(v, 5) == NULL);
    assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 3);
    assert(result != NULL);
    assert(vector_size(v) == 3);
    assert(*(double*)vector_at(v, 0) == 21.7);
    assert(*(double*)vector_at(v, 1) == 30.1);
    assert(*(double*)vector_at(v, 2) == -1.56);
    assert(vector_at(v, 3) == NULL);
    assert(vector_at(v, 4) == NULL);
    assert(vector_at(v, 5) == NULL);
    assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 10.000);
    assert(result == NULL);
    assert(vector_size(v) == 3);
    assert(*(double*)vector_at(v, 0) == 21.7);
    assert(*(double*)vector_at(v, 1) == 30.1);
    assert(*(double*)vector_at(v, 2) == -1.56);
    assert(vector_at(v, 4) == NULL);
    assert(vector_at(v, 4) == NULL);
    assert(vector_at(v, 5) == NULL);
    assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 0);
    assert(*result == 30.1);

    result = vector_erase(v, 0);
    assert(*result == -1.56);

    result = vector_erase(v, 0);
    assert(result != NULL);

    assert(vector_size(v) == 0);
    assert(vector_at(v, 0) == NULL);
    assert(vector_at(v, 1) == NULL);
    assert(vector_at(v, 2) == NULL);
    assert(vector_at(v, 3) == NULL);
    assert(vector_at(v, 4) == NULL);
    assert(vector_at(v, 5) == NULL);
    assert(vector_at(v, 6) == NULL);

    vector_free(v);
}

void test_vector_resize() {
    int values[5] = {1, 2, 3, 4, 5};

    vector *v = vector_init(sizeof(int));
    vector_push(v, &values[0]);
    vector_push(v, &values[1]);
    vector_push(v, &values[2]);
    vector_push(v, &values[3]);

    assert(vector_capacity(v) == 512);
    assert(vector_size(v) == 4);

    void *result = vector_resize(v, 2);
    assert(result != NULL);
    assert(vector_capacity(v) == 2);
    assert(vector_size(v) == 2);

    assert(*(int*) vector_at(v, 0) == 1);
    assert(*(int*) vector_at(v, 1) == 2);
    assert(vector_at(v, 2) == NULL);

    result = vector_resize(v, 0);
    assert(result == NULL);
    assert(vector_capacity(v) == 0);
    assert(vector_size(v) == 0);

    result = vector_resize(v, 512);
    assert(result != NULL);
    assert(vector_capacity(v) == 512);
    assert(vector_size(v) == 0);

    result = vector_push(v, &values[4]);
    assert(vector_capacity(v) == 512);
    assert(vector_size(v) == 1);
    assert(*(int*) result == 5);
    assert(*(int*) vector_at(v, 0) == 5);

    vector_free(v);
}

void test_vector_load() {
    unsigned int seed = time(NULL);
    int random;
    bool empty;
    size_t size, capacity;
    size_t *at, *set, *pushed, *popped, *inserted, *erased, *begin, *back, *end;

    vector *v = vector_init(sizeof(size_t));

    for (size_t i = 0; i < TEST_LOAD; i++) {
        pushed = vector_push(v, &i);
        size = vector_size(v);
        capacity = vector_capacity(v);
        empty = vector_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        begin = vector_begin(v);
        back = vector_back(v);
        end = vector_end(v);
        assert(*pushed == i);
        assert(size == i + 1);
        assert(capacity >= 512);
        assert(!empty);
        assert(*at == i);
        assert(*set == i);
        assert(*begin == 0);
        assert(*back == i);
        assert(end == back + 1);
    }

    for (size_t i = 0; i < TEST_LOAD / 2; i++) {
        popped = vector_pop(v);
        size = vector_size(v);
        capacity = vector_capacity(v);
        empty = vector_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        begin = vector_begin(v);
        back = vector_back(v);
        end = vector_end(v);
        assert(*popped == TEST_LOAD - i - 1);
        assert(size == TEST_LOAD - i - 1);
        assert(capacity >= 512);
        assert(!empty);
        assert(*at == i);
        assert(*set == i);
        assert(*begin == 0);
        assert(*back == TEST_LOAD - i - 2);
        assert(end == back + 1);
    }

    vector_clear(v);
    size = vector_size(v);
    empty = vector_empty(v);
    capacity = vector_capacity(v);
    assert(size == 0);
    assert(empty);
    assert(capacity == 131072);

    for (size_t i = 0; i < TEST_LOAD; i++) {
        size = vector_size(v);
        random = rand_r(&seed) % (size > 0 ? size : 1);

        inserted = vector_insert(v, random, &i);
        size = vector_size(v);
        capacity = vector_capacity(v);
        empty = vector_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        back = vector_back(v);
        end = vector_end(v);
        assert(*inserted == i);
        assert(size == i + 1);
        assert(capacity == 131072);
        assert(!empty);
        assert(*at == i);
        assert(*set == i);
        assert(end == back + 1);
    }

    for (size_t i = 0; i < TEST_LOAD / 2; i++) {
        size = vector_size(v);
        random = rand_r(&seed) % (size > 0 ? size : 1);

        erased = vector_erase(v, random);
        size = vector_size(v);
        capacity = vector_capacity(v);
        empty = vector_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        back = vector_back(v);
        end = vector_end(v);
        assert(erased != NULL);
        assert(size == TEST_LOAD - i - 1);
        assert(capacity == 131072);
        assert(!empty);
        assert(*at == i);
        assert(*set == i);
        assert(end == back + 1);
    }

    vector_resize(v, 100000);
    size = vector_size(v);
    empty = vector_empty(v);
    capacity = vector_capacity(v);
    assert(size == TEST_LOAD / 2);
    assert(!empty);
    assert(capacity == 100000);

    vector_resize(v, 1000);
    size = vector_size(v);
    empty = vector_empty(v);
    capacity = vector_capacity(v);
    assert(size == 1000);
    assert(!empty);
    assert(capacity == 1000);

    vector_resize(v, 1);
    size = vector_size(v);
    empty = vector_empty(v);
    capacity = vector_capacity(v);
    assert(size == 1);
    assert(!empty);
    assert(capacity == 1);

    vector_resize(v, 0);
    size = vector_size(v);
    empty = vector_empty(v);
    capacity = vector_capacity(v);
    assert(size == 0);
    assert(empty);
    assert(capacity == 0);

    vector_free(v);
}

void test_vector() {
    test_vector_init();
    test_vector_init_fail();
    test_vector_with_capacity();
    test_vector_with_capacity_fail();
    test_vector_void_ptrs();
    test_vector_free();
    test_vector_size();
    test_vector_capacity();
    test_vector_empty();
    test_vector_clear();
    test_vector_at();
    test_vector_at_fail();
    test_vector_set();
    test_vector_set_fail();
    test_vector_begin();
    test_vector_back();
    test_vector_end();
    test_vector_pointers();
    test_vector_push();
    test_vector_push_void_ptrs();
    test_vector_push_resize();
    test_vector_pop();
    test_vector_insert();
    test_vector_insert_void_ptrs();
    test_vector_insert_resize();
    test_vector_erase();
    test_vector_resize();
    test_vector_load();
}
