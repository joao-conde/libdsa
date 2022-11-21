#include <check.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../../include/vector.h"

START_TEST(test_vector_init) {
    vector *v = vector_init(sizeof(int));
    ck_assert(vector_length(v) == 0);
    ck_assert(vector_capacity(v) == 256);
    vector_free(v);
}
END_TEST

START_TEST(test_vector_init_fail) {
    vector *v = vector_init(SIZE_MAX);
    ck_assert(v == NULL);

    v = vector_init(SIZE_MAX / 1000);
    ck_assert(v == NULL);
}
END_TEST

START_TEST(test_vector_with_capacity) {
    vector *v = vector_with_capacity(sizeof(int), 10);
    ck_assert(vector_length(v) == 0);
    ck_assert(vector_capacity(v) == 10);
    vector_free(v);
}
END_TEST

START_TEST(test_vector_with_capacity_fail) {
    vector *v = vector_with_capacity(SIZE_MAX, 1000);
    ck_assert(v == NULL);

    v = vector_with_capacity(SIZE_MAX / 1000, 256);
    ck_assert(v == NULL);
}
END_TEST

START_TEST(test_vector_from_array) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_length(v) == 4);
    ck_assert(vector_capacity(v) == 256);
    ck_assert(*(int*)vector_at(v, 0) == 15);
    ck_assert(*(int*)vector_at(v, 1) == 21);
    ck_assert(*(int*)vector_at(v, 2) == 30);
    ck_assert(*(int*)vector_at(v, 3) == 69);
    ck_assert(vector_at(v, 4) == NULL);
    vector_free(v);
}
END_TEST

START_TEST(test_vector_from_array_void_ptrs) {
    void *d1 = malloc(10 * sizeof(void*));
    void *d2 = malloc(10 * sizeof(void*));
    void *d3 = malloc(10 * sizeof(void*));
    void* values[3] = {d1, d2, d3};

    vector *v = vector_from_array(sizeof(void*), 3, values);
    ck_assert(*(void**)vector_at(v, 0) == d1);
    ck_assert(*(void**)vector_at(v, 1) == d2);
    ck_assert(*(void**)vector_at(v, 2) == d3);

    vector_free(v);
    free(d3);
    free(d2);
    free(d1);
}
END_TEST

START_TEST(test_vector_from_array_resize) {
    int *values = calloc(260, sizeof(int));
    vector *v = vector_from_array(sizeof(int), 260, values);
    ck_assert(vector_length(v) == 260);
    ck_assert(vector_capacity(v) == 520);
    vector_free(v);
    free(values);
}
END_TEST

START_TEST(test_vector_from_array_fail) {
    vector *v = vector_from_array(SIZE_MAX, 1, NULL);
    ck_assert(v == NULL);

    v = vector_from_array(SIZE_MAX / 1000, 1, NULL);
    ck_assert(v == NULL);
}
END_TEST

START_TEST(test_vector_free) {
    vector_free(NULL);

    vector *v = vector_init(sizeof(int));
    vector_free(v);
}
END_TEST

START_TEST(test_vector_length) {
    float value = 3.5;
    vector *v = vector_init(sizeof(float));
    ck_assert(vector_length(v) == 0);

    vector_push(v, &value);
    vector_push(v, &value);
    vector_push(v, &value);
    ck_assert(vector_length(v) == 3);

    vector_free(v);
}
END_TEST

START_TEST(test_vector_capacity) {
    vector *v = vector_with_capacity(sizeof(int), 10);
    ck_assert(vector_capacity(v) == 10);
    vector_free(v);
}
END_TEST

START_TEST(test_vector_is_empty) {
    vector *v = vector_init(sizeof(int));
    ck_assert(vector_is_empty(v));

    int value = -10;
    vector_push(v, &value);
    ck_assert(!vector_is_empty(v));

    vector_pop(v);
    ck_assert(vector_is_empty(v));

    vector_free(v);
}
END_TEST

