#include <check.h>
#include <stdint.h>

#include "../../include/queue.h"

START_TEST(test_queue_init) {
    queue *q = queue_init(sizeof(int));
    ck_assert(queue_is_empty(q));
    queue_free(q);
}
END_TEST

START_TEST(test_queue_init_fail) {
    queue *q = queue_init(SIZE_MAX);
    ck_assert(q == NULL);

    q = queue_init(SIZE_MAX / 1000);
    ck_assert(q == NULL);
}
END_TEST

START_TEST(test_queue_free) {
    queue_free(NULL);

    queue *q = queue_init(sizeof(int));
    queue_free(q);
}
END_TEST

START_TEST(test_queue_length) {
    float value = 3.5;
    queue *q = queue_init(sizeof(float));
    ck_assert(queue_length(q) == 0);

    queue_push(q, &value);
    queue_push(q, &value);
    queue_push(q, &value);
    ck_assert(queue_length(q) == 3);

    queue_free(q);
}
END_TEST

START_TEST(test_queue_is_empty) {
    queue *q = queue_init(sizeof(int));
    ck_assert(queue_is_empty(q));

    int value = -10;
    queue_push(q, &value);
    ck_assert(!queue_is_empty(q));

    queue_pop(q);
    ck_assert(queue_is_empty(q));

    queue_free(q);
}
END_TEST

START_TEST(test_queue_clear) {
    float value = 3.5;
    queue *q = queue_init(sizeof(float));
    queue_push(q, &value);
    queue_push(q, &value);
    queue_push(q, &value);
    ck_assert(queue_length(q) == 3);

    queue_clear(q);
    ck_assert(queue_length(q) == 0);

    queue_free(q);
}
END_TEST

START_TEST(test_queue_at) {
    int values[5] = {51, 12, -123, 1000, -1};
    queue *q = queue_init(sizeof(int));
    ck_assert(queue_at(q, 0) == NULL);

    queue_push(q, &values[0]);
    queue_push(q, &values[1]);
    queue_push(q, &values[2]);
    queue_push(q, &values[3]);
    queue_push(q, &values[4]);
    ck_assert(*(int*)queue_at(q, 0) == 51);
    ck_assert(*(int*)queue_at(q, 1) == 12);
    ck_assert(*(int*)queue_at(q, 2) == -123);
    ck_assert(*(int*)queue_at(q, 3) == 1000);
    ck_assert(*(int*)queue_at(q, 4) == -1);
    ck_assert(queue_at(q, 5) == NULL);

    queue_free(q);
}
END_TEST

START_TEST(test_queue_front) {
    int values[4] = {-1, 10, 24, 59};
    queue *q = queue_init(sizeof(int));

    ck_assert(queue_front(q) == NULL);

    queue_push(q, &values[0]);
    ck_assert(*(int*) queue_front(q) == -1);

    queue_push(q, &values[1]);
    ck_assert(*(int*) queue_front(q) == -1);

    queue_push(q, &values[2]);
    ck_assert(*(int*) queue_front(q) == -1);

    queue_push(q, &values[3]);
    ck_assert(*(int*) queue_front(q) == -1);

    queue_pop(q);
    ck_assert(*(int*) queue_front(q) == 10);

    queue_pop(q);
    ck_assert(*(int*) queue_front(q) == 24);

    queue_pop(q);
    ck_assert(*(int*) queue_front(q) == 59);

    queue_pop(q);
    ck_assert(queue_front(q) == NULL);

    queue_free(q);
}
END_TEST

START_TEST(test_queue_back) {
    int values[4] = {-1, 10, 24, 59};
    queue *q = queue_init(sizeof(int));

    ck_assert(queue_back(q) == NULL);

    queue_push(q, &values[0]);
    ck_assert(*(int*) queue_back(q) == -1);

    queue_push(q, &values[1]);
    ck_assert(*(int*) queue_back(q) == 10);

    queue_push(q, &values[2]);
    ck_assert(*(int*) queue_back(q) == 24);

    queue_push(q, &values[3]);
    ck_assert(*(int*) queue_back(q) == 59);

    queue_pop(q);
    ck_assert(*(int*) queue_back(q) == 59);

    queue_pop(q);
    ck_assert(*(int*) queue_back(q) == 59);

    queue_pop(q);
    ck_assert(*(int*) queue_back(q) == 59);

    queue_pop(q);
    ck_assert(queue_back(q) == NULL);

    queue_free(q);
}
END_TEST

