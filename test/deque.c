#include <assert.h>
#include <stdint.h>

#include "../include/deque.h"

#define DEQUE_TEST_LOAD 100000

void test_deque_init() {
    deque *dq = deque_init(sizeof(int));
    assert(deque_empty(dq));
    deque_free(dq);
}

void test_deque_init_fail() {
    deque *dq = deque_init(SIZE_MAX);
    assert(dq == NULL);

    dq = deque_init(SIZE_MAX / 10000);
    assert(dq == NULL);
}

void test_deque_free() {
    deque_free(NULL);

    deque *dq = deque_init(sizeof(int));
    deque_free(dq);
}

void test_deque_size() {
    float value = 3.5;
    deque *dq = deque_init(sizeof(float));
    assert(deque_size(dq) == 0);

    deque_push_back(dq, &value);
    deque_push_back(dq, &value);
    deque_push_back(dq, &value);
    assert(deque_size(dq) == 3);

    deque_free(dq);
}

void test_deque_empty() {
    deque *dq = deque_init(sizeof(int));
    assert(deque_empty(dq));

    int value = -10;
    deque_push_front(dq, &value);
    assert(!deque_empty(dq));

    deque_pop_back(dq);
    assert(deque_empty(dq));

    deque_free(dq);
}

void test_deque_clear() {
    float value = 3.5;
    deque *dq = deque_init(sizeof(float));
    deque_push_back(dq, &value);
    deque_push_back(dq, &value);
    deque_push_back(dq, &value);
    assert(deque_size(dq) == 3);

    deque_clear(dq);
    assert(deque_size(dq) == 0);

    deque_free(dq);
}

void test_deque_at() {
    int values[5] = {51, 12, -123, 1000, -1};
    deque *dq = deque_init(sizeof(int));
    assert(deque_at(dq, 0) == NULL);

    deque_push_back(dq, &values[0]);
    deque_push_back(dq, &values[1]);
    deque_push_back(dq, &values[2]);
    deque_push_back(dq, &values[3]);
    deque_push_back(dq, &values[4]);
    assert(*(int*)deque_at(dq, 0) == 51);
    assert(*(int*)deque_at(dq, 1) == 12);
    assert(*(int*)deque_at(dq, 2) == -123);
    assert(*(int*)deque_at(dq, 3) == 1000);
    assert(*(int*)deque_at(dq, 4) == -1);
    assert(deque_at(dq, 5) == NULL);

    deque_push_front(dq, &values[4]);
    deque_push_back(dq, &values[3]);
    deque_push_front(dq, &values[2]);
    deque_push_back(dq, &values[1]);
    deque_push_front(dq, &values[0]);
    assert(*(int*)deque_at(dq, 0) == 51);
    assert(*(int*)deque_at(dq, 1) == -123);
    assert(*(int*)deque_at(dq, 2) == -1);
    assert(*(int*)deque_at(dq, 3) == 51);
    assert(*(int*)deque_at(dq, 4) == 12);
    assert(*(int*)deque_at(dq, 5) == -123);
    assert(*(int*)deque_at(dq, 6) == 1000);
    assert(*(int*)deque_at(dq, 7) == -1);
    assert(*(int*)deque_at(dq, 8) == 1000);
    assert(*(int*)deque_at(dq, 9) == 12);
    assert(deque_at(dq, 10) == NULL);

    deque_free(dq);
}

void test_deque_front() {
    int values[4] = {-1, 10, 24, 59};
    deque *dq = deque_init(sizeof(int));

    assert(deque_front(dq) == NULL);

    deque_push_back(dq, &values[0]);
    assert(*(int*) deque_front(dq) == -1);

    deque_push_back(dq, &values[1]);
    assert(*(int*) deque_front(dq) == -1);

    deque_push_front(dq, &values[2]);
    assert(*(int*) deque_front(dq) == 24);

    deque_push_front(dq, &values[3]);
    assert(*(int*) deque_front(dq) == 59);

    deque_pop_back(dq);
    assert(*(int*) deque_front(dq) == 59);

    deque_pop_front(dq);
    assert(*(int*) deque_front(dq) == 24);

    deque_pop_front(dq);
    assert(*(int*) deque_front(dq) == -1);

    deque_pop_front(dq);
    assert(deque_front(dq) == NULL);

    deque_free(dq);
}

void test_deque_back() {
    int values[4] = {-1, 10, 24, 59};
    deque *dq = deque_init(sizeof(int));

    assert(deque_back(dq) == NULL);

    deque_push_front(dq, &values[0]);
    assert(*(int*) deque_back(dq) == -1);

    deque_push_front(dq, &values[1]);
    assert(*(int*) deque_back(dq) == -1);

    deque_push_back(dq, &values[2]);
    assert(*(int*) deque_back(dq) == 24);

    deque_push_back(dq, &values[3]);
    assert(*(int*) deque_back(dq) == 59);

    deque_pop_front(dq);
    assert(*(int*) deque_back(dq) == 59);

    deque_pop_back(dq);
    assert(*(int*) deque_back(dq) == 24);

    deque_pop_back(dq);
    assert(*(int*) deque_back(dq) == -1);

    deque_pop_back(dq);
    assert(deque_back(dq) == NULL);

    deque_free(dq);
}

void test_deque_pointers() {
    deque *dq = deque_init(sizeof(int));
    assert(deque_front(dq) == deque_back(dq));

    int value = 3;
    deque_push_front(dq, &value);
    assert(deque_front(dq) == deque_back(dq));

    deque_push_front(dq, &value);
    assert(deque_front(dq) != deque_back(dq));

    deque_pop_back(dq);
    assert(deque_front(dq) == deque_back(dq));

    deque_free(dq);
}

