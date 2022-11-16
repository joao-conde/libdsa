#include <check.h>
#include <stdint.h>
#include <string.h>

#include "../../include/vector.h"

START_TEST(test_vec) {
    vector *v = vec(sizeof(int));
    ck_assert(vec_length(v) == 0);
    ck_assert(vec_capacity(v) == 256);
    vec_free(v);
}
END_TEST

START_TEST(test_vec_fail) {
    vector *v = vec(SIZE_MAX);
    ck_assert(v == NULL);
}
END_TEST

START_TEST(test_with_capacity) {
    vector *v = vec_with_capacity(sizeof(int), 10);
    ck_assert(vec_length(v) == 0);
    ck_assert(vec_capacity(v) == 10);
    vec_free(v);
}
END_TEST

START_TEST(test_with_capacity_fail) {
    vector *v = vec_with_capacity(SIZE_MAX, 1000);
    ck_assert(v == NULL);
}
END_TEST

START_TEST(test_from_array) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(int), 4, values);
    ck_assert(vec_length(v) == 4);
    ck_assert(vec_capacity(v) == 256);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 30);
    ck_assert(*(int*)vec_at(v, 3) == 69);
    ck_assert(vec_at(v, 4) == NULL);
    vec_free(v);
}
END_TEST

START_TEST(test_from_array_resize) {
    int *values = calloc(260, sizeof(int));
    vector *v = vec_from_array(sizeof(int), 260, values);
    ck_assert(vec_length(v) == 260);
    ck_assert(vec_capacity(v) == 520);
    vec_free(v);
    free(values);
}
END_TEST

START_TEST(test_from_array_fail) {
    vector *v = vec_from_array(SIZE_MAX, 1, NULL);
    ck_assert(v == NULL);
}
END_TEST

START_TEST(test_free) {
    vector *v = vec(sizeof(int));
    vec_free(v);
}
END_TEST

START_TEST(test_length) {
    float value = 3.5;
    vector *v = vec(sizeof(float));
    ck_assert(vec_length(v) == 0);

    vec_push(v, &value);
    vec_push(v, &value);
    vec_push(v, &value);
    ck_assert(vec_length(v) == 3);

    vec_free(v);
}
END_TEST

START_TEST(test_capacity) {
    vector *v = vec_with_capacity(sizeof(int), 10);
    ck_assert(vec_capacity(v) == 10);
    vec_free(v);
}
END_TEST

START_TEST(test_empty) {
    vector *v = vec(sizeof(int));
    ck_assert(vec_empty(v) == true);

    int value = -10;
    vec_push(v, &value);
    ck_assert(vec_empty(v) == false);

    vec_pop(v);
    ck_assert(vec_empty(v) == true);

    vec_free(v);
}
END_TEST

START_TEST(test_at) {
    unsigned int values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(unsigned int), 4, values);
    ck_assert(*(unsigned int*)vec_at(v, 0) == 15);
    ck_assert(*(unsigned int*)vec_at(v, 1) == 21);
    ck_assert(*(unsigned int*)vec_at(v, 2) == 30);
    ck_assert(*(unsigned int*)vec_at(v, 3) == 69);
    ck_assert(vec_at(v, 4) == NULL);
    vec_free(v);
}
END_TEST

START_TEST(test_at_fail) {
    vector *v = vec(sizeof(int));
    ck_assert(vec_at(v, 0) == NULL);
    vec_free(v);
}
END_TEST

START_TEST(test_begin) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(int), 4, values);
    ck_assert(*(int*)vec_begin(v) == 15);
    ck_assert(vec_begin(v) == vec_at(v, 0));
    vec_free(v);
}
END_TEST

START_TEST(test_end) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(int), 4, values);
    ck_assert(vec_end(v) == vec_at(v, 3) + sizeof(int));
    vec_free(v);
}
END_TEST

START_TEST(test_push) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    vector *v = vec(sizeof(int));

    result = vec_push(v, &values[0]);
    ck_assert(*result == 51);

    result = vec_push(v, &values[1]);
    ck_assert(*result == 12);

    result = vec_push(v, &values[2]);
    ck_assert(*result == -123);

    result = vec_push(v, &values[3]);
    ck_assert(*result == 1000);

    result = vec_push(v, &values[4]);
    ck_assert(*result == -1);

    ck_assert(vec_length(v) == 5);
    ck_assert(*(int*)vec_at(v, 0) == 51);
    ck_assert(*(int*)vec_at(v, 1) == 12);
    ck_assert(*(int*)vec_at(v, 2) == -123);
    ck_assert(*(int*)vec_at(v, 3) == 1000);
    ck_assert(*(int*)vec_at(v, 4) == -1);
    ck_assert(vec_at(v, 5) == NULL);

    vec_free(v);
}
END_TEST

