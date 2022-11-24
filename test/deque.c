#include <check.h>
#include <stdint.h>

#include "../include/deque.h"

START_TEST(test_deque_init) {
    deque *dq = deque_init(sizeof(int));
    ck_assert(deque_is_empty(dq));
    deque_free(dq);
}
END_TEST

START_TEST(test_deque_init_fail) {
    deque *dq = deque_init(SIZE_MAX);
    ck_assert(dq == NULL);

    dq = deque_init(SIZE_MAX / 1000);
    ck_assert(dq == NULL);
}
END_TEST

START_TEST(test_deque_free) {
    deque_free(NULL);

    deque *dq = deque_init(sizeof(int));
    deque_free(dq);
}
END_TEST

START_TEST(test_deque_length) {
    float value = 3.5;
    deque *dq = deque_init(sizeof(float));
    ck_assert(deque_length(dq) == 0);

    deque_push_back(dq, &value);
    deque_push_back(dq, &value);
    deque_push_back(dq, &value);
    ck_assert(deque_length(dq) == 3);

    deque_free(dq);
}
END_TEST

START_TEST(test_deque_is_empty) {
    deque *dq = deque_init(sizeof(int));
    ck_assert(deque_is_empty(dq));

    int value = -10;
    deque_push_front(dq, &value);
    ck_assert(!deque_is_empty(dq));

    deque_pop_back(dq);
    ck_assert(deque_is_empty(dq));

    deque_free(dq);
}
END_TEST

START_TEST(test_deque_clear) {
    float value = 3.5;
    deque *dq = deque_init(sizeof(float));
    deque_push_back(dq, &value);
    deque_push_back(dq, &value);
    deque_push_back(dq, &value);
    ck_assert(deque_length(dq) == 3);

    deque_clear(dq);
    ck_assert(deque_length(dq) == 0);

    deque_free(dq);
}
END_TEST

START_TEST(test_deque_at) {
    int values[5] = {51, 12, -123, 1000, -1};
    deque *dq = deque_init(sizeof(int));
    ck_assert(deque_at(dq, 0) == NULL);

    deque_push_back(dq, &values[0]);
    deque_push_back(dq, &values[1]);
    deque_push_back(dq, &values[2]);
    deque_push_back(dq, &values[3]);
    deque_push_back(dq, &values[4]);
    ck_assert(*(int*)deque_at(dq, 0) == 51);
    ck_assert(*(int*)deque_at(dq, 1) == 12);
    ck_assert(*(int*)deque_at(dq, 2) == -123);
    ck_assert(*(int*)deque_at(dq, 3) == 1000);
    ck_assert(*(int*)deque_at(dq, 4) == -1);
    ck_assert(deque_at(dq, 5) == NULL);

    deque_push_front(dq, &values[4]);
    deque_push_back(dq, &values[3]);
    deque_push_front(dq, &values[2]);
    deque_push_back(dq, &values[1]);
    deque_push_front(dq, &values[0]);
    ck_assert(*(int*)deque_at(dq, 0) == 51);
    ck_assert(*(int*)deque_at(dq, 1) == -123);
    ck_assert(*(int*)deque_at(dq, 2) == -1);
    ck_assert(*(int*)deque_at(dq, 3) == 51);
    ck_assert(*(int*)deque_at(dq, 4) == 12);
    ck_assert(*(int*)deque_at(dq, 5) == -123);
    ck_assert(*(int*)deque_at(dq, 6) == 1000);
    ck_assert(*(int*)deque_at(dq, 7) == -1);
    ck_assert(*(int*)deque_at(dq, 8) == 1000);
    ck_assert(*(int*)deque_at(dq, 9) == 12);
    ck_assert(deque_at(dq, 10) == NULL);

    deque_free(dq);
}
END_TEST

START_TEST(test_deque_front) {
    int values[4] = {-1, 10, 24, 59};
    deque *dq = deque_init(sizeof(int));

    ck_assert(deque_front(dq) == NULL);

    deque_push_back(dq, &values[0]);
    ck_assert(*(int*) deque_front(dq) == -1);

    deque_push_back(dq, &values[1]);
    ck_assert(*(int*) deque_front(dq) == -1);

    deque_push_front(dq, &values[2]);
    ck_assert(*(int*) deque_front(dq) == 24);

    deque_push_front(dq, &values[3]);
    ck_assert(*(int*) deque_front(dq) == 59);

    deque_pop_back(dq);
    ck_assert(*(int*) deque_front(dq) == 59);

    deque_pop_front(dq);
    ck_assert(*(int*) deque_front(dq) == 24);

    deque_pop_front(dq);
    ck_assert(*(int*) deque_front(dq) == -1);

    deque_pop_front(dq);
    ck_assert(deque_front(dq) == NULL);

    deque_free(dq);
}
END_TEST