START_TEST(test_vector_at) {
    unsigned int values[4] = {15, 21, 30, 69};
    vector *v = vector_from_array(sizeof(unsigned int), 4, values);
    ck_assert(*(unsigned int*)vector_at(v, 0) == 15);
    ck_assert(*(unsigned int*)vector_at(v, 1) == 21);
    ck_assert(*(unsigned int*)vector_at(v, 2) == 30);
    ck_assert(*(unsigned int*)vector_at(v, 3) == 69);
    ck_assert(vector_at(v, 4) == NULL);
    vector_free(v);
}
END_TEST

START_TEST(test_vector_at_fail) {
    vector *v = vector_init(sizeof(int));
    ck_assert(vector_at(v, 0) == NULL);
    vector_free(v);
}
END_TEST

START_TEST(test_vector_set) {
    unsigned int values[4] = {15, 21, 30, 69};
    vector *v = vector_from_array(sizeof(unsigned int), 4, values);
    ck_assert(*(unsigned int*)vector_at(v, 0) == 15);
    ck_assert(*(unsigned int*)vector_at(v, 1) == 21);
    ck_assert(*(unsigned int*)vector_at(v, 2) == 30);
    ck_assert(*(unsigned int*)vector_at(v, 3) == 69);

    void *result = vector_set(v, 0, &values[3]);
    ck_assert(*(unsigned int*)result == 69);

    result = vector_set(v, 1, &values[0]);
    ck_assert(*(unsigned int*)result == 15);

    result = vector_set(v, 2, &values[2]);
    ck_assert(*(unsigned int*)result == 30);

    result = vector_set(v, 3, &values[1]);
    ck_assert(*(unsigned int*)result == 21);

    ck_assert(*(unsigned int*)vector_at(v, 0) == 69);
    ck_assert(*(unsigned int*)vector_at(v, 1) == 15);
    ck_assert(*(unsigned int*)vector_at(v, 2) == 30);
    ck_assert(*(unsigned int*)vector_at(v, 3) == 21);

    vector_free(v);
}
END_TEST

START_TEST(test_vector_set_fail) {
    int value = 3;
    vector *v = vector_init(sizeof(int));
    ck_assert(vector_set(v, 0, &value) == NULL);
    vector_free(v);
}
END_TEST

START_TEST(test_vector_begin) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_from_array(sizeof(int), 4, values);
    ck_assert(*(int*)vector_begin(v) == 15);
    ck_assert(vector_begin(v) == vector_at(v, 0));
    vector_free(v);
}
END_TEST

START_TEST(test_vector_back) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_back(v) == vector_at(v, 3));
    vector_free(v);
}
END_TEST

START_TEST(test_vector_end) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_end(v) == vector_at(v, 3) + sizeof(int));
    vector_free(v);
}
END_TEST

START_TEST(test_vector_pointers) {
    vector *v = vector_init(sizeof(int));
    ck_assert(vector_begin(v) == vector_back(v));
    ck_assert(vector_begin(v) == vector_end(v));
    vector_free(v);
}
END_TEST

START_TEST(test_vector_push) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    vector *v = vector_init(sizeof(int));

    result = vector_push(v, &values[0]);
    ck_assert(*result == 51);

    result = vector_push(v, &values[1]);
    ck_assert(*result == 12);

    result = vector_push(v, &values[2]);
    ck_assert(*result == -123);

    result = vector_push(v, &values[3]);
    ck_assert(*result == 1000);

    result = vector_push(v, &values[4]);
    ck_assert(*result == -1);

    ck_assert(vector_length(v) == 5);
    ck_assert(*(int*)vector_at(v, 0) == 51);
    ck_assert(*(int*)vector_at(v, 1) == 12);
    ck_assert(*(int*)vector_at(v, 2) == -123);
    ck_assert(*(int*)vector_at(v, 3) == 1000);
    ck_assert(*(int*)vector_at(v, 4) == -1);
    ck_assert(vector_at(v, 5) == NULL);

    vector_free(v);
}
END_TEST