void test_deque_push_back() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    deque *dq = deque_init(sizeof(int));

    result = deque_push_back(dq, &values[0]);
    assert(*result == 51);

    result = deque_push_back(dq, &values[1]);
    assert(*result == 12);

    result = deque_push_back(dq, &values[2]);
    assert(*result == -123);

    result = deque_push_back(dq, &values[3]);
    assert(*result == 1000);

    result = deque_push_back(dq, &values[4]);
    assert(*result == -1);

    assert(deque_size(dq) == 5);

    deque_free(dq);
}

void test_deque_push_front() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    deque *dq = deque_init(sizeof(int));

    result = deque_push_front(dq, &values[0]);
    assert(*result == 51);

    result = deque_push_front(dq, &values[1]);
    assert(*result == 12);

    result = deque_push_front(dq, &values[2]);
    assert(*result == -123);

    result = deque_push_front(dq, &values[3]);
    assert(*result == 1000);

    result = deque_push_front(dq, &values[4]);
    assert(*result == -1);

    assert(deque_size(dq) == 5);

    deque_free(dq);
}

void test_deque_pop_back() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    deque *dq = deque_init(sizeof(int));
    deque_push_back(dq, &values[0]);
    deque_push_back(dq, &values[1]);
    deque_push_back(dq, &values[2]);
    deque_push_back(dq, &values[3]);
    deque_push_back(dq, &values[4]);

    assert(deque_size(dq) == 5);

    result = deque_pop_back(dq);
    assert(deque_size(dq) == 4);
    assert(*result == -1);

    result = deque_pop_back(dq);
    assert(deque_size(dq) == 3);
    assert(*result == 1000);

    result = deque_pop_back(dq);
    assert(deque_size(dq) == 2);
    assert(*result == -123);

    result = deque_pop_back(dq);
    assert(deque_size(dq) == 1);
    assert(*result == 12);

    result = deque_pop_back(dq);
    assert(deque_size(dq) == 0);
    assert(*result == 51);

    result = deque_pop_back(dq);
    assert(deque_size(dq) == 0);
    assert(result == NULL);

    deque_free(dq);
}

void test_deque_pop_front() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    deque *dq = deque_init(sizeof(int));
    deque_push_front(dq, &values[0]);
    deque_push_front(dq, &values[1]);
    deque_push_front(dq, &values[2]);
    deque_push_front(dq, &values[3]);
    deque_push_front(dq, &values[4]);

    assert(deque_size(dq) == 5);

    result = deque_pop_front(dq);
    assert(deque_size(dq) == 4);
    assert(*result == -1);

    result = deque_pop_front(dq);
    assert(deque_size(dq) == 3);
    assert(*result == 1000);

    result = deque_pop_front(dq);
    assert(deque_size(dq) == 2);
    assert(*result == -123);

    result = deque_pop_front(dq);
    assert(deque_size(dq) == 1);
    assert(*result == 12);

    result = deque_pop_front(dq);
    assert(deque_size(dq) == 0);
    assert(*result == 51);

    result = deque_pop_front(dq);
    assert(deque_size(dq) == 0);
    assert(result == NULL);

    deque_free(dq);
}

void test_LOAD() {
    bool empty;
    size_t size;
    size_t *at, *pushed, *popped, *front, *back;

    deque *dq = deque_init(sizeof(size_t));

    for (size_t i = 0; i < DEQUE_TEST_LOAD; i++) {
        pushed = deque_push_back(dq, &i);
        size = deque_size(dq);
        empty = deque_empty(dq);
        at = deque_at(dq, i);
        front = deque_front(dq);
        back = deque_back(dq);
        assert(*pushed == i);
        assert(size == i + 1);
        assert(!empty);
        assert(*at == i);
        assert(*front == 0);
        assert(*back == i);
    }

    for (size_t i = 0; i < DEQUE_TEST_LOAD / 2; i++) {
        popped = deque_pop_back(dq);
        size = deque_size(dq);
        empty = deque_empty(dq);
        at = deque_at(dq, i);
        front = deque_front(dq);
        back = deque_back(dq);
        assert(*popped == DEQUE_TEST_LOAD - i - 1);
        assert(size == DEQUE_TEST_LOAD - i - 1);
        assert(!empty);
        assert(*at == i);
        assert(*front == 0);
        assert(*back == DEQUE_TEST_LOAD - i - 2);
    }

    deque_clear(dq);
    size = deque_size(dq);
    empty = deque_empty(dq);
    assert(size == 0);
    assert(empty);

    for (size_t i = 0; i < DEQUE_TEST_LOAD; i++) {
        pushed = deque_push_front(dq, &i);
        size = deque_size(dq);
        empty = deque_empty(dq);
        at = deque_at(dq, i);
        back = deque_back(dq);
        assert(*pushed == i);
        assert(size == i + 1);
        assert(!empty);
        assert(*at == 0);
    }

    for (size_t i = 0; i < DEQUE_TEST_LOAD - 1; i++) {
        popped = deque_pop_front(dq);
        size = deque_size(dq);
        empty = deque_empty(dq);
        back = deque_back(dq);
        assert(*popped == DEQUE_TEST_LOAD - i - 1);
        assert(size == DEQUE_TEST_LOAD - i - 1);
        assert(!empty);
    }

    deque_clear(dq);
    size = deque_size(dq);
    empty = deque_empty(dq);
    assert(size == 0);
    assert(empty);

    deque_free(dq);
}

void test_deque() {
    test_deque_init();
    test_deque_init_fail();
    test_deque_free();
    test_deque_size();
    test_deque_empty();
    test_deque_clear();
    test_deque_at();
    test_deque_front();
    test_deque_back();
    test_deque_pointers();
    test_deque_push_back();
    test_deque_push_front();
    test_deque_pop_back();
    test_deque_pop_front();
    test_LOAD();
}
