#include <check.h>
#include <limits.h>

#include "../../include/vector.h"

START_TEST(test_vector) {
    vector *v = vec(sizeof(int));
    ck_assert(vec_length(v) == 0);
    ck_assert(vec_capacity(v) == 256);
    vec_free(v);
}
END_TEST

START_TEST(test_vector_fail) {
    vector *v = vec(UINT_MAX);
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
    vector *v = vec_with_capacity(UINT_MAX, 100);
    ck_assert(v == NULL);
}
END_TEST

START_TEST(test_from_array) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(int), 4, values);
    ck_assert(vec_length(v) == 4);
    ck_assert(vec_capacity(v) == 256);
    for (int i = 0; i < 4; i++) {
        int *at = vec_at(v, i);
        ck_assert(*at == values[i]);
    }
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
    vector *v = vec_from_array(UINT_MAX, 1, NULL);
    ck_assert(v == NULL);
}
END_TEST

START_TEST(test_free) {
    vector *v = vec(sizeof(int));
    vec_free(v);
}
END_TEST

START_TEST(test_length) {
    int value = 3;
    vector *v = vec(sizeof(int));
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

    vec_free(v);
}
END_TEST

START_TEST(test_at) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(int), 4, values);
    for (int i = 0; i < 4; i++) {
        int *at = vec_at(v, i);
        ck_assert(*at == values[i]);
    }
    vec_free(v);
}
END_TEST

START_TEST(test_at_fail) {
    vector *v = vec(sizeof(int));
    int *at = vec_at(v, 0);
    ck_assert(at == NULL);
    vec_free(v);
}
END_TEST

START_TEST(test_begin) {
    int values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(int), 4, values);
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
    int *at, values[5] = {51, 12, -123, 1000, -1};
    vector *v = vec(sizeof(int));
    for (int i = 0; i < 5; i++) {
        at = vec_push(v, &values[i]);
        ck_assert(*at == values[i]);
    }

    ck_assert(vec_length(v) == 5);
    for (int i = 0; i < 5; i++) {
        at = vec_at(v, i);
        ck_assert(*at == values[i]);
    }

    at = vec_at(v, 5);
    ck_assert(at == NULL);

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
    ck_assert(*(int*)vec_at(v, 0) == values[0]);

    vec_push(v, &values[1]);
    ck_assert(vec_length(v) == 2);
    ck_assert(vec_capacity(v) == 2);
    ck_assert(*(int*)vec_at(v, 0) == values[0]);
    ck_assert(*(int*)vec_at(v, 1) == values[1]);

    vec_push(v, &values[2]);
    ck_assert(vec_length(v) == 3);
    ck_assert(vec_capacity(v) == 4);
    ck_assert(*(int*)vec_at(v, 0) == values[0]);
    ck_assert(*(int*)vec_at(v, 1) == values[1]);
    ck_assert(*(int*)vec_at(v, 2) == values[2]);

    vec_push(v, &values[3]);
    ck_assert(vec_length(v) == 4);
    ck_assert(vec_capacity(v) == 4);
    ck_assert(*(int*)vec_at(v, 0) == values[0]);
    ck_assert(*(int*)vec_at(v, 1) == values[1]);
    ck_assert(*(int*)vec_at(v, 2) == values[2]);
    ck_assert(*(int*)vec_at(v, 3) == values[3]);

    vec_push(v, &values[4]);
    ck_assert(vec_length(v) == 5);
    ck_assert(vec_capacity(v) == 8);
    ck_assert(*(int*)vec_at(v, 0) == values[0]);
    ck_assert(*(int*)vec_at(v, 1) == values[1]);
    ck_assert(*(int*)vec_at(v, 2) == values[2]);
    ck_assert(*(int*)vec_at(v, 3) == values[3]);
    ck_assert(*(int*)vec_at(v, 4) == values[4]);

    vec_free(v);
}
END_TEST