START_TEST(test_push_resize) {
    int values[5] = {0, -10, 50, 30, -57};

    vector *v = vec_with_capacity(sizeof(int), 1);
    ck_assert(vec_length(v) == 0);
    ck_assert(vec_capacity(v) == 1);

    vec_push(v, &values[0]);
    ck_assert(vec_length(v) == 1);
    ck_assert(vec_capacity(v) == 1);
    ck_assert(*(int*)vec_at(v, 0) == 0);

    vec_push(v, &values[1]);
    ck_assert(vec_length(v) == 2);
    ck_assert(vec_capacity(v) == 2);
    ck_assert(*(int*)vec_at(v, 0) == 0);
    ck_assert(*(int*)vec_at(v, 1) == -10);

    vec_push(v, &values[2]);
    ck_assert(vec_length(v) == 3);
    ck_assert(vec_capacity(v) == 4);
    ck_assert(*(int*)vec_at(v, 0) == 0);
    ck_assert(*(int*)vec_at(v, 1) == -10);
    ck_assert(*(int*)vec_at(v, 2) == 50);

    vec_push(v, &values[3]);
    ck_assert(vec_length(v) == 4);
    ck_assert(vec_capacity(v) == 4);
    ck_assert(*(int*)vec_at(v, 0) == 0);
    ck_assert(*(int*)vec_at(v, 1) == -10);
    ck_assert(*(int*)vec_at(v, 2) == 50);
    ck_assert(*(int*)vec_at(v, 3) == 30);

    vec_push(v, &values[4]);
    ck_assert(vec_length(v) == 5);
    ck_assert(vec_capacity(v) == 8);
    ck_assert(*(int*)vec_at(v, 0) == 0);
    ck_assert(*(int*)vec_at(v, 1) == -10);
    ck_assert(*(int*)vec_at(v, 2) == 50);
    ck_assert(*(int*)vec_at(v, 3) == 30);
    ck_assert(*(int*)vec_at(v, 4) == -57);

    vec_free(v);
}
END_TEST

START_TEST(test_pop) {
    int *result, values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(int), 4, values);
    ck_assert(vec_length(v) == 4);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 30);
    ck_assert(*(int*)vec_at(v, 3) == 69);

    result = vec_pop(v);
    ck_assert(*result == 69);
    ck_assert(vec_length(v) == 3);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 30);
    ck_assert(vec_at(v, 3) == NULL);

    result = vec_pop(v);
    ck_assert(*result == 30);
    ck_assert(vec_length(v) == 2);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(vec_at(v, 2) == NULL);
    ck_assert(vec_at(v, 3) == NULL);

    result = vec_pop(v);
    ck_assert(*result == 21);
    ck_assert(vec_length(v) == 1);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(vec_at(v, 1) == NULL);
    ck_assert(vec_at(v, 2) == NULL);
    ck_assert(vec_at(v, 3) == NULL);

    result = vec_pop(v);
    ck_assert(*result == 15);
    ck_assert(vec_length(v) == 0);
    ck_assert(vec_at(v, 0) == NULL);
    ck_assert(vec_at(v, 1) == NULL);
    ck_assert(vec_at(v, 2) == NULL);
    ck_assert(vec_at(v, 3) == NULL);

    result = vec_pop(v);
    ck_assert(result == NULL);
    ck_assert(vec_length(v) == 0);
    ck_assert(vec_at(v, 0) == NULL);
    ck_assert(vec_at(v, 1) == NULL);
    ck_assert(vec_at(v, 2) == NULL);
    ck_assert(vec_at(v, 3) == NULL);

    vec_free(v);
}
END_TEST