START_TEST(test_vector_push_void_ptrs) {
    void *d1 = malloc(10 * sizeof(void*));
    void *d2 = malloc(10 * sizeof(void*));
    void *d3 = malloc(10 * sizeof(void*));

    vector *v = vector_init(sizeof(void*));
    vector_push(v, &d1);
    vector_push(v, &d2);
    vector_push(v, &d3);
    ck_assert(*(void**)vector_at(v, 0) == d1);
    ck_assert(*(void**)vector_at(v, 1) == d2);
    ck_assert(*(void**)vector_at(v, 2) == d3);

    vector_free(v);
    free(d3);
    free(d2);
    free(d1);
}
END_TEST

START_TEST(test_vector_push_resize) {
    int values[5] = {0, -10, 50, 30, -57};

    vector *v = vector_with_capacity(sizeof(int), 1);
    ck_assert(vector_length(v) == 0);
    ck_assert(vector_capacity(v) == 1);

    vector_push(v, &values[0]);
    ck_assert(vector_length(v) == 1);
    ck_assert(vector_capacity(v) == 1);
    ck_assert(*(int*)vector_at(v, 0) == 0);

    vector_push(v, &values[1]);
    ck_assert(vector_length(v) == 2);
    ck_assert(vector_capacity(v) == 2);
    ck_assert(*(int*)vector_at(v, 0) == 0);
    ck_assert(*(int*)vector_at(v, 1) == -10);

    vector_push(v, &values[2]);
    ck_assert(vector_length(v) == 3);
    ck_assert(vector_capacity(v) == 4);
    ck_assert(*(int*)vector_at(v, 0) == 0);
    ck_assert(*(int*)vector_at(v, 1) == -10);
    ck_assert(*(int*)vector_at(v, 2) == 50);

    vector_push(v, &values[3]);
    ck_assert(vector_length(v) == 4);
    ck_assert(vector_capacity(v) == 4);
    ck_assert(*(int*)vector_at(v, 0) == 0);
    ck_assert(*(int*)vector_at(v, 1) == -10);
    ck_assert(*(int*)vector_at(v, 2) == 50);
    ck_assert(*(int*)vector_at(v, 3) == 30);

    vector_push(v, &values[4]);
    ck_assert(vector_length(v) == 5);
    ck_assert(vector_capacity(v) == 8);
    ck_assert(*(int*)vector_at(v, 0) == 0);
    ck_assert(*(int*)vector_at(v, 1) == -10);
    ck_assert(*(int*)vector_at(v, 2) == 50);
    ck_assert(*(int*)vector_at(v, 3) == 30);
    ck_assert(*(int*)vector_at(v, 4) == -57);

    vector_free(v);
}
END_TEST

START_TEST(test_vector_pop) {
    int *result, values[4] = {15, 21, 30, 69};
    vector *v = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_length(v) == 4);
    ck_assert(*(int*)vector_at(v, 0) == 15);
    ck_assert(*(int*)vector_at(v, 1) == 21);
    ck_assert(*(int*)vector_at(v, 2) == 30);
    ck_assert(*(int*)vector_at(v, 3) == 69);

    result = vector_pop(v);
    ck_assert(*result == 69);
    ck_assert(vector_length(v) == 3);
    ck_assert(*(int*)vector_at(v, 0) == 15);
    ck_assert(*(int*)vector_at(v, 1) == 21);
    ck_assert(*(int*)vector_at(v, 2) == 30);
    ck_assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    ck_assert(*result == 30);
    ck_assert(vector_length(v) == 2);
    ck_assert(*(int*)vector_at(v, 0) == 15);
    ck_assert(*(int*)vector_at(v, 1) == 21);
    ck_assert(vector_at(v, 2) == NULL);
    ck_assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    ck_assert(*result == 21);
    ck_assert(vector_length(v) == 1);
    ck_assert(*(int*)vector_at(v, 0) == 15);
    ck_assert(vector_at(v, 1) == NULL);
    ck_assert(vector_at(v, 2) == NULL);
    ck_assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    ck_assert(*result == 15);
    ck_assert(vector_length(v) == 0);
    ck_assert(vector_at(v, 0) == NULL);
    ck_assert(vector_at(v, 1) == NULL);
    ck_assert(vector_at(v, 2) == NULL);
    ck_assert(vector_at(v, 3) == NULL);

    result = vector_pop(v);
    ck_assert(result == NULL);
    ck_assert(vector_length(v) == 0);
    ck_assert(vector_at(v, 0) == NULL);
    ck_assert(vector_at(v, 1) == NULL);
    ck_assert(vector_at(v, 2) == NULL);
    ck_assert(vector_at(v, 3) == NULL);

    vector_free(v);
}
END_TEST

