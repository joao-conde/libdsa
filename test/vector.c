#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../include/vector.h"

void test_vector_init() {
    vector *v = vector_init(sizeof(int));
    assert(vector_length(v) == 0);
    assert(vector_capacity(v) == 256);
    vector_free(v);
}

void test_vector_init_fail() {
    vector *v = vector_init(SIZE_MAX);
    assert(v == NULL);

    v = vector_init(SIZE_MAX / 1000);
    assert(v == NULL);
}

void test_vector_with_capacity() {
    vector *v = vector_with_capacity(sizeof(int), 10);
    assert(vector_length(v) == 0);
    assert(vector_capacity(v) == 10);
    vector_free(v);
}

void test_vector_with_capacity_fail() {
    vector *v = vector_with_capacity(SIZE_MAX, 1000);
    assert(v == NULL);

    v = vector_with_capacity(SIZE_MAX / 1000, 256);
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

void test_vector_length() {
    float value = 3.5;
    vector *v = vector_init(sizeof(float));
    assert(vector_length(v) == 0);

    vector_push(v, &value);
    vector_push(v, &value);
    vector_push(v, &value);
    assert(vector_length(v) == 3);

    vector_free(v);
}

void test_vector_capacity() {
    vector *v = vector_with_capacity(sizeof(int), 10);
    assert(vector_capacity(v) == 10);
    vector_free(v);
}

void test_vector_is_empty() {
    vector *v = vector_init(sizeof(int));
    assert(vector_is_empty(v));

    int value = -10;
    vector_push(v, &value);
    assert(!vector_is_empty(v));

    vector_pop(v);
    assert(vector_is_empty(v));

    vector_free(v);
}

void test_vector_clear() {
    double values[7] = {15.5, 21.7, 30.1, 69.10, -1.56, 10.0, 28.2};
    vector *v = vector_init(sizeof(double));
    for (int i = 0; i < 7; i++) vector_push(v, values + i);
    assert(!vector_is_empty(v));
    assert(vector_length(v) == 7);
    assert(vector_capacity(v) == 256);

    vector_clear(v);
    assert(vector_is_empty(v));
    assert(vector_length(v) == 0);
    assert(vector_capacity(v) == 256);

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
    assert(vector_end(v) == vector_at(v, 3) + sizeof(int));
    vector_free(v);
}

void test_vector_pointers() {
    vector *v = vector_init(sizeof(int));
    assert(vector_begin(v) == vector_back(v));
    assert(vector_back(v) + sizeof(int) == vector_end(v));
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

    assert(vector_length(v) == 5);
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
    assert(vector_length(v) == 0);
    assert(vector_capacity(v) == 1);

    vector_push(v, &values[0]);
    assert(vector_length(v) == 1);
    assert(vector_capacity(v) == 1);
    assert(*(int*)vector_at(v, 0) == 0);

    vector_push(v, &values[1]);
    assert(vector_length(v) == 2);
    assert(vector_capacity(v) == 2);
    assert(*(int*)vector_at(v, 0) == 0);
    assert(*(int*)vector_at(v, 1) == -10);

    vector_push(v, &values[2]);
    assert(vector_length(v) == 3);
    assert(vector_capacity(v) == 4);
    assert(*(int*)vector_at(v, 0) == 0);
    assert(*(int*)vector_at(v, 1) == -10);
    assert(*(int*)vector_at(v, 2) == 50);

    vector_push(v, &values[3]);
    assert(vector_length(v) == 4);
    assert(vector_capacity(v) == 4);
    assert(*(int*)vector_at(v, 0) == 0);
    assert(*(int*)vector_at(v, 1) == -10);
    assert(*(int*)vector_at(v, 2) == 50);
    assert(*(int*)vector_at(v, 3) == 30);

    vector_push(v, &values[4]);
    assert(vector_length(v) == 5);
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
    assert(vector_length(v) == 4);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(*(int*)vector_at(v, 1) == 21);
    assert(*(int*)vector_at(v, 2) == 30);
    assert(*(int*)vector_at(v, 3) == 69);

    result = vector_pop(v);
    assert(*result == 69);
    assert(vector_length(v) == 3);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(*(int*)vector_at(v, 1) == 21);
    assert(*(int*)vector_at(v, 2) == 30);
    assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    assert(*result == 30);
    assert(vector_length(v) == 2);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(*(int*)vector_at(v, 1) == 21);
    assert(vector_at(v, 2) == NULL);
    assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    assert(*result == 21);
    assert(vector_length(v) == 1);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(vector_at(v, 1) == NULL);
    assert(vector_at(v, 2) == NULL);
    assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    assert(*result == 15);
    assert(vector_length(v) == 0);
    assert(vector_at(v, 0) == NULL);
    assert(vector_at(v, 1) == NULL);
    assert(vector_at(v, 2) == NULL);
    assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    assert(result == NULL);
    assert(vector_length(v) == 0);
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
    assert(vector_length(v) == 4);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(*(int*)vector_at(v, 1) == 21);
    assert(*(int*)vector_at(v, 2) == 30);
    assert(*(int*)vector_at(v, 3) == 69);

    result = vector_insert(v, 2, &values[3]);
    assert(*result == 69);
    assert(vector_length(v) == 5);
    assert(*(int*)vector_at(v, 0) == 15);
    assert(*(int*)vector_at(v, 1) == 21);
    assert(*(int*)vector_at(v, 2) == 69);
    assert(*(int*)vector_at(v, 3) == 30);
    assert(*(int*)vector_at(v, 4) == 69);

    result = vector_insert(v, 0, &values[2]);
    assert(*result == 30);
    assert(vector_length(v) == 6);
    assert(*(int*)vector_at(v, 0) == 30);
    assert(*(int*)vector_at(v, 1) == 15);
    assert(*(int*)vector_at(v, 2) == 21);
    assert(*(int*)vector_at(v, 3) == 69);
    assert(*(int*)vector_at(v, 4) == 30);
    assert(*(int*)vector_at(v, 5) == 69);

    result = vector_insert(v, 6, &values[0]);
    assert(*result == 15);
    assert(vector_length(v) == 7);
    assert(*(int*)vector_at(v, 0) == 30);
    assert(*(int*)vector_at(v, 1) == 15);
    assert(*(int*)vector_at(v, 2) == 21);
    assert(*(int*)vector_at(v, 3) == 69);
    assert(*(int*)vector_at(v, 4) == 30);
    assert(*(int*)vector_at(v, 5) == 69);
    assert(*(int*)vector_at(v, 6) == 15);

    result = vector_insert(v, 1000, &values[0]);
    assert(result == NULL);
    assert(vector_length(v) == 7);
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
    assert(vector_length(v) == 0);
    assert(vector_capacity(v) == 1);

    vector_insert(v, 0, &values[0]);
    assert(vector_length(v) == 1);
    assert(vector_capacity(v) == 1);

    vector_insert(v, 0, &values[1]);
    assert(vector_length(v) == 2);
    assert(vector_capacity(v) == 2);

    vector_insert(v, 0, &values[2]);
    assert(vector_length(v) == 3);
    assert(vector_capacity(v) == 4);

    vector_insert(v, 0, &values[3]);
    assert(vector_length(v) == 4);
    assert(vector_capacity(v) == 4);

    vector_insert(v, 0, &values[0]);
    assert(vector_length(v) == 5);
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
    assert(vector_length(v) == 7);
    assert(*(double*)vector_at(v, 0) == 15.5);
    assert(*(double*)vector_at(v, 1) == 21.7);
    assert(*(double*)vector_at(v, 2) == 30.1);
    assert(*(double*)vector_at(v, 3) == 69.10);
    assert(*(double*)vector_at(v, 4) == -1.56);
    assert(*(double*)vector_at(v, 5) == 10.0);
    assert(*(double*)vector_at(v, 6) == 28.2);

    result = vector_erase(v, 3);
    assert(*result == -1.56);
    assert(vector_length(v) == 6);
    assert(*(double*)vector_at(v, 0) == 15.5);
    assert(*(double*)vector_at(v, 1) == 21.7);
    assert(*(double*)vector_at(v, 2) == 30.1);
    assert(*(double*)vector_at(v, 3) == -1.56);
    assert(*(double*)vector_at(v, 4) == 10.0);
    assert(*(double*)vector_at(v, 5) == 28.2);
    assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 4);
    assert(*result == 28.2);
    assert(vector_length(v) == 5);
    assert(*(double*)vector_at(v, 0) == 15.5);
    assert(*(double*)vector_at(v, 1) == 21.7);
    assert(*(double*)vector_at(v, 2) == 30.1);
    assert(*(double*)vector_at(v, 3) == -1.56);
    assert(*(double*)vector_at(v, 4) == 28.2);
    assert(vector_at(v, 5) == NULL);
    assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 0);
    assert(*result == 21.7);
    assert(vector_length(v) == 4);
    assert(*(double*)vector_at(v, 0) == 21.7);
    assert(*(double*)vector_at(v, 1) == 30.1);
    assert(*(double*)vector_at(v, 2) == -1.56);
    assert(*(double*)vector_at(v, 3) == 28.2);
    assert(vector_at(v, 4) == NULL);
    assert(vector_at(v, 5) == NULL);
    assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 3);
    assert(result != NULL);
    assert(vector_length(v) == 3);
    assert(*(double*)vector_at(v, 0) == 21.7);
    assert(*(double*)vector_at(v, 1) == 30.1);
    assert(*(double*)vector_at(v, 2) == -1.56);
    assert(vector_at(v, 3) == NULL);
    assert(vector_at(v, 4) == NULL);
    assert(vector_at(v, 5) == NULL);
    assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 10.000);
    assert(result == NULL);
    assert(vector_length(v) == 3);
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

    assert(vector_length(v) == 0);
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
    vector *v = vector_init(sizeof(char*));
    vector_push(v, "hello");
    vector_push(v, "world");
    vector_push(v, "welcome");
    vector_push(v, "all");

    assert(vector_capacity(v) == 256);
    assert(vector_length(v) == 4);

    void *result = vector_resize(v, 2);
    assert(result != NULL);
    assert(vector_capacity(v) == 2);
    assert(vector_length(v) == 2);

    assert(strcmp(vector_at(v, 0), "hello") == 0);
    assert(strcmp(vector_at(v, 1), "world") == 0);
    assert(vector_at(v, 2) == NULL);

    result = vector_resize(v, 0);
    assert(result == NULL);
    assert(vector_capacity(v) == 0);
    assert(vector_length(v) == 0);

    result = vector_resize(v, 256);
    assert(result != NULL);
    assert(vector_capacity(v) == 256);
    assert(vector_length(v) == 0);

    result = vector_push(v, "hello");
    assert(vector_capacity(v) == 256);
    assert(vector_length(v) == 1);
    assert(strcmp(result, "hello") == 0);
    assert(strcmp(vector_at(v, 0), "hello") == 0);

    vector_free(v);
}

