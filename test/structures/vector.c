#include <check.h>
#include <limits.h>

#include "../../include/vector.h"

START_TEST(test_vector) {
    // should fail if too much memory is requested
    Vector *vec = vector(UINT_MAX);
    ck_assert(vec == NULL);

    // should have default length and capacity
    vec = vector(sizeof(int));
    ck_assert(vector_length(vec) == 0);
    ck_assert(vector_capacity(vec) == 256);

    vector_free(vec);
}
END_TEST

START_TEST(test_vector_with_capacity) {
    // should fail if too much memory is requested
    Vector *vec = vector_with_capacity(UINT_MAX, 100);
    ck_assert(vec == NULL);

    // should have default length and specified capacity
    vec = vector_with_capacity(sizeof(int), 10);
    ck_assert(vector_length(vec) == 0);
    ck_assert(vector_capacity(vec) == 10);

    vector_free(vec);
}
END_TEST

START_TEST(test_vector_from_array) {
    // should fail if too much memory is requested
    Vector *vec = vector_from_array(UINT_MAX, 1, NULL);
    ck_assert(vec == NULL);

    // should be created from array elements
    int array[4] = {15, 21, 30, 69};
    vec = vector_from_array(sizeof(int), 4, array);
    ck_assert(vector_length(vec) == 4);
    ck_assert(vector_capacity(vec) == 256);
    for (int i = 0; i < 4; i++) {
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

    int value = 3;
    vector_push(vec, &value);
    vector_push(vec, &value);
    vector_push(vec, &value);
    ck_assert(vector_length(vec) == 3);

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
    int *result = vector_at(vec, 0);
    ck_assert(result == NULL);

    vector_free(vec);

    int array[4] = {15, 21, 30, 69};
    vec = vector_from_array(sizeof(int), 4, array);
    for (int i = 0; i < 4; i++) {
        int *at = vector_at(vec, i);
        ck_assert(*at == array[i]);
    }

    vector_free(vec);
}
END_TEST

START_TEST(test_vector_push) {
    Vector *vec = vector(sizeof(int));

    int *result = vector_at(vec, 0);
    ck_assert(result == NULL);

    int values[5] = {51, 12, -123, 1000, -1};
    for (int i = 0; i < 5; i++) {
        vector_push(vec, &values[i]);
    }

    ck_assert(vector_length(vec) == 5);
    for (int i = 0; i < 5; i++) {
        int *at = vector_at(vec, i);
        ck_assert(*at == values[i]);
    }

    result = vector_at(vec, 5);
    ck_assert(result == NULL);

    vector_free(vec);
}
END_TEST

START_TEST(test_vector_resize) {
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

    vec = vector(0);
    result = vector_resize(vec, 10);
    ck_assert(result == NULL);

    // TODO(joao-conde): debug why vec->data was already free'd
    // problem lies in realloc ? it should not free it
    // when it fails
    // vector_free(vec);
    free(vec);
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
    tcase_add_test(test_case, test_vector_push);
    tcase_add_test(test_case, test_vector_resize);
    suite_add_tcase(suite, test_case);
    return suite;
}