START_TEST(test_vector_insert) {
    int *result, values[4] = {15, 21, 30, 69};
    vector *v = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_length(v) == 4);
    ck_assert(*(int*)vector_at(v, 0) == 15);
    ck_assert(*(int*)vector_at(v, 1) == 21);
    ck_assert(*(int*)vector_at(v, 2) == 30);
    ck_assert(*(int*)vector_at(v, 3) == 69);

    result = vector_insert(v, 2, &values[3]);
    ck_assert(*result == 69);
    ck_assert(vector_length(v) == 5);
    ck_assert(*(int*)vector_at(v, 0) == 15);
    ck_assert(*(int*)vector_at(v, 1) == 21);
    ck_assert(*(int*)vector_at(v, 2) == 69);
    ck_assert(*(int*)vector_at(v, 3) == 30);
    ck_assert(*(int*)vector_at(v, 4) == 69);

    result = vector_insert(v, 0, &values[2]);
    ck_assert(*result == 30);
    ck_assert(vector_length(v) == 6);
    ck_assert(*(int*)vector_at(v, 0) == 30);
    ck_assert(*(int*)vector_at(v, 1) == 15);
    ck_assert(*(int*)vector_at(v, 2) == 21);
    ck_assert(*(int*)vector_at(v, 3) == 69);
    ck_assert(*(int*)vector_at(v, 4) == 30);
    ck_assert(*(int*)vector_at(v, 5) == 69);

    result = vector_insert(v, 6, &values[0]);
    ck_assert(*result == 15);
    ck_assert(vector_length(v) == 7);
    ck_assert(*(int*)vector_at(v, 0) == 30);
    ck_assert(*(int*)vector_at(v, 1) == 15);
    ck_assert(*(int*)vector_at(v, 2) == 21);
    ck_assert(*(int*)vector_at(v, 3) == 69);
    ck_assert(*(int*)vector_at(v, 4) == 30);
    ck_assert(*(int*)vector_at(v, 5) == 69);
    ck_assert(*(int*)vector_at(v, 6) == 15);

    result = vector_insert(v, 1000, &values[0]);
    ck_assert(result == NULL);
    ck_assert(vector_length(v) == 7);
    ck_assert(*(int*)vector_at(v, 0) == 30);
    ck_assert(*(int*)vector_at(v, 1) == 15);
    ck_assert(*(int*)vector_at(v, 2) == 21);
    ck_assert(*(int*)vector_at(v, 3) == 69);
    ck_assert(*(int*)vector_at(v, 4) == 30);
    ck_assert(*(int*)vector_at(v, 5) == 69);
    ck_assert(*(int*)vector_at(v, 6) == 15);

    vector_free(v);
}
END_TEST

START_TEST(test_vector_insert_void_ptrs) {
    void *d1 = malloc(10 * sizeof(void*));
    void *d2 = malloc(10 * sizeof(void*));
    void *d3 = malloc(10 * sizeof(void*));

    vector *v = vector_init(sizeof(void*));
    vector_insert(v, 0, &d1);
    vector_insert(v, 0, &d2);
    vector_insert(v, 0, &d3);
    ck_assert(*(void**)vector_at(v, 0) == d3);
    ck_assert(*(void**)vector_at(v, 1) == d2);
    ck_assert(*(void**)vector_at(v, 2) == d1);

    vector_free(v);
    free(d3);
    free(d2);
    free(d1);
}
END_TEST