START_TEST(test_insert) {
    int *result, values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(int), 4, values);
    ck_assert(vec_length(v) == 4);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 30);
    ck_assert(*(int*)vec_at(v, 3) == 69);

    result = vec_insert(v, 2, &values[3]);
    ck_assert(*result == 69);
    ck_assert(vec_length(v) == 5);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 69);
    ck_assert(*(int*)vec_at(v, 3) == 30);
    ck_assert(*(int*)vec_at(v, 4) == 69);

    result = vec_insert(v, 0, &values[2]);
    ck_assert(*result == 30);
    ck_assert(vec_length(v) == 6);
    ck_assert(*(int*)vec_at(v, 0) == 30);
    ck_assert(*(int*)vec_at(v, 1) == 15);
    ck_assert(*(int*)vec_at(v, 2) == 21);
    ck_assert(*(int*)vec_at(v, 3) == 69);
    ck_assert(*(int*)vec_at(v, 4) == 30);
    ck_assert(*(int*)vec_at(v, 5) == 69);

    result = vec_insert(v, 6, &values[0]);
    ck_assert(*result == 15);
    ck_assert(vec_length(v) == 7);
    ck_assert(*(int*)vec_at(v, 0) == 30);
    ck_assert(*(int*)vec_at(v, 1) == 15);
    ck_assert(*(int*)vec_at(v, 2) == 21);
    ck_assert(*(int*)vec_at(v, 3) == 69);
    ck_assert(*(int*)vec_at(v, 4) == 30);
    ck_assert(*(int*)vec_at(v, 5) == 69);
    ck_assert(*(int*)vec_at(v, 6) == 15);

    result = vec_insert(v, 1000, &values[0]);
    ck_assert(result == NULL);
    ck_assert(vec_length(v) == 7);
    ck_assert(*(int*)vec_at(v, 0) == 30);
    ck_assert(*(int*)vec_at(v, 1) == 15);
    ck_assert(*(int*)vec_at(v, 2) == 21);
    ck_assert(*(int*)vec_at(v, 3) == 69);
    ck_assert(*(int*)vec_at(v, 4) == 30);
    ck_assert(*(int*)vec_at(v, 5) == 69);
    ck_assert(*(int*)vec_at(v, 6) == 15);

    vec_free(v);
}
END_TEST

START_TEST(test_insert_resize) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vec_with_capacity(sizeof(int), 1);
    ck_assert(vec_length(v) == 0);
    ck_assert(vec_capacity(v) == 1);

    vec_insert(v, 0, &values[0]);
    ck_assert(vec_length(v) == 1);
    ck_assert(vec_capacity(v) == 1);

    vec_insert(v, 0, &values[1]);
    ck_assert(vec_length(v) == 2);
    ck_assert(vec_capacity(v) == 2);

    vec_insert(v, 0, &values[2]);
    ck_assert(vec_length(v) == 3);
    ck_assert(vec_capacity(v) == 4);

    vec_insert(v, 0, &values[3]);
    ck_assert(vec_length(v) == 4);
    ck_assert(vec_capacity(v) == 4);

    vec_insert(v, 0, &values[0]);
    ck_assert(vec_length(v) == 5);
    ck_assert(vec_capacity(v) == 8);

    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 69);
    ck_assert(*(int*)vec_at(v, 2) == 30);
    ck_assert(*(int*)vec_at(v, 3) == 21);
    ck_assert(*(int*)vec_at(v, 4) == 15);

    vec_free(v);
}
END_TEST

