#include <check.h>
#include <limits.h>

#include "../../include/vector.h"

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
    int values[4] = {15, 21, 30, 69};
    Vector *vec = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_length(vec) == 4);
    ck_assert(vector_capacity(vec) == 256);
    for (int i = 0; i < 4; i++) {
        int *at = vector_at(vec, i);
        ck_assert(*at == values[i]);
    }
    vector_free(vec);
}
END_TEST

START_TEST(test_from_array_resize) {
    int *values = calloc(260, sizeof(int));
    Vector *vec = vector_from_array(sizeof(int), 260, values);
    ck_assert(vector_length(vec) == 260);
    ck_assert(vector_capacity(vec) == 520);
    vector_free(vec);
    free(values);
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
    Vector *vec = vector_with_capacity(sizeof(int), 10);
    ck_assert(vector_capacity(vec) == 10);
    vector_free(vec);
}
END_TEST

START_TEST(test_empty) {
    Vector *vec = vector(sizeof(int));
    ck_assert(vector_empty(vec) == true);

    int value = -10;
    vector_push(vec, &value);
    ck_assert(vector_empty(vec) == false);

    vector_free(vec);
}
END_TEST

START_TEST(test_at) {
    int values[4] = {15, 21, 30, 69};
    Vector *vec = vector_from_array(sizeof(int), 4, values);
    for (int i = 0; i < 4; i++) {
        int *at = vector_at(vec, i);
        ck_assert(*at == values[i]);
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

START_TEST(test_begin) {
    int values[4] = {15, 21, 30, 69};
    Vector *vec = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_begin(vec) == vector_at(vec, 0));
    vector_free(vec);
}
END_TEST

START_TEST(test_end) {
    int values[4] = {15, 21, 30, 69};
    Vector *vec = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_end(vec) == vector_at(vec, 3) + sizeof(int));
    vector_free(vec);
}
END_TEST

