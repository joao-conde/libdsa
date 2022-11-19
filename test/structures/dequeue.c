#include <check.h>
#include <stdint.h>

#include "../../include/dequeue.h"

START_TEST(test_dequeue_init) {
    dequeue *dq = dequeue_init(sizeof(int));
    ck_assert(dequeue_is_empty(dq));
    dequeue_free(dq);
}
END_TEST

START_TEST(test_dequeue_init_fail) {
    dequeue *dq = dequeue_init(SIZE_MAX);
    ck_assert(dq == NULL);
}
END_TEST

START_TEST(test_dequeue_free) {
    dequeue_free(NULL);

    dequeue *dq = dequeue_init(sizeof(int));
    dequeue_free(dq);
}
END_TEST

START_TEST(test_dequeue_length) {
    float value = 3.5;
    dequeue *dq = dequeue_init(sizeof(float));
    ck_assert(dequeue_length(dq) == 0);

    dequeue_push_back(dq, &value);
    dequeue_push_back(dq, &value);
    dequeue_push_back(dq, &value);
    ck_assert(dequeue_length(dq) == 3);

    dequeue_free(dq);
}
END_TEST

START_TEST(test_dequeue_is_empty) {
    dequeue *dq = dequeue_init(sizeof(int));
    ck_assert(dequeue_is_empty(dq));

    int value = -10;
    dequeue_push_back(dq, &value);
    ck_assert(!dequeue_is_empty(dq));

    dequeue_pop_back(dq);
    ck_assert(dequeue_is_empty(dq));

    dequeue_free(dq);
}
END_TEST

START_TEST(test_dequeue_front) {
    int values[4] = { -1, 10, 24, 59 };
    dequeue *dq = dequeue_init(sizeof(int));

    ck_assert(dequeue_front(dq) == NULL);

    dequeue_push_back(dq, &values[0]);
    ck_assert(*(int*) dequeue_front(dq) == -1);

    dequeue_push_back(dq, &values[1]);
    ck_assert(*(int*) dequeue_front(dq) == -1);

    dequeue_push_front(dq, &values[2]);
    ck_assert(*(int*) dequeue_front(dq) == 24);

    dequeue_push_front(dq, &values[3]);
    ck_assert(*(int*) dequeue_front(dq) == 59);

    dequeue_pop_back(dq);
    ck_assert(*(int*) dequeue_front(dq) == 59);

    dequeue_pop_front(dq);
    ck_assert(*(int*) dequeue_front(dq) == 24);

    dequeue_pop_front(dq);
    ck_assert(*(int*) dequeue_front(dq) == -1);

    dequeue_pop_front(dq);
    ck_assert(dequeue_front(dq) == NULL);

    dequeue_free(dq);
}
END_TEST

START_TEST(test_dequeue_back) {
    int values[4] = { -1, 10, 24, 59 };
    dequeue *dq = dequeue_init(sizeof(int));

    ck_assert(dequeue_back(dq) == NULL);

    dequeue_push_front(dq, &values[0]);
    ck_assert(*(int*) dequeue_back(dq) == -1);

    dequeue_push_front(dq, &values[1]);
    ck_assert(*(int*) dequeue_back(dq) == -1);

    dequeue_push_back(dq, &values[2]);
    ck_assert(*(int*) dequeue_back(dq) == 24);

    dequeue_push_back(dq, &values[3]);
    ck_assert(*(int*) dequeue_back(dq) == 59);

    dequeue_pop_front(dq);
    ck_assert(*(int*) dequeue_back(dq) == 59);

    dequeue_pop_back(dq);
    ck_assert(*(int*) dequeue_back(dq) == 24);

    dequeue_pop_back(dq);
    ck_assert(*(int*) dequeue_back(dq) == -1);

    dequeue_pop_back(dq);
    ck_assert(dequeue_back(dq) == NULL);

    dequeue_free(dq);
}
END_TEST

