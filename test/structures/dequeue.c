#include <check.h>
#include <stdint.h>

#include "../../include/dequeue.h"

START_TEST(test_dequeue_init) {
    dequeue *d = dequeue_init(sizeof(int));
    ck_assert(dequeue_is_empty(d));
    dequeue_free(d);
}
END_TEST

START_TEST(test_dequeue_init_fail) {
    dequeue *d = dequeue_init(SIZE_MAX);
    ck_assert(d == NULL);
}
END_TEST

START_TEST(test_dequeue_free) {
    dequeue_free(NULL);

    dequeue *d = dequeue_init(sizeof(int));
    dequeue_free(d);
}
END_TEST

START_TEST(test_dequeue_length) {
    float value = 3.5;
    dequeue *d = dequeue_init(sizeof(float));
    ck_assert(dequeue_length(d) == 0);

    dequeue_push_back(d, &value);
    dequeue_push_back(d, &value);
    dequeue_push_back(d, &value);
    ck_assert(dequeue_length(d) == 3);

    dequeue_free(d);
}
END_TEST

START_TEST(test_dequeue_is_empty) {
    dequeue *d = dequeue_init(sizeof(int));
    ck_assert(dequeue_is_empty(d));

    int value = -10;
    dequeue_push_back(d, &value);
    ck_assert(!dequeue_is_empty(d));

    dequeue_pop_back(d);
    ck_assert(dequeue_is_empty(d));

    dequeue_free(d);
}
END_TEST

START_TEST(test_dequeue_front) {
    int values[4] = { -1, 10, 24, 59 };
    dequeue *d = dequeue_init(sizeof(int));

    ck_assert(dequeue_front(d) == NULL);

    dequeue_push_back(d, &values[0]);
    ck_assert(*(int*) dequeue_front(d) == -1);

    dequeue_push_back(d, &values[1]);
    ck_assert(*(int*) dequeue_front(d) == -1);

    dequeue_push_front(d, &values[2]);
    ck_assert(*(int*) dequeue_front(d) == 24);

    dequeue_push_front(d, &values[3]);
    ck_assert(*(int*) dequeue_front(d) == 59);

    dequeue_pop_back(d);
    ck_assert(*(int*) dequeue_front(d) == 59);

    dequeue_pop_front(d);
    ck_assert(*(int*) dequeue_front(d) == 24);

    dequeue_pop_front(d);
    ck_assert(*(int*) dequeue_front(d) == -1);

    dequeue_pop_front(d);
    ck_assert(dequeue_front(d) == NULL);

    dequeue_free(d);
}
END_TEST

START_TEST(test_dequeue_back) {
    int values[4] = { -1, 10, 24, 59 };
    dequeue *d = dequeue_init(sizeof(int));

    ck_assert(dequeue_back(d) == NULL);

    dequeue_push_front(d, &values[0]);
    ck_assert(*(int*) dequeue_back(d) == -1);

    dequeue_push_front(d, &values[1]);
    ck_assert(*(int*) dequeue_back(d) == -1);

    dequeue_push_back(d, &values[2]);
    ck_assert(*(int*) dequeue_back(d) == 24);

    dequeue_push_back(d, &values[3]);
    ck_assert(*(int*) dequeue_back(d) == 59);

    dequeue_pop_front(d);
    ck_assert(*(int*) dequeue_back(d) == 59);

    dequeue_pop_back(d);
    ck_assert(*(int*) dequeue_back(d) == 24);

    dequeue_pop_back(d);
    ck_assert(*(int*) dequeue_back(d) == -1);

    dequeue_pop_back(d);
    ck_assert(dequeue_back(d) == NULL);

    dequeue_free(d);
}
END_TEST

START_TEST(test_dequeue_push_back) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    dequeue *d = dequeue_init(sizeof(int));

    result = dequeue_push_back(d, &values[0]);
    ck_assert(*result == 51);

    result = dequeue_push_back(d, &values[1]);
    ck_assert(*result == 12);

    result = dequeue_push_back(d, &values[2]);
    ck_assert(*result == -123);

    result = dequeue_push_back(d, &values[3]);
    ck_assert(*result == 1000);

    result = dequeue_push_back(d, &values[4]);
    ck_assert(*result == -1);

    ck_assert(dequeue_length(d) == 5);

    dequeue_free(d);
}
END_TEST