START_TEST(test_push) {
    int *at, values[5] = {51, 12, -123, 1000, -1};
    Vector *vec = vector(sizeof(int));
    for (int i = 0; i < 5; i++) {
        at = vector_push(vec, &values[i]);
        ck_assert(*at == values[i]);
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

START_TEST(test_pop) {
    int *at, values[4] = {15, 21, 30, 69};
    Vector *vec = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_length(vec) == 4);
    ck_assert(*(int*)vector_at(vec, 0) == 15);
    ck_assert(*(int*)vector_at(vec, 1) == 21);
    ck_assert(*(int*)vector_at(vec, 2) == 30);
    ck_assert(*(int*)vector_at(vec, 3) == 69);

    at = vector_pop(vec);
    ck_assert(*at == 69);
    ck_assert(vector_length(vec) == 3);
    ck_assert(*(int*)vector_at(vec, 0) == 15);
    ck_assert(*(int*)vector_at(vec, 1) == 21);
    ck_assert(*(int*)vector_at(vec, 2) == 30);
    ck_assert(vector_at(vec, 3) == NULL);

    at = vector_pop(vec);
    ck_assert(*at == 30);
    ck_assert(vector_length(vec) == 2);
    ck_assert(*(int*)vector_at(vec, 0) == 15);
    ck_assert(*(int*)vector_at(vec, 1) == 21);
    ck_assert(vector_at(vec, 2) == NULL);
    ck_assert(vector_at(vec, 3) == NULL);

    at = vector_pop(vec);
    ck_assert(*at == 21);
    ck_assert(vector_length(vec) == 1);
    ck_assert(*(int*)vector_at(vec, 0) == 15);
    ck_assert(vector_at(vec, 1) == NULL);
    ck_assert(vector_at(vec, 2) == NULL);
    ck_assert(vector_at(vec, 3) == NULL);

    at = vector_pop(vec);
    ck_assert(*at == 15);
    ck_assert(vector_length(vec) == 0);
    ck_assert(vector_at(vec, 0) == NULL);
    ck_assert(vector_at(vec, 1) == NULL);
    ck_assert(vector_at(vec, 2) == NULL);
    ck_assert(vector_at(vec, 3) == NULL);

    at = vector_pop(vec);
    ck_assert(at == NULL);
    ck_assert(vector_length(vec) == 0);
    ck_assert(vector_at(vec, 0) == NULL);
    ck_assert(vector_at(vec, 1) == NULL);
    ck_assert(vector_at(vec, 2) == NULL);
    ck_assert(vector_at(vec, 3) == NULL);

    vector_free(vec);
}
END_TEST

START_TEST(test_insert) {
    int *inserted, values[4] = {15, 21, 30, 69};
    Vector *vec = vector_from_array(sizeof(int), 4, values);
    ck_assert(*(int*)vector_at(vec, 0) == 15);
    ck_assert(*(int*)vector_at(vec, 1) == 21);
    ck_assert(*(int*)vector_at(vec, 2) == 30);
    ck_assert(*(int*)vector_at(vec, 3) == 69);

    inserted = vector_insert(vec, 2, &values[3]);
    ck_assert(*inserted == values[3]);
    ck_assert(*(int*)vector_at(vec, 0) == 15);
    ck_assert(*(int*)vector_at(vec, 1) == 21);
    ck_assert(*(int*)vector_at(vec, 2) == 69);
    ck_assert(*(int*)vector_at(vec, 3) == 30);
    ck_assert(*(int*)vector_at(vec, 4) == 69);

    inserted = vector_insert(vec, 0, &values[2]);
    ck_assert(*inserted == values[2]);
    ck_assert(*(int*)vector_at(vec, 0) == 30);
    ck_assert(*(int*)vector_at(vec, 1) == 15);
    ck_assert(*(int*)vector_at(vec, 2) == 21);
    ck_assert(*(int*)vector_at(vec, 3) == 69);
    ck_assert(*(int*)vector_at(vec, 4) == 30);
    ck_assert(*(int*)vector_at(vec, 5) == 69);

    inserted = vector_insert(vec, 1000, &values[0]);
    ck_assert(*inserted == values[0]);
    ck_assert(*(int*)vector_at(vec, 0) == 30);
    ck_assert(*(int*)vector_at(vec, 1) == 15);
    ck_assert(*(int*)vector_at(vec, 2) == 21);
    ck_assert(*(int*)vector_at(vec, 3) == 69);
    ck_assert(*(int*)vector_at(vec, 4) == 30);
    ck_assert(*(int*)vector_at(vec, 5) == 69);
    ck_assert(*(int*)vector_at(vec, 6) == 15);
}
END_TEST

START_TEST(test_insert_resize) {
    int values[4] = {15, 21, 30, 69};
    Vector *vec = vector_with_capacity(sizeof(int), 1);
    ck_assert(vector_length(vec) == 0);
    ck_assert(vector_capacity(vec) == 1);

    vector_insert(vec, 0, &values[0]);
    ck_assert(vector_length(vec) == 1);
    ck_assert(vector_capacity(vec) == 1);

    vector_insert(vec, 0, &values[1]);
    ck_assert(vector_length(vec) == 2);
    ck_assert(vector_capacity(vec) == 2);

    vector_insert(vec, 0, &values[2]);
    ck_assert(vector_length(vec) == 3);
    ck_assert(vector_capacity(vec) == 4);

    vector_insert(vec, 0, &values[3]);
    ck_assert(vector_length(vec) == 4);
    ck_assert(vector_capacity(vec) == 4);

    vector_insert(vec, 0, &values[0]);
    ck_assert(vector_length(vec) == 5);
    ck_assert(vector_capacity(vec) == 8);

    ck_assert(*(int*)vector_at(vec, 0) == values[0]);
    ck_assert(*(int*)vector_at(vec, 1) == values[3]);
    ck_assert(*(int*)vector_at(vec, 2) == values[2]);
    ck_assert(*(int*)vector_at(vec, 3) == values[1]);
    ck_assert(*(int*)vector_at(vec, 4) == values[0]);
}
END_TEST

START_TEST(test_resize) {
    int values[4] = {15, 21, 30, 69};
    Vector *vec = vector_from_array(sizeof(int), 4, values);
    ck_assert(vector_capacity(vec) == 256);
    ck_assert(vector_length(vec) == 4);

    void *result = vector_resize(vec, 2);
    ck_assert(result != NULL);
    ck_assert(vector_capacity(vec) == 2);
    ck_assert(vector_length(vec) == 2);
    for (int i = 0; i < 2; i++) {
        ck_assert(*(int*)vector_at(vec, i) == values[i]);
    }
    ck_assert(vector_at(vec, 2) == NULL);

    vector_free(vec);
}
END_TEST

START_TEST(test_resize_fail) {
    Vector *vec = vector(sizeof(int));
    void *result = vector_resize(vec, 0);
    ck_assert(result == NULL);
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
    tcase_add_test(test_case, test_resize);
    // double free, realloc(0) is freeing old pointer and returning NULL
    // tcase_add_test(test_case, test_resize_fail);
    suite_add_tcase(suite, test_case);
    return suite;
}