void test_vector_load() {
    unsigned int seed = time(NULL);
    int random, nelements = 100000;
    bool is_empty;
    size_t length, capacity;
    int *at, *set, *pushed, *popped, *inserted, *erased, *begin, *back, *end;

    vector *v = vector_init(sizeof(int));

    for (int i = 0; i < nelements; i++) {
        pushed = vector_push(v, &i);
        length = vector_length(v);
        capacity = vector_capacity(v);
        is_empty = vector_is_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        begin = vector_begin(v);
        back = vector_back(v);
        end = vector_end(v);
        assert(*pushed == i);
        assert(length == i + 1);
        assert(capacity >= 256);
        assert(!is_empty);
        assert(*at == i);
        assert(*set == i);
        assert(*begin == 0);
        assert(*back == i);
        assert(end == back + 1);
    }

    for (int i = 0; i < nelements / 2; i++) {
        popped = vector_pop(v);
        length = vector_length(v);
        capacity = vector_capacity(v);
        is_empty = vector_is_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        begin = vector_begin(v);
        back = vector_back(v);
        end = vector_end(v);
        assert(*popped == nelements - i - 1);
        assert(length == nelements - i - 1);
        assert(capacity >= 256);
        assert(!is_empty);
        assert(*at == i);
        assert(*set == i);
        assert(*begin == 0);
        assert(*back == nelements - i - 2);
        assert(end == back + 1);
    }

    vector_clear(v);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);
    assert(length == 0);
    assert(is_empty);
    assert(capacity == 131072);

    for (int i = 0; i < nelements; i++) {
        length = vector_length(v);
        random = rand_r(&seed) % (length > 0 ? length : 1);

        inserted = vector_insert(v, random, &i);
        length = vector_length(v);
        capacity = vector_capacity(v);
        is_empty = vector_is_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        back = vector_back(v);
        end = vector_end(v);
        assert(*inserted == i);
        assert(length == i + 1);
        assert(capacity == 131072);
        assert(!is_empty);
        assert(*at == i);
        assert(*set == i);
        assert(end == back + 1);
    }

    for (int i = 0; i < nelements / 2; i++) {
        length = vector_length(v);
        random = rand_r(&seed) % (length > 0 ? length : 1);

        erased = vector_erase(v, random);
        length = vector_length(v);
        capacity = vector_capacity(v);
        is_empty = vector_is_empty(v);
        at = vector_at(v, i);
        set = vector_set(v, i, &i);
        back = vector_back(v);
        end = vector_end(v);
        assert(erased != NULL);
        assert(length == nelements - i - 1);
        assert(capacity == 131072);
        assert(!is_empty);
        assert(*at == i);
        assert(*set == i);
        assert(end == back + 1);
    }

    vector_resize(v, 100000);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);
    assert(length == nelements / 2);
    assert(!is_empty);
    assert(capacity == 100000);

    vector_resize(v, 1000);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);
    assert(length == 1000);
    assert(!is_empty);
    assert(capacity == 1000);

    vector_resize(v, 1);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);
    assert(length == 1);
    assert(!is_empty);
    assert(capacity == 1);

    vector_resize(v, 0);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);
    assert(length == 0);
    assert(is_empty);
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
    test_vector_length();
    test_vector_capacity();
    test_vector_is_empty();
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