START_TEST(test_dequeue_push_front) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    dequeue *d = dequeue_init(sizeof(int));

    result = dequeue_push_front(d, &values[0]);
    ck_assert(*result == 51);

    result = dequeue_push_front(d, &values[1]);
    ck_assert(*result == 12);

    result = dequeue_push_front(d, &values[2]);
    ck_assert(*result == -123);

    result = dequeue_push_front(d, &values[3]);
    ck_assert(*result == 1000);

    result = dequeue_push_front(d, &values[4]);
    ck_assert(*result == -1);

    ck_assert(dequeue_length(d) == 5);

    dequeue_free(d);
}
END_TEST

START_TEST(test_dequeue_pop_back) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    dequeue *s = dequeue_init(sizeof(int));
    dequeue_push_back(s, &values[0]);
    dequeue_push_back(s, &values[1]);
    dequeue_push_back(s, &values[2]);
    dequeue_push_back(s, &values[3]);
    dequeue_push_back(s, &values[4]);

    ck_assert(dequeue_length(s) == 5);

    result = dequeue_pop_back(s);
    ck_assert(dequeue_length(s) == 4);
    ck_assert(*result == -1);

    result = dequeue_pop_back(s);
    ck_assert(dequeue_length(s) == 3);
    ck_assert(*result == 1000);

    result = dequeue_pop_back(s);
    ck_assert(dequeue_length(s) == 2);
    ck_assert(*result == -123);

    result = dequeue_pop_back(s);
    ck_assert(dequeue_length(s) == 1);
    ck_assert(*result == 12);

    result = dequeue_pop_back(s);
    ck_assert(dequeue_length(s) == 0);
    ck_assert(*result == 51);

    result = dequeue_pop_back(s);
    ck_assert(dequeue_length(s) == 0);
    ck_assert(result == NULL);

    dequeue_free(s);
}
END_TEST

START_TEST(test_dequeue_pop_front) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    dequeue *s = dequeue_init(sizeof(int));
    dequeue_push_front(s, &values[0]);
    dequeue_push_front(s, &values[1]);
    dequeue_push_front(s, &values[2]);
    dequeue_push_front(s, &values[3]);
    dequeue_push_front(s, &values[4]);

    ck_assert(dequeue_length(s) == 5);

    result = dequeue_pop_front(s);
    ck_assert(dequeue_length(s) == 4);
    ck_assert(*result == -1);

    result = dequeue_pop_front(s);
    ck_assert(dequeue_length(s) == 3);
    ck_assert(*result == 1000);

    result = dequeue_pop_front(s);
    ck_assert(dequeue_length(s) == 2);
    ck_assert(*result == -123);

    result = dequeue_pop_front(s);
    ck_assert(dequeue_length(s) == 1);
    ck_assert(*result == 12);

    result = dequeue_pop_front(s);
    ck_assert(dequeue_length(s) == 0);
    ck_assert(*result == 51);

    result = dequeue_pop_front(s);
    ck_assert(dequeue_length(s) == 0);
    ck_assert(result == NULL);

    dequeue_free(s);
}
END_TEST

Suite* suite_stack() {
    Suite *suite = suite_create("dequeue");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_dequeue_init);
    tcase_add_test(test_case, test_dequeue_init_fail);
    tcase_add_test(test_case, test_dequeue_free);
    tcase_add_test(test_case, test_dequeue_length);
    tcase_add_test(test_case, test_dequeue_is_empty);
    tcase_add_test(test_case, test_dequeue_front);
    tcase_add_test(test_case, test_dequeue_back);
    tcase_add_test(test_case, test_dequeue_push_back);
    tcase_add_test(test_case, test_dequeue_push_front);
    tcase_add_test(test_case, test_dequeue_pop_back);
    tcase_add_test(test_case, test_dequeue_pop_front);
    suite_add_tcase(suite, test_case);
    return suite;
}