START_TEST(test_vector_insert_resize) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_with_capacity(sizeof(int), 1);
    ck_assert(vector_length(v) == 0);
    ck_assert(vector_capacity(v) == 1);

    vector_insert(v, 0, &values[0]);
    ck_assert(vector_length(v) == 1);
    ck_assert(vector_capacity(v) == 1);

    vector_insert(v, 0, &values[1]);
    ck_assert(vector_length(v) == 2);
    ck_assert(vector_capacity(v) == 2);

    vector_insert(v, 0, &values[2]);
    ck_assert(vector_length(v) == 3);
    ck_assert(vector_capacity(v) == 4);

    vector_insert(v, 0, &values[3]);
    ck_assert(vector_length(v) == 4);
    ck_assert(vector_capacity(v) == 4);

    vector_insert(v, 0, &values[0]);
    ck_assert(vector_length(v) == 5);
    ck_assert(vector_capacity(v) == 8);

    ck_assert(*(int*)vector_at(v, 0) == 15);
    ck_assert(*(int*)vector_at(v, 1) == 69);
    ck_assert(*(int*)vector_at(v, 2) == 30);
    ck_assert(*(int*)vector_at(v, 3) == 21);
    ck_assert(*(int*)vector_at(v, 4) == 15);

    vector_free(v);
}
END_TEST

START_TEST(test_vector_erase) {
    double *result, values[7] = {15.5, 21.7, 30.1, 69.10, -1.56, 10.0, 28.2};
    vector *v = vector_from_array(sizeof(double), 7, values);
    ck_assert(vector_length(v) == 7);
    ck_assert(*(double*)vector_at(v, 0) == 15.5);
    ck_assert(*(double*)vector_at(v, 1) == 21.7);
    ck_assert(*(double*)vector_at(v, 2) == 30.1);
    ck_assert(*(double*)vector_at(v, 3) == 69.10);
    ck_assert(*(double*)vector_at(v, 4) == -1.56);
    ck_assert(*(double*)vector_at(v, 5) == 10.0);
    ck_assert(*(double*)vector_at(v, 6) == 28.2);

    result = vector_erase(v, 3);
    ck_assert(*result == -1.56);
    ck_assert(vector_length(v) == 6);
    ck_assert(*(double*)vector_at(v, 0) == 15.5);
    ck_assert(*(double*)vector_at(v, 1) == 21.7);
    ck_assert(*(double*)vector_at(v, 2) == 30.1);
    ck_assert(*(double*)vector_at(v, 3) == -1.56);
    ck_assert(*(double*)vector_at(v, 4) == 10.0);
    ck_assert(*(double*)vector_at(v, 5) == 28.2);
    ck_assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 4);
    ck_assert(*result == 28.2);
    ck_assert(vector_length(v) == 5);
    ck_assert(*(double*)vector_at(v, 0) == 15.5);
    ck_assert(*(double*)vector_at(v, 1) == 21.7);
    ck_assert(*(double*)vector_at(v, 2) == 30.1);
    ck_assert(*(double*)vector_at(v, 3) == -1.56);
    ck_assert(*(double*)vector_at(v, 4) == 28.2);
    ck_assert(vector_at(v, 5) == NULL);
    ck_assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 0);
    ck_assert(*result == 21.7);
    ck_assert(vector_length(v) == 4);
    ck_assert(*(double*)vector_at(v, 0) == 21.7);
    ck_assert(*(double*)vector_at(v, 1) == 30.1);
    ck_assert(*(double*)vector_at(v, 2) == -1.56);
    ck_assert(*(double*)vector_at(v, 3) == 28.2);
    ck_assert(vector_at(v, 4) == NULL);
    ck_assert(vector_at(v, 5) == NULL);
    ck_assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 3);
    ck_assert(result != NULL);
    ck_assert(vector_length(v) == 3);
    ck_assert(*(double*)vector_at(v, 0) == 21.7);
    ck_assert(*(double*)vector_at(v, 1) == 30.1);
    ck_assert(*(double*)vector_at(v, 2) == -1.56);
    ck_assert(vector_at(v, 3) == NULL);
    ck_assert(vector_at(v, 4) == NULL);
    ck_assert(vector_at(v, 5) == NULL);
    ck_assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 10.000);
    ck_assert(result == NULL);
    ck_assert(vector_length(v) == 3);
    ck_assert(*(double*)vector_at(v, 0) == 21.7);
    ck_assert(*(double*)vector_at(v, 1) == 30.1);
    ck_assert(*(double*)vector_at(v, 2) == -1.56);
    ck_assert(vector_at(v, 4) == NULL);
    ck_assert(vector_at(v, 4) == NULL);
    ck_assert(vector_at(v, 5) == NULL);
    ck_assert(vector_at(v, 6) == NULL);

    result = vector_erase(v, 0);
    ck_assert(*result == 30.1);

    result = vector_erase(v, 0);
    ck_assert(*result == -1.56);

    result = vector_erase(v, 0);
    ck_assert(result != NULL);

    ck_assert(vector_length(v) == 0);
    ck_assert(vector_at(v, 0) == NULL);
    ck_assert(vector_at(v, 1) == NULL);
    ck_assert(vector_at(v, 2) == NULL);
    ck_assert(vector_at(v, 3) == NULL);
    ck_assert(vector_at(v, 4) == NULL);
    ck_assert(vector_at(v, 5) == NULL);
    ck_assert(vector_at(v, 6) == NULL);

    vector_free(v);
}
END_TEST