START_TEST(test_queue_pointers) {
    queue *q = queue_init(sizeof(int));
    ck_assert(queue_front(q) == queue_back(q));

    int value = 3;
    queue_push(q, &value);
    ck_assert(queue_front(q) == queue_back(q));

    queue_push(q, &value);
    ck_assert(queue_front(q) != queue_back(q));

    queue_pop(q);
    ck_assert(queue_front(q) == queue_back(q));

    queue_free(q);
}
END_TEST

START_TEST(test_queue_push) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    queue *q = queue_init(sizeof(int));

    result = queue_push(q, &values[0]);
    ck_assert(*result == 51);

    result = queue_push(q, &values[1]);
    ck_assert(*result == 12);

    result = queue_push(q, &values[2]);
    ck_assert(*result == -123);

    result = queue_push(q, &values[3]);
    ck_assert(*result == 1000);

    result = queue_push(q, &values[4]);
    ck_assert(*result == -1);

    ck_assert(queue_length(q) == 5);

    queue_free(q);
}
END_TEST

START_TEST(test_queue_pop) {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    queue *q = queue_init(sizeof(int));
    queue_push(q, &values[0]);
    queue_push(q, &values[1]);
    queue_push(q, &values[2]);
    queue_push(q, &values[3]);
    queue_push(q, &values[4]);

    ck_assert(queue_length(q) == 5);

    result = queue_pop(q);
    ck_assert(queue_length(q) == 4);
    ck_assert(*result == 51);

    result = queue_pop(q);
    ck_assert(queue_length(q) == 3);
    ck_assert(*result == 12);

    result = queue_pop(q);
    ck_assert(queue_length(q) == 2);
    ck_assert(*result == -123);

    result = queue_pop(q);
    ck_assert(queue_length(q) == 1);
    ck_assert(*result == 1000);

    result = queue_pop(q);
    ck_assert(queue_length(q) == 0);
    ck_assert(*result == -1);

    result = queue_pop(q);
    ck_assert(queue_length(q) == 0);
    ck_assert(result == NULL);

    queue_free(q);
}
END_TEST

START_TEST(test_queue_stress) {
    int nelements = 100000;
    bool is_empty;
    size_t length;
    int *at, *pushed, *popped, *front, *back;

    queue *q = queue_init(sizeof(int));

    for (int i = 0; i < nelements; i++) {
        pushed = queue_push(q, &i);
        length = queue_length(q);
        is_empty = queue_is_empty(q);
        at = queue_at(q, i);
        front = queue_front(q);
        back = queue_back(q);
        ck_assert(*pushed == i);
        ck_assert(length == i + 1);
        ck_assert(!is_empty);
        ck_assert(*at == i);
        ck_assert(*front == 0);
        ck_assert(*back == i);
    }

    for (int i = 0; i < nelements / 2; i++) {
        at = queue_at(q, 0);
        front = queue_front(q);
        back = queue_back(q);
        popped = queue_pop(q);
        length = queue_length(q);
        is_empty = queue_is_empty(q);
        ck_assert(*popped == i);
        ck_assert(length == nelements - i - 1);
        ck_assert(!is_empty);
        ck_assert(*at == *popped);
        ck_assert(*front == i);
        ck_assert(*back == nelements - 1);
    }

    queue_clear(q);
    length = queue_length(q);
    is_empty = queue_is_empty(q);
    ck_assert(length == 0);
    ck_assert(is_empty);

    queue_free(q);
}
END_TEST

Suite* suite_queue() {
    Suite *suite = suite_create("queue");
    TCase *test_case = tcase_create("");
    tcase_add_test(test_case, test_queue_init);
    tcase_add_test(test_case, test_queue_init_fail);
    tcase_add_test(test_case, test_queue_free);
    tcase_add_test(test_case, test_queue_length);
    tcase_add_test(test_case, test_queue_is_empty);
    tcase_add_test(test_case, test_queue_clear);
    tcase_add_test(test_case, test_queue_at);
    tcase_add_test(test_case, test_queue_front);
    tcase_add_test(test_case, test_queue_back);
    tcase_add_test(test_case, test_queue_pointers);
    tcase_add_test(test_case, test_queue_push);
    tcase_add_test(test_case, test_queue_pop);
    tcase_add_test(test_case, test_queue_stress);
    suite_add_tcase(suite, test_case);
    return suite;
}
