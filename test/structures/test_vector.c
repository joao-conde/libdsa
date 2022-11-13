#include <check.h>

#include <stdio.h>

#include "../../include/vector.h"

START_TEST(test_vector) {
    Vector *vec = vector(sizeof(int), 10);
    ck_assert(vector_length(vec) == 0);
    ck_assert(vector_capacity(vec) == 10);
}
END_TEST

START_TEST(test_vector_length) {
    Vector *vec = vector(sizeof(int), 10);
    ck_assert(vector_length(vec) == 0);
}
END_TEST

START_TEST(test_vector_capacity) {
    Vector *vec = vector(sizeof(int), 10);
    ck_assert(vector_capacity(vec) == 10);
}
END_TEST

START_TEST(test_vector_get) {
    Vector *vec = vector(sizeof(int), 10);
    int* result = vector_get(vec, 0);
    ck_assert(result == NULL);

    int value = 3;
    result = vector_push(vec, &value);
    ck_assert(*result == 3);

    result = vector_get(vec, 0);
    ck_assert(*result == 3);
}
END_TEST

Suite* suite_vector() {
    Suite *suite = suite_create("vector");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_vector);
    tcase_add_test(test_case, test_vector_length);
    tcase_add_test(test_case, test_vector_capacity);
    tcase_add_test(test_case, test_vector_get);
    suite_add_tcase(suite, test_case);
    return suite;
}