START_TEST(test_erase) {
    double *result, values[7] = {15.5, 21.7, 30.1, 69.10, -1.56, 10.0, 28.2};
    vector *v = vec_from_array(sizeof(double), 7, values);
    ck_assert(vec_length(v) == 7);
    ck_assert(*(double*)vec_at(v, 0) == 15.5);
    ck_assert(*(double*)vec_at(v, 1) == 21.7);
    ck_assert(*(double*)vec_at(v, 2) == 30.1);
    ck_assert(*(double*)vec_at(v, 3) == 69.10);
    ck_assert(*(double*)vec_at(v, 4) == -1.56);
    ck_assert(*(double*)vec_at(v, 5) == 10.0);
    ck_assert(*(double*)vec_at(v, 6) == 28.2);

    result = vec_erase(v, 3);
    ck_assert(*result == -1.56);
    ck_assert(vec_length(v) == 6);
    ck_assert(*(double*)vec_at(v, 0) == 15.5);
    ck_assert(*(double*)vec_at(v, 1) == 21.7);
    ck_assert(*(double*)vec_at(v, 2) == 30.1);
    ck_assert(*(double*)vec_at(v, 3) == -1.56);
    ck_assert(*(double*)vec_at(v, 4) == 10.0);
    ck_assert(*(double*)vec_at(v, 5) == 28.2);
    ck_assert(vec_at(v, 6) == NULL);

    result = vec_erase(v, 4);
    ck_assert(*result == 28.2);
    ck_assert(vec_length(v) == 5);
    ck_assert(*(double*)vec_at(v, 0) == 15.5);
    ck_assert(*(double*)vec_at(v, 1) == 21.7);
    ck_assert(*(double*)vec_at(v, 2) == 30.1);
    ck_assert(*(double*)vec_at(v, 3) == -1.56);
    ck_assert(*(double*)vec_at(v, 4) == 28.2);
    ck_assert(vec_at(v, 5) == NULL);
    ck_assert(vec_at(v, 6) == NULL);

    result = vec_erase(v, 0);
    ck_assert(*result == 21.7);
    ck_assert(vec_length(v) == 4);
    ck_assert(*(double*)vec_at(v, 0) == 21.7);
    ck_assert(*(double*)vec_at(v, 1) == 30.1);
    ck_assert(*(double*)vec_at(v, 2) == -1.56);
    ck_assert(*(double*)vec_at(v, 3) == 28.2);
    ck_assert(vec_at(v, 4) == NULL);
    ck_assert(vec_at(v, 5) == NULL);
    ck_assert(vec_at(v, 6) == NULL);

    result = vec_erase(v, 3);
    ck_assert(result != NULL);
    ck_assert(vec_length(v) == 3);
    ck_assert(*(double*)vec_at(v, 0) == 21.7);
    ck_assert(*(double*)vec_at(v, 1) == 30.1);
    ck_assert(*(double*)vec_at(v, 2) == -1.56);
    ck_assert(vec_at(v, 3) == NULL);
    ck_assert(vec_at(v, 4) == NULL);
    ck_assert(vec_at(v, 5) == NULL);
    ck_assert(vec_at(v, 6) == NULL);

    result = vec_erase(v, 10.000);
    ck_assert(result == NULL);
    ck_assert(vec_length(v) == 3);
    ck_assert(*(double*)vec_at(v, 0) == 21.7);
    ck_assert(*(double*)vec_at(v, 1) == 30.1);
    ck_assert(*(double*)vec_at(v, 2) == -1.56);
    ck_assert(vec_at(v, 4) == NULL);
    ck_assert(vec_at(v, 4) == NULL);
    ck_assert(vec_at(v, 5) == NULL);
    ck_assert(vec_at(v, 6) == NULL);

    result = vec_erase(v, 0);
    ck_assert(*result == 30.1);

    result = vec_erase(v, 0);
    ck_assert(*result == -1.56);

    result = vec_erase(v, 0);
    ck_assert(result != NULL);

    ck_assert(vec_length(v) == 0);
    ck_assert(vec_at(v, 0) == NULL);
    ck_assert(vec_at(v, 1) == NULL);
    ck_assert(vec_at(v, 2) == NULL);
    ck_assert(vec_at(v, 3) == NULL);
    ck_assert(vec_at(v, 4) == NULL);
    ck_assert(vec_at(v, 5) == NULL);
    ck_assert(vec_at(v, 6) == NULL);

    vec_free(v);
}
END_TEST

START_TEST(test_resize) {
    char* values[4] = {"hello", "world", "welcome", "all"};
    vector *v = vec_from_array(sizeof(char*), 4, values);
    ck_assert(vec_capacity(v) == 256);
    ck_assert(vec_length(v) == 4);

    void *result = vec_resize(v, 2);
    ck_assert(result != NULL);
    ck_assert(vec_capacity(v) == 2);
    ck_assert(vec_length(v) == 2);
    ck_assert(strcmp(vec_at(v, 0), "hello"));
    ck_assert(strcmp(vec_at(v, 0), "world"));
    ck_assert(vec_at(v, 2) == NULL);

    result = vec_resize(v, 0);
    ck_assert(result == NULL);
    ck_assert(vec_capacity(v) == 0);
    ck_assert(vec_length(v) == 0);

    result = vec_resize(v, 256);
    ck_assert(result != NULL);
    ck_assert(vec_capacity(v) == 256);
    ck_assert(vec_length(v) == 0);

    vec_free(v);
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
    tcase_add_test(test_case, test_begin);
    tcase_add_test(test_case, test_end);
    tcase_add_test(test_case, test_push);
    tcase_add_test(test_case, test_push_resize);
    tcase_add_test(test_case, test_pop);
    tcase_add_test(test_case, test_insert);
    tcase_add_test(test_case, test_insert_resize);
    tcase_add_test(test_case, test_erase);
    tcase_add_test(test_case, test_resize);
    suite_add_tcase(suite, test_case);
    return suite;
}
