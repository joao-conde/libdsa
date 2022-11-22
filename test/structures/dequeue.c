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

    dq = dequeue_init(SIZE_MAX / 1000);
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
    dequeue_push_front(dq, &value);
    ck_assert(!dequeue_is_empty(dq));

    dequeue_pop_back(dq);
    ck_assert(dequeue_is_empty(dq));

    dequeue_free(dq);
}
END_TEST

START_TEST(test_dequeue_clear) {
    float value = 3.5;
    dequeue *dq = dequeue_init(sizeof(float));
    dequeue_push_back(dq, &value);
    dequeue_push_back(dq, &value);
    dequeue_push_back(dq, &value);
    ck_assert(dequeue_length(dq) == 3);

    dequeue_clear(dq);
    ck_assert(dequeue_length(dq) == 0);

    dequeue_free(dq);
}
END_TEST

START_TEST(test_dequeue_at) {
    int values[5] = {51, 12, -123, 1000, -1};
    dequeue *dq = dequeue_init(sizeof(int));
    ck_assert(dequeue_at(dq, 0) == NULL);

    dequeue_push_back(dq, &values[0]);
    dequeue_push_back(dq, &values[1]);
    dequeue_push_back(dq, &values[2]);
    dequeue_push_back(dq, &values[3]);
    dequeue_push_back(dq, &values[4]);
    ck_assert(*(int*)dequeue_at(dq, 0) == 51);
    ck_assert(*(int*)dequeue_at(dq, 1) == 12);
    ck_assert(*(int*)dequeue_at(dq, 2) == -123);
    ck_assert(*(int*)dequeue_at(dq, 3) == 1000);
    ck_assert(*(int*)dequeue_at(dq, 4) == -1);
    ck_assert(dequeue_at(dq, 5) == NULL);

    dequeue_push_front(dq, &values[4]);
    dequeue_push_back(dq, &values[3]);
    dequeue_push_front(dq, &values[2]);
    dequeue_push_back(dq, &values[1]);
    dequeue_push_front(dq, &values[0]);
    ck_assert(*(int*)dequeue_at(dq, 0) == 51);
    ck_assert(*(int*)dequeue_at(dq, 1) == -123);
    ck_assert(*(int*)dequeue_at(dq, 2) == -1);
    ck_assert(*(int*)dequeue_at(dq, 3) == 51);
    ck_assert(*(int*)dequeue_at(dq, 4) == 12);
    ck_assert(*(int*)dequeue_at(dq, 5) == -123);
    ck_assert(*(int*)dequeue_at(dq, 6) == 1000);
    ck_assert(*(int*)dequeue_at(dq, 7) == -1);
    ck_assert(*(int*)dequeue_at(dq, 8) == 1000);
    ck_assert(*(int*)dequeue_at(dq, 9) == 12);
    ck_assert(dequeue_at(dq, 10) == NULL);

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

START_TEST(test_dequeue_pointers) {
    dequeue *dq = dequeue_init(sizeof(int));
    ck_assert(dequeue_front(dq) == dequeue_back(dq));

    int value = 3;
    dequeue_push_front(dq, &value);
    ck_assert(dequeue_front(dq) == dequeue_back(dq));

    dequeue_push_front(dq, &value);
    ck_assert(dequeue_front(dq) != dequeue_back(dq));

    dequeue_pop_back(dq);
    ck_assert(dequeue_front(dq) == dequeue_back(dq));

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

START_TEST(test_dequeue_stress) {
    int nelements = 100000;
    bool is_empty;
    size_t length;
    int *at, *pushed, *popped, *front, *back;

    dequeue *dq = dequeue_init(sizeof(int));

    for (int i = 0; i < nelements; i++) {
        pushed = dequeue_push_back(dq, &i);
        length = dequeue_length(dq);
        is_empty = dequeue_is_empty(dq);
        at = dequeue_at(dq, i);
        front = dequeue_front(dq);
        back = dequeue_back(dq);
        ck_assert(*pushed == i);
        ck_assert(length == i + 1);
        ck_assert(!is_empty);
        ck_assert(*at == i);
        ck_assert(*front == 0);
        ck_assert(*back == i);
    }

    for (int i = 0; i < nelements / 2; i++) {
        popped = dequeue_pop_back(dq);
        length = dequeue_length(dq);
        is_empty = dequeue_is_empty(dq);
        at = dequeue_at(dq, i);
        front = dequeue_front(dq);
        back = dequeue_back(dq);
        ck_assert(*popped == nelements - i - 1);
        ck_assert(length == nelements - i - 1);
        ck_assert(!is_empty);
        ck_assert(*at == i);
        ck_assert(*front == 0);
        ck_assert(*back == nelements - i - 2);
    }

    dequeue_clear(dq);
    length = dequeue_length(dq);
    is_empty = dequeue_is_empty(dq);
    ck_assert(length == 0);
    ck_assert(is_empty);

    for (int i = 0; i < nelements; i++) {
        pushed = dequeue_push_front(dq, &i);
        length = dequeue_length(dq);
        is_empty = dequeue_is_empty(dq);
        at = dequeue_at(dq, i);
        back = dequeue_back(dq);
        ck_assert(*pushed == i);
        ck_assert(length == i + 1);
        ck_assert(!is_empty);
        ck_assert(*at == 0);
    }

    for (int i = 0; i < nelements - 1; i++) {
        popped = dequeue_pop_front(dq);
        length = dequeue_length(dq);
        is_empty = dequeue_is_empty(dq);
        back = dequeue_back(dq);
        ck_assert(*popped == nelements - i - 1);
        ck_assert(length == nelements - i - 1);
        ck_assert(!is_empty);
    }

    dequeue_clear(dq);
    length = dequeue_length(dq);
    is_empty = dequeue_is_empty(dq);
    ck_assert(length == 0);
    ck_assert(is_empty);

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
    tcase_add_test(test_case, test_dequeue_clear);
    tcase_add_test(test_case, test_dequeue_at);
    tcase_add_test(test_case, test_dequeue_front);
    tcase_add_test(test_case, test_dequeue_back);
    tcase_add_test(test_case, test_dequeue_pointers);
    tcase_add_test(test_case, test_dequeue_push_back);
    tcase_add_test(test_case, test_dequeue_push_front);
    tcase_add_test(test_case, test_dequeue_pop_back);
    tcase_add_test(test_case, test_dequeue_pop_front);
    tcase_add_test(test_case, test_dequeue_stress);
    suite_add_tcase(suite, test_case);
    return suite;
}
