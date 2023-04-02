#include <assert.h>
#include <stdint.h>

#include "../include/queue.h"

void test_queue_init() {
    queue *q = queue_init(sizeof(int));
    assert(queue_empty(q));
    queue_free(q);
}

void test_queue_init_fail() {
    queue *q = queue_init(SIZE_MAX);
    assert(q == NULL);

    q = queue_init(SIZE_MAX / 1000);
    assert(q == NULL);
}

void test_queue_free() {
    queue_free(NULL);

    queue *q = queue_init(sizeof(int));
    queue_free(q);
}

void test_queue_length() {
    float value = 3.5;
    queue *q = queue_init(sizeof(float));
    assert(queue_length(q) == 0);

    queue_push(q, &value);
    queue_push(q, &value);
    queue_push(q, &value);
    assert(queue_length(q) == 3);

    queue_free(q);
}

void test_queue_empty() {
    queue *q = queue_init(sizeof(int));
    assert(queue_empty(q));

    int value = -10;
    queue_push(q, &value);
    assert(!queue_empty(q));

    queue_pop(q);
    assert(queue_empty(q));

    queue_free(q);
}

void test_queue_clear() {
    float value = 3.5;
    queue *q = queue_init(sizeof(float));
    queue_push(q, &value);
    queue_push(q, &value);
    queue_push(q, &value);
    assert(queue_length(q) == 3);

    queue_clear(q);
    assert(queue_length(q) == 0);

    queue_free(q);
}

void test_queue_at() {
    int values[5] = {51, 12, -123, 1000, -1};
    queue *q = queue_init(sizeof(int));
    assert(queue_at(q, 0) == NULL);

    queue_push(q, &values[0]);
    queue_push(q, &values[1]);
    queue_push(q, &values[2]);
    queue_push(q, &values[3]);
    queue_push(q, &values[4]);
    assert(*(int*)queue_at(q, 0) == 51);
    assert(*(int*)queue_at(q, 1) == 12);
    assert(*(int*)queue_at(q, 2) == -123);
    assert(*(int*)queue_at(q, 3) == 1000);
    assert(*(int*)queue_at(q, 4) == -1);
    assert(queue_at(q, 5) == NULL);

    queue_free(q);
}

void test_queue_front() {
    int values[4] = {-1, 10, 24, 59};
    queue *q = queue_init(sizeof(int));

    assert(queue_front(q) == NULL);

    queue_push(q, &values[0]);
    assert(*(int*) queue_front(q) == -1);

    queue_push(q, &values[1]);
    assert(*(int*) queue_front(q) == -1);

    queue_push(q, &values[2]);
    assert(*(int*) queue_front(q) == -1);

    queue_push(q, &values[3]);
    assert(*(int*) queue_front(q) == -1);

    queue_pop(q);
    assert(*(int*) queue_front(q) == 10);

    queue_pop(q);
    assert(*(int*) queue_front(q) == 24);

    queue_pop(q);
    assert(*(int*) queue_front(q) == 59);

    queue_pop(q);
    assert(queue_front(q) == NULL);

    queue_free(q);
}

void test_queue_back() {
    int values[4] = {-1, 10, 24, 59};
    queue *q = queue_init(sizeof(int));

    assert(queue_back(q) == NULL);

    queue_push(q, &values[0]);
    assert(*(int*) queue_back(q) == -1);

    queue_push(q, &values[1]);
    assert(*(int*) queue_back(q) == 10);

    queue_push(q, &values[2]);
    assert(*(int*) queue_back(q) == 24);

    queue_push(q, &values[3]);
    assert(*(int*) queue_back(q) == 59);

    queue_pop(q);
    assert(*(int*) queue_back(q) == 59);

    queue_pop(q);
    assert(*(int*) queue_back(q) == 59);

    queue_pop(q);
    assert(*(int*) queue_back(q) == 59);

    queue_pop(q);
    assert(queue_back(q) == NULL);

    queue_free(q);
}

void test_queue_pointers() {
    queue *q = queue_init(sizeof(int));
    assert(queue_front(q) == queue_back(q));

    int value = 3;
    queue_push(q, &value);
    assert(queue_front(q) == queue_back(q));

    queue_push(q, &value);
    assert(queue_front(q) != queue_back(q));

    queue_pop(q);
    assert(queue_front(q) == queue_back(q));

    queue_free(q);
}

void test_queue_push() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    queue *q = queue_init(sizeof(int));

    result = queue_push(q, &values[0]);
    assert(*result == 51);

    result = queue_push(q, &values[1]);
    assert(*result == 12);

    result = queue_push(q, &values[2]);
    assert(*result == -123);

    result = queue_push(q, &values[3]);
    assert(*result == 1000);

    result = queue_push(q, &values[4]);
    assert(*result == -1);

    assert(queue_length(q) == 5);

    queue_free(q);
}

void test_queue_pop() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    queue *q = queue_init(sizeof(int));
    queue_push(q, &values[0]);
    queue_push(q, &values[1]);
    queue_push(q, &values[2]);
    queue_push(q, &values[3]);
    queue_push(q, &values[4]);

    assert(queue_length(q) == 5);

    result = queue_pop(q);
    assert(queue_length(q) == 4);
    assert(*result == 51);

    result = queue_pop(q);
    assert(queue_length(q) == 3);
    assert(*result == 12);

    result = queue_pop(q);
    assert(queue_length(q) == 2);
    assert(*result == -123);

    result = queue_pop(q);
    assert(queue_length(q) == 1);
    assert(*result == 1000);

    result = queue_pop(q);
    assert(queue_length(q) == 0);
    assert(*result == -1);

    result = queue_pop(q);
    assert(queue_length(q) == 0);
    assert(result == NULL);

    queue_free(q);
}

void test_queue_load() {
    int nelements = 100000;
    bool empty;
    size_t length;
    int *at, *pushed, *popped, *front, *back;

    queue *q = queue_init(sizeof(int));

    for (int i = 0; i < nelements; i++) {
        pushed = queue_push(q, &i);
        length = queue_length(q);
        empty = queue_empty(q);
        at = queue_at(q, i);
        front = queue_front(q);
        back = queue_back(q);
        assert(*pushed == i);
        assert(length == i + 1);
        assert(!empty);
        assert(*at == i);
        assert(*front == 0);
        assert(*back == i);
    }

    for (int i = 0; i < nelements / 2; i++) {
        at = queue_at(q, 0);
        front = queue_front(q);
        back = queue_back(q);
        popped = queue_pop(q);
        length = queue_length(q);
        empty = queue_empty(q);
        assert(*popped == i);
        assert(length == nelements - i - 1);
        assert(!empty);
        assert(*at == *popped);
        assert(*front == i);
        assert(*back == nelements - 1);
    }

    queue_clear(q);
    length = queue_length(q);
    empty = queue_empty(q);
    assert(length == 0);
    assert(empty);

    queue_free(q);
}

void test_queue() {
    test_queue_init();
    test_queue_init_fail();
    test_queue_free();
    test_queue_length();
    test_queue_empty();
    test_queue_clear();
    test_queue_at();
    test_queue_front();
    test_queue_back();
    test_queue_pointers();
    test_queue_push();
    test_queue_pop();
    test_queue_load();
}