START_TEST(test_deque_back) {
    int values[4] = {-1, 10, 24, 59};
    deque *dq = deque_init(sizeof(int));

    ck_assert(deque_back(dq) == NULL);

    deque_push_front(dq, &values[0]);
    ck_assert(*(int*) deque_back(dq) == -1);

    deque_push_front(dq, &values[1]);
    ck_assert(*(int*) deque_back(dq) == -1);

    deque_push_back(dq, &values[2]);
    ck_assert(*(int*) deque_back(dq) == 24);

    deque_push_back(dq, &values[3]);
    ck_assert(*(int*) deque_back(dq) == 59);

    deque_pop_front(dq);
    ck_assert(*(int*) deque_back(dq) == 59);

    deque_pop_back(dq);
    ck_assert(*(int*) deque_back(dq) == 24);

    deque_pop_back(dq);
    ck_assert(*(int*) deque_back(dq) == -1);

    deque_pop_back(dq);
    ck_assert(deque_back(dq) == NULL);

    deque_free(dq);
}
END_TEST

START_TEST(test_deque_pointers) {
    deque *dq = deque_init(sizeof(int));
    ck_assert(deque_front(dq) == deque_back(dq));

    int value = 3;
    deque_push_front(dq, &value);
    ck_assert(deque_front(dq) == deque_back(dq));

    deque_push_front(dq, &value);
    ck_assert(deque_front(dq) != deque_back(dq));

    deque_pop_back(dq);
    ck_assert(deque_front(dq) == deque_back(dq));

    deque_free(dq);
}
END_TEST

START_TEST(test_deque_push_back) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    deque *dq = deque_init(sizeof(int));

    result = deque_push_back(dq, &values[0]);
    ck_assert(*result == 51);

    result = deque_push_back(dq, &values[1]);
    ck_assert(*result == 12);

    result = deque_push_back(dq, &values[2]);
    ck_assert(*result == -123);

    result = deque_push_back(dq, &values[3]);
    ck_assert(*result == 1000);

    result = deque_push_back(dq, &values[4]);
    ck_assert(*result == -1);

    ck_assert(deque_length(dq) == 5);

    deque_free(dq);
}
END_TEST

START_TEST(test_deque_push_front) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    deque *dq = deque_init(sizeof(int));

    result = deque_push_front(dq, &values[0]);
    ck_assert(*result == 51);

    result = deque_push_front(dq, &values[1]);
    ck_assert(*result == 12);

    result = deque_push_front(dq, &values[2]);
    ck_assert(*result == -123);

    result = deque_push_front(dq, &values[3]);
    ck_assert(*result == 1000);

    result = deque_push_front(dq, &values[4]);
    ck_assert(*result == -1);

    ck_assert(deque_length(dq) == 5);

    deque_free(dq);
}
END_TEST

START_TEST(test_deque_pop_back) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    deque *dq = deque_init(sizeof(int));
    deque_push_back(dq, &values[0]);
    deque_push_back(dq, &values[1]);
    deque_push_back(dq, &values[2]);
    deque_push_back(dq, &values[3]);
    deque_push_back(dq, &values[4]);

    ck_assert(deque_length(dq) == 5);

    result = deque_pop_back(dq);
    ck_assert(deque_length(dq) == 4);
    ck_assert(*result == -1);

    result = deque_pop_back(dq);
    ck_assert(deque_length(dq) == 3);
    ck_assert(*result == 1000);

    result = deque_pop_back(dq);
    ck_assert(deque_length(dq) == 2);
    ck_assert(*result == -123);

    result = deque_pop_back(dq);
    ck_assert(deque_length(dq) == 1);
    ck_assert(*result == 12);

    result = deque_pop_back(dq);
    ck_assert(deque_length(dq) == 0);
    ck_assert(*result == 51);

    result = deque_pop_back(dq);
    ck_assert(deque_length(dq) == 0);
    ck_assert(result == NULL);

    deque_free(dq);
}
END_TEST

