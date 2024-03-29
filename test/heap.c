#include <assert.h>
#include <stdint.h>

#include "test.h"

#include "../include/heap.h"

void test_heap_init() {
    heap *h = heap_init(sizeof(int), lt_int);
    assert(heap_empty(h));
    heap_free(h);
}

void test_heap_init_fail() {
    heap *h = heap_init(SIZE_MAX, NULL);
    assert(h == NULL);

    h = heap_init(SIZE_MAX / 1000, NULL);
    assert(h == NULL);
}

void test_heap_free() {
    heap_free(NULL);

    heap *h = heap_init(sizeof(int), lt_int);
    heap_free(h);
}

void test_heap_size() {
    float value = 3.5;
    heap *h = heap_init(sizeof(float), lt_float);
    assert(heap_size(h) == 0);

    heap_push(h, &value);
    heap_push(h, &value);
    heap_push(h, &value);
    assert(heap_size(h) == 3);

    heap_free(h);
}

void test_heap_empty() {
    heap *h = heap_init(sizeof(int), lt_int);
    assert(heap_empty(h));

    int value = -10;
    heap_push(h, &value);
    assert(!heap_empty(h));

    heap_pop(h);
    assert(heap_empty(h));

    heap_free(h);
}

void test_heap_clear() {
    float value = 3.5;
    heap *h = heap_init(sizeof(float), lt_float);
    heap_push(h, &value);
    heap_push(h, &value);
    heap_push(h, &value);
    assert(heap_size(h) == 3);

    heap_clear(h);
    assert(heap_size(h) == 0);

    heap_free(h);
}

void test_heap_top() {
    int values[5] = {51, 12, -123, 1000, -1};
    heap *max_heap = heap_init(sizeof(int), lt_int);
    heap *min_heap = heap_init(sizeof(int), gt_int);

    for (int i = 0; i < 5; i++) {
        heap_push(max_heap, values + i);
        heap_push(min_heap, values + i);
    }

    assert(*(int*)heap_top(max_heap) == 1000);
    assert(*(int*)heap_top(min_heap) == -123);

    heap_pop(max_heap);
    heap_pop(min_heap);
    assert(*(int*)heap_top(max_heap) == 51);
    assert(*(int*)heap_top(min_heap) == -1);

    heap_pop(max_heap);
    heap_pop(min_heap);
    assert(*(int*)heap_top(max_heap) == 12);
    assert(*(int*)heap_top(min_heap) == 12);

    heap_pop(max_heap);
    heap_pop(min_heap);
    assert(*(int*)heap_top(max_heap) == -1);
    assert(*(int*)heap_top(min_heap) == 51);

    heap_pop(max_heap);
    heap_pop(min_heap);
    assert(*(int*)heap_top(max_heap) == -123);
    assert(*(int*)heap_top(min_heap) == 1000);

    heap_pop(max_heap);
    heap_pop(min_heap);
    assert(heap_top(max_heap) == NULL);
    assert(heap_top(min_heap) == NULL);

    heap_free(max_heap);
    heap_free(min_heap);
}

void test_heap_push() {
    int values[5] = {51, 12, -123, 1000, -1};
    heap *h = heap_init(sizeof(int), lt_int);

    for (int i = 0; i < 5; i++) heap_push(h, values + i);

    assert(heap_size(h) == 5);

    heap_free(h);
}

void test_heap_pop() {
    int values[5] = {51, 12, -123, 1000, -1};
    heap *h = heap_init(sizeof(int), lt_int);

    for (int i = 0; i < 5; i++) heap_push(h, values + i);

    assert(heap_size(h) == 5);

    heap_pop(h);
    assert(heap_size(h) == 4);

    heap_pop(h);
    assert(heap_size(h) == 3);

    heap_pop(h);
    assert(heap_size(h) == 2);

    heap_pop(h);
    assert(heap_size(h) == 1);

    heap_pop(h);
    assert(heap_size(h) == 0);

    heap_pop(h);
    assert(heap_size(h) == 0);

    heap_free(h);
}

void test_heap_load() {
    bool empty;
    size_t size, *top;

    heap *h = heap_init(sizeof(size_t), lt_size_t);

    for (size_t i = 0; i < TEST_LOAD; i++) {
        heap_push(h, &i);
        size = heap_size(h);
        empty = heap_empty(h);
        top = heap_top(h);
        assert(size == i + 1);
        assert(!empty);
        assert(*(size_t*) top == i);
    }

    for (size_t i = 0; i < TEST_LOAD - 1; i++) {
        heap_pop(h);
        size = heap_size(h);
        empty = heap_empty(h);
        top = heap_top(h);
        assert(size == TEST_LOAD - i - 1);
        assert(!empty);
        assert(*(size_t*) top == TEST_LOAD - i - 2);
    }

    heap_clear(h);
    size = heap_size(h);
    empty = heap_empty(h);
    assert(size == 0);
    assert(empty);

    heap_free(h);
}

void test_heap() {
    test_heap_init();
    test_heap_init_fail();
    test_heap_free();
    test_heap_size();
    test_heap_empty();
    test_heap_clear();
    test_heap_top();
    test_heap_push();
    test_heap_pop();
    test_heap_load();
}