START_TEST(test_pop) {
    int *at, values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(int), 4, values);
    ck_assert(vec_length(v) == 4);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 30);
    ck_assert(*(int*)vec_at(v, 3) == 69);

    at = vec_pop(v);
    ck_assert(*at == 69);
    ck_assert(vec_length(v) == 3);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 30);
    ck_assert(vec_at(v, 3) == NULL);

    at = vec_pop(v);
    ck_assert(*at == 30);
    ck_assert(vec_length(v) == 2);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(vec_at(v, 2) == NULL);
    ck_assert(vec_at(v, 3) == NULL);

    at = vec_pop(v);
    ck_assert(*at == 21);
    ck_assert(vec_length(v) == 1);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(vec_at(v, 1) == NULL);
    ck_assert(vec_at(v, 2) == NULL);
    ck_assert(vec_at(v, 3) == NULL);

    at = vec_pop(v);
    ck_assert(*at == 15);
    ck_assert(vec_length(v) == 0);
    ck_assert(vec_at(v, 0) == NULL);
    ck_assert(vec_at(v, 1) == NULL);
    ck_assert(vec_at(v, 2) == NULL);
    ck_assert(vec_at(v, 3) == NULL);

    at = vec_pop(v);
    ck_assert(at == NULL);
    ck_assert(vec_length(v) == 0);
    ck_assert(vec_at(v, 0) == NULL);
    ck_assert(vec_at(v, 1) == NULL);
    ck_assert(vec_at(v, 2) == NULL);
    ck_assert(vec_at(v, 3) == NULL);

    vec_free(v);
}
END_TEST

START_TEST(test_insert) {
    int *inserted, values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(int), 4, values);
    ck_assert(vec_length(v) == 4);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 30);
    ck_assert(*(int*)vec_at(v, 3) == 69);

    inserted = vec_insert(v, 2, &values[3]);
    ck_assert(*inserted == values[3]);
    ck_assert(vec_length(v) == 5);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 69);
    ck_assert(*(int*)vec_at(v, 3) == 30);
    ck_assert(*(int*)vec_at(v, 4) == 69);

    inserted = vec_insert(v, 0, &values[2]);
    ck_assert(*inserted == values[2]);
    ck_assert(vec_length(v) == 6);
    ck_assert(*(int*)vec_at(v, 0) == 30);
    ck_assert(*(int*)vec_at(v, 1) == 15);
    ck_assert(*(int*)vec_at(v, 2) == 21);
    ck_assert(*(int*)vec_at(v, 3) == 69);
    ck_assert(*(int*)vec_at(v, 4) == 30);
    ck_assert(*(int*)vec_at(v, 5) == 69);

    inserted = vec_insert(v, 6, &values[0]);
    ck_assert(*inserted == values[0]);
    ck_assert(vec_length(v) == 7);
    ck_assert(*(int*)vec_at(v, 0) == 30);
    ck_assert(*(int*)vec_at(v, 1) == 15);
    ck_assert(*(int*)vec_at(v, 2) == 21);
    ck_assert(*(int*)vec_at(v, 3) == 69);
    ck_assert(*(int*)vec_at(v, 4) == 30);
    ck_assert(*(int*)vec_at(v, 5) == 69);
    ck_assert(*(int*)vec_at(v, 6) == 15);

    inserted = vec_insert(v, 1000, &values[0]);
    ck_assert(inserted == NULL);
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

    ck_assert(*(int*)vec_at(v, 0) == values[0]);
    ck_assert(*(int*)vec_at(v, 1) == values[3]);
    ck_assert(*(int*)vec_at(v, 2) == values[2]);
    ck_assert(*(int*)vec_at(v, 3) == values[1]);
    ck_assert(*(int*)vec_at(v, 4) == values[0]);

    vec_free(v);
}
END_TEST

