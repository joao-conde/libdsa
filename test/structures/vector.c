#include <check.h>
#include <limits.h>

#include "../../include/vector.h"

#include <stdio.h>

START_TEST(test_vector) {
    Vector *vec = vector(sizeof(int));
    ck_assert(vector_length(vec) == 0);
    ck_assert(vector_capacity(vec) == 256);
    vector_free(vec);
}
END_TEST

START_TEST(test_vector_fail) {
    Vector *vec = vector(UINT_MAX);
    ck_assert(vec == NULL);
}
END_TEST

START_TEST(test_with_capacity) {
    Vector *vec = vector_with_capacity(sizeof(int), 10);
    ck_assert(vector_length(vec) == 0);
    ck_assert(vector_capacity(vec) == 10);
    vector_free(vec);
}
END_TEST

START_TEST(test_with_capacity_fail) {
    Vector *vec = vector_with_capacity(UINT_MAX, 100);
    ck_assert(vec == NULL);
}
END_TEST

START_TEST(test_from_array) {
    int array[4] = {15, 21, 30, 69};
    Vector *vec;

    vec = vector_from_array(sizeof(int), 4, array);
    ck_assert(vector_length(vec) == 4);
    ck_assert(vector_capacity(vec) == 256);
    for (int i = 0; i < 4; i++) {
        int *at = vector_at(vec, i);
        ck_assert(*at == array[i]);
    }
    vector_free(vec);

    vec = vector_from_array(sizeof(int), 260, array);
    ck_assert(vector_length(vec) == 260);
    ck_assert(vector_capacity(vec) == 520);
    vector_free(vec);
}
END_TEST

START_TEST(test_from_array_fail) {
    Vector *vec = vector_from_array(UINT_MAX, 1, NULL);
    ck_assert(vec == NULL);
}
END_TEST

START_TEST(test_free) {
    Vector *vec = vector(sizeof(int));
    vector_free(vec);
}
END_TEST

START_TEST(test_length) {
    int value = 3;
    Vector *vec = vector(sizeof(int));
    ck_assert(vector_length(vec) == 0);

    vector_push(vec, &value);
    vector_push(vec, &value);
    vector_push(vec, &value);
    ck_assert(vector_length(vec) == 3);

    vector_free(vec);
}
END_TEST

START_TEST(test_capacity) {
    Vector *vec;

    vec = vector(sizeof(int));
    ck_assert(vector_capacity(vec) == 256);
    vector_free(vec);

    vec = vector_with_capacity(sizeof(int), 10);
    ck_assert(vector_capacity(vec) == 10);
    vector_free(vec);
}
END_TEST

START_TEST(test_at) {
    int array[4] = {15, 21, 30, 69};
    Vector *vec = vector_from_array(sizeof(int), 4, array);
    for (int i = 0; i < 4; i++) {
        int *at = vector_at(vec, i);
        ck_assert(*at == array[i]);
    }
    vector_free(vec);
}
END_TEST

START_TEST(test_at_fail) {
    Vector *vec = vector(sizeof(int));
    int *at = vector_at(vec, 0);
    ck_assert(at == NULL);
    vector_free(vec);
}
END_TEST

START_TEST(test_push) {
    int *at;
    Vector *vec = vector(sizeof(int));
    int values[5] = {51, 12, -123, 1000, -1};
    for (int i = 0; i < 5; i++) {
        vector_push(vec, &values[i]);
    }

    ck_assert(vector_length(vec) == 5);
    for (int i = 0; i < 5; i++) {
        at = vector_at(vec, i);
        ck_assert(*at == values[i]);
    }

    at = vector_at(vec, 5);
    ck_assert(at == NULL);

    vector_free(vec);
}
END_TEST

START_TEST(test_push_resize) {
    int values[5] = {0, -10, 50, 30, -57};

    Vector *vec = vector_with_capacity(sizeof(int), 1);
    ck_assert(vector_length(vec) == 0);
    ck_assert(vector_capacity(vec) == 1);

    vector_push(vec, &values[0]);
    ck_assert(vector_length(vec) == 1);
    ck_assert(vector_capacity(vec) == 1);
    ck_assert(*(int*)vector_at(vec, 0) == values[0]);

    vector_push(vec, &values[1]);
    ck_assert(vector_length(vec) == 2);
    ck_assert(vector_capacity(vec) == 2);
    ck_assert(*(int*)vector_at(vec, 0) == values[0]);
    ck_assert(*(int*)vector_at(vec, 1) == values[1]);

    vector_push(vec, &values[2]);
    ck_assert(vector_length(vec) == 3);
    ck_assert(vector_capacity(vec) == 4);
    ck_assert(*(int*)vector_at(vec, 0) == values[0]);
    ck_assert(*(int*)vector_at(vec, 1) == values[1]);
    ck_assert(*(int*)vector_at(vec, 2) == values[2]);

    vector_push(vec, &values[3]);
    ck_assert(vector_length(vec) == 4);
    ck_assert(vector_capacity(vec) == 4);
    ck_assert(*(int*)vector_at(vec, 0) == values[0]);
    ck_assert(*(int*)vector_at(vec, 1) == values[1]);
    ck_assert(*(int*)vector_at(vec, 2) == values[2]);
    ck_assert(*(int*)vector_at(vec, 3) == values[3]);

    vector_push(vec, &values[4]);
    ck_assert(vector_length(vec) == 5);
    ck_assert(vector_capacity(vec) == 8);
    ck_assert(*(int*)vector_at(vec, 0) == values[0]);
    ck_assert(*(int*)vector_at(vec, 1) == values[1]);
    ck_assert(*(int*)vector_at(vec, 2) == values[2]);
    ck_assert(*(int*)vector_at(vec, 3) == values[3]);
    ck_assert(*(int*)vector_at(vec, 4) == values[4]);

    vector_free(vec);
}
END_TEST

START_TEST(test_resize) {
    int array[4] = {15, 21, 30, 69};
    Vector *vec = vector_from_array(sizeof(int), 4, array);
    ck_assert(vector_capacity(vec) == 256);
    ck_assert(vector_length(vec) == 4);
    for (int i = 0; i < 4; i++) {
        ck_assert(*(int*)vector_at(vec, i) == array[i]);
    }

    void *result = vector_resize(vec, 2);
    ck_assert(result != NULL);
    ck_assert(vector_capacity(vec) == 2);
    ck_assert(vector_length(vec) == 2);
    for (int i = 0; i < 2; i++) {
        ck_assert(*(int*)vector_at(vec, i) == array[i]);
    }
    ck_assert(vector_at(vec, 2) == NULL);

    vector_free(vec);
}
END_TEST

Suite* suite_vector() {
    Suite *suite = suite_create("vector");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_vector);
    tcase_add_test(test_case, test_vector_fail);
    tcase_add_test(test_case, test_with_capacity);
    tcase_add_test(test_case, test_with_capacity_fail);
    tcase_add_test(test_case, test_from_array);
    tcase_add_test(test_case, test_from_array_fail);
    tcase_add_test(test_case, test_free);
    tcase_add_test(test_case, test_length);
    tcase_add_test(test_case, test_capacity);
    tcase_add_test(test_case, test_at);
    tcase_add_test(test_case, test_at_fail);
    tcase_add_test(test_case, test_push);
    tcase_add_test(test_case, test_push_resize);
    tcase_add_test(test_case, test_resize);
    suite_add_tcase(suite, test_case);
    return suite;
}