START_TEST(test_vector_clear) {
    double values[7] = {15.5, 21.7, 30.1, 69.10, -1.56, 10.0, 28.2};
    vector *v = vector_from_array(sizeof(double), 7, values);
    ck_assert(!vector_is_empty(v));
    ck_assert(vector_length(v) == 7);
    ck_assert(vector_capacity(v) == 256);

    vector_clear(v);
    ck_assert(vector_is_empty(v));
    ck_assert(vector_length(v) == 0);
    ck_assert(vector_capacity(v) == 256);

    vector_free(v);
}
END_TEST

START_TEST(test_vector_resize) {
    char* values[4] = {"hello", "world", "welcome", "all"};
    vector *v = vector_from_array(sizeof(char*), 4, values);
    ck_assert(vector_capacity(v) == 256);
    ck_assert(vector_length(v) == 4);

    void *result = vector_resize(v, 2);
    ck_assert(result != NULL);
    ck_assert(vector_capacity(v) == 2);
    ck_assert(vector_length(v) == 2);
    ck_assert(strcmp(vector_at(v, 0), "hello"));
    ck_assert(strcmp(vector_at(v, 0), "world"));
    ck_assert(vector_at(v, 2) == NULL);

    result = vector_resize(v, 0);
    ck_assert(result == NULL);
    ck_assert(vector_capacity(v) == 0);
    ck_assert(vector_length(v) == 0);

    result = vector_resize(v, 256);
    ck_assert(result != NULL);
    ck_assert(vector_capacity(v) == 256);
    ck_assert(vector_length(v) == 0);

    result = vector_push(v, &values[0]);
    ck_assert(vector_capacity(v) == 256);
    ck_assert(vector_length(v) == 1);
    ck_assert(strcmp(result, "hello"));
    ck_assert(strcmp(vector_at(v, 0), "hello"));

    vector_free(v);
}
END_TEST