START_TEST(test_erase) {
    int *new, values[7] = {15, 21, 30, 69, -1, 10, 28};
    vector *v = vec_from_array(sizeof(int), 7, values);
    ck_assert(vec_length(v) == 7);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 30);
    ck_assert(*(int*)vec_at(v, 3) == 69);
    ck_assert(*(int*)vec_at(v, 4) == -1);
    ck_assert(*(int*)vec_at(v, 5) == 10);
    ck_assert(*(int*)vec_at(v, 6) == 28);

    new = vec_erase(v, 3);
    ck_assert(*new == -1);
    ck_assert(vec_length(v) == 6);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 30);
    ck_assert(*(int*)vec_at(v, 3) == -1);
    ck_assert(*(int*)vec_at(v, 4) == 10);
    ck_assert(*(int*)vec_at(v, 5) == 28);
    ck_assert(vec_at(v, 6) == NULL);

    new = vec_erase(v, 4);
    ck_assert(*new == 28);
    ck_assert(vec_length(v) == 5);
    ck_assert(*(int*)vec_at(v, 0) == 15);
    ck_assert(*(int*)vec_at(v, 1) == 21);
    ck_assert(*(int*)vec_at(v, 2) == 30);
    ck_assert(*(int*)vec_at(v, 3) == -1);
    ck_assert(*(int*)vec_at(v, 4) == 28);
    ck_assert(vec_at(v, 5) == NULL);
    ck_assert(vec_at(v, 6) == NULL);

    new = vec_erase(v, 0);
    ck_assert(*new == 21);
    ck_assert(vec_length(v) == 4);
    ck_assert(*(int*)vec_at(v, 0) == 21);
    ck_assert(*(int*)vec_at(v, 1) == 30);
    ck_assert(*(int*)vec_at(v, 2) == -1);
    ck_assert(*(int*)vec_at(v, 3) == 28);
    ck_assert(vec_at(v, 4) == NULL);
    ck_assert(vec_at(v, 5) == NULL);
    ck_assert(vec_at(v, 6) == NULL);

    new = vec_erase(v, 3);
    ck_assert(new != NULL);
    ck_assert(vec_length(v) == 3);
    ck_assert(*(int*)vec_at(v, 0) == 21);
    ck_assert(*(int*)vec_at(v, 1) == 30);
    ck_assert(*(int*)vec_at(v, 2) == -1);
    ck_assert(vec_at(v, 3) == NULL);
    ck_assert(vec_at(v, 4) == NULL);
    ck_assert(vec_at(v, 5) == NULL);
    ck_assert(vec_at(v, 6) == NULL);

    new = vec_erase(v, 1000);
    ck_assert(new == NULL);
    ck_assert(vec_length(v) == 3);
    ck_assert(*(int*)vec_at(v, 0) == 21);
    ck_assert(*(int*)vec_at(v, 1) == 30);
    ck_assert(*(int*)vec_at(v, 2) == -1);
    ck_assert(vec_at(v, 4) == NULL);
    ck_assert(vec_at(v, 4) == NULL);
    ck_assert(vec_at(v, 5) == NULL);
    ck_assert(vec_at(v, 6) == NULL);

    new = vec_erase(v, 0);
    ck_assert(*new == 30);

    new = vec_erase(v, 0);
    ck_assert(*new == -1);

    new = vec_erase(v, 0);
    ck_assert(new != NULL);

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
    int values[4] = {15, 21, 30, 69};
    vector *v = vec_from_array(sizeof(int), 4, values);
    ck_assert(vec_capacity(v) == 256);
    ck_assert(vec_length(v) == 4);

    void *result = vec_resize(v, 2);
    ck_assert(result != NULL);
    ck_assert(vec_capacity(v) == 2);
    ck_assert(vec_length(v) == 2);
    for (int i = 0; i < 2; i++) {
        ck_assert(*(int*)vec_at(v, i) == values[i]);
    }
    ck_assert(vec_at(v, 2) == NULL);

    vec_free(v);
}
END_TEST

START_TEST(test_resize_fail) {
    vector *v = vec(sizeof(int));
    void *result = vec_resize(v, 0);
    ck_assert(result == NULL);
    vec_free(v);
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
    tcase_add_test(test_case, test_erase);
    tcase_add_test(test_case, test_resize);

    // double free, realloc(0) is freeing old pointer and returning NULL
    // tcase_add_test(test_case, test_resize_fail);

    suite_add_tcase(suite, test_case);
    return suite;
}