START_TEST(test_deque_pop_front) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    deque *dq = deque_init(sizeof(int));
    deque_push_front(dq, &values[0]);
    deque_push_front(dq, &values[1]);
    deque_push_front(dq, &values[2]);
    deque_push_front(dq, &values[3]);
    deque_push_front(dq, &values[4]);

    ck_assert(deque_length(dq) == 5);

    result = deque_pop_front(dq);
    ck_assert(deque_length(dq) == 4);
    ck_assert(*result == -1);

    result = deque_pop_front(dq);
    ck_assert(deque_length(dq) == 3);
    ck_assert(*result == 1000);

    result = deque_pop_front(dq);
    ck_assert(deque_length(dq) == 2);
    ck_assert(*result == -123);

    result = deque_pop_front(dq);
    ck_assert(deque_length(dq) == 1);
    ck_assert(*result == 12);

    result = deque_pop_front(dq);
    ck_assert(deque_length(dq) == 0);
    ck_assert(*result == 51);

    result = deque_pop_front(dq);
    ck_assert(deque_length(dq) == 0);
    ck_assert(result == NULL);

    deque_free(dq);
}
END_TEST

START_TEST(test_deque_stress) {
    int nelements = 100000;
    bool is_empty;
    size_t length;
    int *at, *pushed, *popped, *front, *back;

    deque *dq = deque_init(sizeof(int));

    for (int i = 0; i < nelements; i++) {
        pushed = deque_push_back(dq, &i);
        length = deque_length(dq);
        is_empty = deque_is_empty(dq);
        at = deque_at(dq, i);
        front = deque_front(dq);
        back = deque_back(dq);
        ck_assert(*pushed == i);
        ck_assert(length == i + 1);
        ck_assert(!is_empty);
        ck_assert(*at == i);
        ck_assert(*front == 0);
        ck_assert(*back == i);
    }

    for (int i = 0; i < nelements / 2; i++) {
        popped = deque_pop_back(dq);
        length = deque_length(dq);
        is_empty = deque_is_empty(dq);
        at = deque_at(dq, i);
        front = deque_front(dq);
        back = deque_back(dq);
        ck_assert(*popped == nelements - i - 1);
        ck_assert(length == nelements - i - 1);
        ck_assert(!is_empty);
        ck_assert(*at == i);
        ck_assert(*front == 0);
        ck_assert(*back == nelements - i - 2);
    }

    deque_clear(dq);
    length = deque_length(dq);
    is_empty = deque_is_empty(dq);
    ck_assert(length == 0);
    ck_assert(is_empty);

    for (int i = 0; i < nelements; i++) {
        pushed = deque_push_front(dq, &i);
        length = deque_length(dq);
        is_empty = deque_is_empty(dq);
        at = deque_at(dq, i);
        back = deque_back(dq);
        ck_assert(*pushed == i);
        ck_assert(length == i + 1);
        ck_assert(!is_empty);
        ck_assert(*at == 0);
    }

    for (int i = 0; i < nelements - 1; i++) {
        popped = deque_pop_front(dq);
        length = deque_length(dq);
        is_empty = deque_is_empty(dq);
        back = deque_back(dq);
        ck_assert(*popped == nelements - i - 1);
        ck_assert(length == nelements - i - 1);
        ck_assert(!is_empty);
    }

    deque_clear(dq);
    length = deque_length(dq);
    is_empty = deque_is_empty(dq);
    ck_assert(length == 0);
    ck_assert(is_empty);

    deque_free(dq);
}
END_TEST

Suite* suite_deque() {
    Suite *suite = suite_create("deque");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_deque_init);
    tcase_add_test(test_case, test_deque_init_fail);
    tcase_add_test(test_case, test_deque_free);
    tcase_add_test(test_case, test_deque_length);
    tcase_add_test(test_case, test_deque_is_empty);
    tcase_add_test(test_case, test_deque_clear);
    tcase_add_test(test_case, test_deque_at);
    tcase_add_test(test_case, test_deque_front);
    tcase_add_test(test_case, test_deque_back);
    tcase_add_test(test_case, test_deque_pointers);
    tcase_add_test(test_case, test_deque_push_back);
    tcase_add_test(test_case, test_deque_push_front);
    tcase_add_test(test_case, test_deque_pop_back);
    tcase_add_test(test_case, test_deque_pop_front);
    tcase_add_test(test_case, test_deque_stress);
    suite_add_tcase(suite, test_case);
    return suite;
}