START_TEST(test_dequeue_push_back) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    dequeue *dq = dequeue_init(sizeof(int));

    result = dequeue_push_back(dq, &values[0]);
    ck_assert(*result == 51);

    result = dequeue_push_back(dq, &values[1]);
    ck_assert(*result == 12);

    result = dequeue_push_back(dq, &values[2]);
    ck_assert(*result == -123);

    result = dequeue_push_back(dq, &values[3]);
    ck_assert(*result == 1000);

    result = dequeue_push_back(dq, &values[4]);
    ck_assert(*result == -1);

    ck_assert(dequeue_length(dq) == 5);

    dequeue_free(dq);
}
END_TEST

START_TEST(test_dequeue_push_front) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    dequeue *dq = dequeue_init(sizeof(int));

    result = dequeue_push_front(dq, &values[0]);
    ck_assert(*result == 51);

    result = dequeue_push_front(dq, &values[1]);
    ck_assert(*result == 12);

    result = dequeue_push_front(dq, &values[2]);
    ck_assert(*result == -123);

    result = dequeue_push_front(dq, &values[3]);
    ck_assert(*result == 1000);

    result = dequeue_push_front(dq, &values[4]);
    ck_assert(*result == -1);

    ck_assert(dequeue_length(dq) == 5);

    dequeue_free(dq);
}
END_TEST

START_TEST(test_dequeue_pop_back) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    dequeue *dq = dequeue_init(sizeof(int));
    dequeue_push_back(dq, &values[0]);
    dequeue_push_back(dq, &values[1]);
    dequeue_push_back(dq, &values[2]);
    dequeue_push_back(dq, &values[3]);
    dequeue_push_back(dq, &values[4]);

    ck_assert(dequeue_length(dq) == 5);

    result = dequeue_pop_back(dq);
    ck_assert(dequeue_length(dq) == 4);
    ck_assert(*result == -1);

    result = dequeue_pop_back(dq);
    ck_assert(dequeue_length(dq) == 3);
    ck_assert(*result == 1000);

    result = dequeue_pop_back(dq);
    ck_assert(dequeue_length(dq) == 2);
    ck_assert(*result == -123);

    result = dequeue_pop_back(dq);
    ck_assert(dequeue_length(dq) == 1);
    ck_assert(*result == 12);

    result = dequeue_pop_back(dq);
    ck_assert(dequeue_length(dq) == 0);
    ck_assert(*result == 51);

    result = dequeue_pop_back(dq);
    ck_assert(dequeue_length(dq) == 0);
    ck_assert(result == NULL);

    dequeue_free(dq);
}
END_TEST

START_TEST(test_dequeue_pop_front) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    dequeue *dq = dequeue_init(sizeof(int));
    dequeue_push_front(dq, &values[0]);
    dequeue_push_front(dq, &values[1]);
    dequeue_push_front(dq, &values[2]);
    dequeue_push_front(dq, &values[3]);
    dequeue_push_front(dq, &values[4]);

    ck_assert(dequeue_length(dq) == 5);

    result = dequeue_pop_front(dq);
    ck_assert(dequeue_length(dq) == 4);
    ck_assert(*result == -1);

    result = dequeue_pop_front(dq);
    ck_assert(dequeue_length(dq) == 3);
    ck_assert(*result == 1000);

    result = dequeue_pop_front(dq);
    ck_assert(dequeue_length(dq) == 2);
    ck_assert(*result == -123);

    result = dequeue_pop_front(dq);
    ck_assert(dequeue_length(dq) == 1);
    ck_assert(*result == 12);

    result = dequeue_pop_front(dq);
    ck_assert(dequeue_length(dq) == 0);
    ck_assert(*result == 51);

    result = dequeue_pop_front(dq);
    ck_assert(dequeue_length(dq) == 0);
    ck_assert(result == NULL);

    dequeue_free(dq);
}
END_TEST

Suite* suite_dequeue() {
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
