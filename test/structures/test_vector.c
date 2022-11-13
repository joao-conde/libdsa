#include <check.h>

#include <stdio.h>

#include "../../include/vector.h"

START_TEST(test_vector) {
    Vector *vec = vector(sizeof(int));
    ck_assert(vector_length(vec) == 0);
    ck_assert(vector_capacity(vec) == 256);
    vector_free(vec);
}
END_TEST

START_TEST(test_vector_with_capacity) {
    Vector *vec = vector_with_capacity(sizeof(int), 10);
    ck_assert(vector_length(vec) == 0);
    ck_assert(vector_capacity(vec) == 10);
    vector_free(vec);
}
END_TEST

START_TEST(test_vector_from_array) {
    int array[4] = {15, 21, 30, 69};
    Vector *vec = vector_from_array(sizeof(int), 4, array);
    ck_assert(vector_length(vec) == 4);
    ck_assert(vector_capacity(vec) == 256);

    for(int i = 0; i < 4; i++) {
        int *at = vector_at(vec, i);
        ck_assert(*at == array[i]);
    }

    vector_free(vec);
}
END_TEST

START_TEST(test_vector_free) {
    Vector *vec = vector(sizeof(int));
    vector_free(vec);
}
END_TEST

START_TEST(test_vector_length) {
    Vector *vec = vector(sizeof(int));
    ck_assert(vector_length(vec) == 0);
    vector_free(vec);
}
END_TEST

START_TEST(test_vector_capacity) {
    Vector *vec = vector(sizeof(int));
    ck_assert(vector_capacity(vec) == 256);
    vector_free(vec);

    vec = vector_with_capacity(sizeof(int), 10);
    ck_assert(vector_capacity(vec) == 10);
    vector_free(vec);
}
END_TEST

START_TEST(test_vector_at) {
    Vector *vec = vector(sizeof(int));
    int* result = vector_at(vec, 0);
    ck_assert(result == NULL);
    vector_free(vec);

    int array[4] = {15, 21, 30, 69};
    vec = vector_from_array(sizeof(int), 4, array);
    for(int i = 0; i < 4; i++) {
        int *at = vector_at(vec, i);
        ck_assert(*at == array[i]);
    }
    vector_free(vec);
}
END_TEST

Suite* suite_vector() {
    Suite *suite = suite_create("vector");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_vector);
    tcase_add_test(test_case, test_vector_with_capacity);
    tcase_add_test(test_case, test_vector_from_array);
    tcase_add_test(test_case, test_vector_free);
    tcase_add_test(test_case, test_vector_length);
    tcase_add_test(test_case, test_vector_capacity);
    tcase_add_test(test_case, test_vector_at);
    suite_add_tcase(suite, test_case);
    return suite;
}