START_TEST(test_vector_stress) {
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
        ck_assert(*pushed == i);
        ck_assert(length == i + 1);
        ck_assert(capacity >= 256);
        ck_assert(!is_empty);
        ck_assert(*at == i);
        ck_assert(*set == i);
        ck_assert(*begin == 0);
        ck_assert(*back == i);
        ck_assert(end == back + 1);
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
        ck_assert(*popped == nelements - i - 1);
        ck_assert(length == nelements - i - 1);
        ck_assert(capacity >= 256);
        ck_assert(!is_empty);
        ck_assert(*at == i);
        ck_assert(*set == i);
        ck_assert(*begin == 0);
        ck_assert(*back == nelements - i - 2);
        ck_assert(end == back + 1);
    }

    vector_clear(v);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);
    ck_assert(length == 0);
    ck_assert(is_empty);
    ck_assert(capacity == 131072);

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
        ck_assert(*inserted == i);
        ck_assert(length == i + 1);
        ck_assert(capacity == 131072);
        ck_assert(!is_empty);
        ck_assert(*at == i);
        ck_assert(*set == i);
        ck_assert(end == back + 1);
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
        ck_assert(erased != NULL);
        ck_assert(length == nelements - i - 1);
        ck_assert(capacity == 131072);
        ck_assert(!is_empty);
        ck_assert(*at == i);
        ck_assert(*set == i);
        ck_assert(end == back + 1);
    }

    vector_resize(v, 100000);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);
    ck_assert(length == nelements / 2);
    ck_assert(!is_empty);
    ck_assert(capacity == 100000);

    vector_resize(v, 1000);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);
    ck_assert(length == 1000);
    ck_assert(!is_empty);
    ck_assert(capacity == 1000);

    vector_resize(v, 1);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);
    ck_assert(length == 1);
    ck_assert(!is_empty);
    ck_assert(capacity == 1);

    vector_resize(v, 0);
    length = vector_length(v);
    is_empty = vector_is_empty(v);
    capacity = vector_capacity(v);
    ck_assert(length == 0);
    ck_assert(is_empty);
    ck_assert(capacity == 0);

    vector_free(v);
}
END_TEST

Suite* suite_vector() {
    Suite *suite = suite_create("vector");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_vector_init);
    tcase_add_test(test_case, test_vector_init_fail);
    tcase_add_test(test_case, test_vector_with_capacity);
    tcase_add_test(test_case, test_vector_with_capacity_fail);
    tcase_add_test(test_case, test_vector_from_array);
    tcase_add_test(test_case, test_vector_from_array_void_ptrs);
    tcase_add_test(test_case, test_vector_from_array_resize);
    tcase_add_test(test_case, test_vector_from_array_fail);
    tcase_add_test(test_case, test_vector_free);
    tcase_add_test(test_case, test_vector_length);
    tcase_add_test(test_case, test_vector_capacity);
    tcase_add_test(test_case, test_vector_is_empty);
    tcase_add_test(test_case, test_vector_at);
    tcase_add_test(test_case, test_vector_at_fail);
    tcase_add_test(test_case, test_vector_set);
    tcase_add_test(test_case, test_vector_set_fail);
    tcase_add_test(test_case, test_vector_begin);
    tcase_add_test(test_case, test_vector_back);
    tcase_add_test(test_case, test_vector_end);
    tcase_add_test(test_case, test_vector_pointers);
    tcase_add_test(test_case, test_vector_push);
    tcase_add_test(test_case, test_vector_push_void_ptrs);
    tcase_add_test(test_case, test_vector_push_resize);
    tcase_add_test(test_case, test_vector_pop);
    tcase_add_test(test_case, test_vector_insert);
    tcase_add_test(test_case, test_vector_insert_void_ptrs);
    tcase_add_test(test_case, test_vector_insert_resize);
    tcase_add_test(test_case, test_vector_erase);
    tcase_add_test(test_case, test_vector_clear);
    tcase_add_test(test_case, test_vector_resize);
    tcase_add_test(test_case, test_vector_stress);
    suite_add_tcase(suite, test_case);
    return suite;
}
