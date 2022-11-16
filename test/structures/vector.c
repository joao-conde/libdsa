#include <check.h>
#include <stdint.h>
#include <string.h>

#include "../../include/vector.h"

START_TEST(test_vec) {
    vector *v = vector_init(sizeof(int));
    ck_assert(vector_length(v) == 0);
    ck_assert(vector_capacity(v) == 256);
    vector_free(v);
}
END_TEST

START_TEST(test_vec_fail) {
    vector *v = vector_init(SIZE_MAX);
    ck_assert(v == NULL);
}
END_TEST

START_TEST(test_with_capacity) {
    vector *v = vector_with_capacity(sizeof(int), 10);
    ck_assert(vector_length(v) == 0);
    ck_assert(vector_capacity(v) == 10);
    vector_free(v);
}
END_TEST

START_TEST(test_with_capacity_fail) {
    vector *v = vector_with_capacity(SIZE_MAX, 1000);
    ck_assert(v == NULL);
}
END_TEST

START_TEST(test_from_array) {
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

START_TEST(test_from_array_resize) {
    int *values = calloc(260, sizeof(int));
    vector *v = vector_from_array(sizeof(int), 260, values);
    ck_assert(vector_length(v) == 260);
    ck_assert(vector_capacity(v) == 520);
    vector_free(v);
    free(values);
}
END_TEST

START_TEST(test_from_array_fail) {
    vector *v = vector_from_array(SIZE_MAX, 1, NULL);
    ck_assert(v == NULL);
}
END_TEST

START_TEST(test_free) {
    vector *v = vector_init(sizeof(int));
    vector_free(v);
}
END_TEST

START_TEST(test_length) {
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

START_TEST(test_capacity) {
    vector *v = vector_with_capacity(sizeof(int), 10);
    ck_assert(vector_capacity(v) == 10);
    vector_free(v);
}
END_TEST

START_TEST(test_empty) {
    vector *v = vector_init(sizeof(int));
    ck_assert(vector_empty(v) == true);

    int value = -10;
    vector_push(v, &value);
    ck_assert(vector_empty(v) == false);

    vector_pop(v);
    ck_assert(vector_empty(v) == true);

    vector_free(v);
}
END_TEST

START_TEST(test_at) {
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

START_TEST(test_at_fail) {
    vector *v = vector_init(sizeof(int));
    ck_assert(vector_at(v, 0) == NULL);
    vector_free(v);
}
END_TEST

START_TEST(test_set) {
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

START_TEST(test_set_fail) {
    int value = 3;
    vector *v = vector_init(sizeof(int));
    ck_assert(vector_set(v, 0, &value) == NULL);
    vector_free(v);
}
END_TEST

START_TEST(test_begin) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_from_array(sizeof(int), 4, values);
    ck_assert(*(int*)vector_begin(v) == 15);
    ck_assert(vector_begin(v) == vector_at(v, 0));
    vector_free(v);
}
END_TEST

START_TEST(test_back) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_back(v) == vector_at(v, 3));
    vector_free(v);
}
END_TEST

START_TEST(test_end) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_end(v) == vector_at(v, 3) + sizeof(int));
    vector_free(v);
}
END_TEST

START_TEST(test_push) {
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

START_TEST(test_push_resize) {
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

START_TEST(test_pop) {
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

START_TEST(test_insert) {
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

START_TEST(test_insert_resize) {
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

START_TEST(test_erase) {
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

START_TEST(test_clear) {
    double values[7] = {15.5, 21.7, 30.1, 69.10, -1.56, 10.0, 28.2};
    vector *v = vector_from_array(sizeof(double), 7, values);
    ck_assert(!vector_empty(v));
    ck_assert(vector_length(v) == 7);
    ck_assert(vector_capacity(v) == 256);

    vector_clear(v);
    ck_assert(vector_empty(v));
    ck_assert(vector_length(v) == 0);
    ck_assert(vector_capacity(v) == 256);

    vector_free(v);
}
END_TEST

START_TEST(test_resize) {
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

Suite* suite_vector() {
    Suite *suite = suite_create("vector");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_vec);
    tcase_add_test(test_case, test_vec_fail);
    tcase_add_test(test_case, test_with_capacity);
    tcase_add_test(test_case, test_with_capacity_fail);
    tcase_add_test(test_case, test_from_array);
    tcase_add_test(test_case, test_from_array_resize);
    tcase_add_test(test_case, test_from_array_fail);
    tcase_add_test(test_case, test_free);
    tcase_add_test(test_case, test_length);
    tcase_add_test(test_case, test_capacity);
    tcase_add_test(test_case, test_empty);
    tcase_add_test(test_case, test_at);
    tcase_add_test(test_case, test_at_fail);
    tcase_add_test(test_case, test_set);
    tcase_add_test(test_case, test_set_fail);
    tcase_add_test(test_case, test_begin);
    tcase_add_test(test_case, test_back);
    tcase_add_test(test_case, test_end);
    tcase_add_test(test_case, test_push);
    tcase_add_test(test_case, test_push_resize);
    tcase_add_test(test_case, test_pop);
    tcase_add_test(test_case, test_insert);
    tcase_add_test(test_case, test_insert_resize);
    tcase_add_test(test_case, test_erase);
    tcase_add_test(test_case, test_clear);
    tcase_add_test(test_case, test_resize);
    suite_add_tcase(suite, test_case);
    return suite;
}
