#include <assert.h>
#include <stdint.h>

#include "../include/stack.h"

#define TEST_LOAD 100000

void test_stack_init() {
    stack *s = stack_init(sizeof(int));
    assert(stack_empty(s));
    stack_free(s);
}

void test_stack_init_fail() {
    stack *s = stack_init(SIZE_MAX);
    assert(s == NULL);

    s = stack_init(SIZE_MAX / 1000);
    assert(s == NULL);
}

void test_stack_free() {
    stack_free(NULL);

    stack *s = stack_init(sizeof(int));
    stack_free(s);
}

void test_stack_size() {
    float value = 3.5;
    stack *s = stack_init(sizeof(float));
    assert(stack_size(s) == 0);

    stack_push(s, &value);
    stack_push(s, &value);
    stack_push(s, &value);
    assert(stack_size(s) == 3);

    stack_free(s);
}

void test_stack_empty() {
    stack *s = stack_init(sizeof(int));
    assert(stack_empty(s));

    int value = -10;
    stack_push(s, &value);
    assert(!stack_empty(s));

    stack_pop(s);
    assert(stack_empty(s));

    stack_free(s);
}

void test_stack_clear() {
    float value = 3.5;
    stack *s = stack_init(sizeof(float));
    stack_push(s, &value);
    stack_push(s, &value);
    stack_push(s, &value);
    assert(stack_size(s) == 3);

    stack_clear(s);
    assert(stack_size(s) == 0);

    stack_free(s);
}

void test_stack_top() {
    int values[4] = {-1, 10, 24, 59};
    stack *s = stack_init(sizeof(int));

    assert(stack_top(s) == NULL);

    stack_push(s, &values[0]);
    assert(*(int*) stack_top(s) == -1);

    stack_push(s, &values[1]);
    assert(*(int*) stack_top(s) == 10);

    stack_push(s, &values[2]);
    assert(*(int*) stack_top(s) == 24);

    stack_push(s, &values[3]);
    assert(*(int*) stack_top(s) == 59);

    stack_pop(s);
    assert(*(int*) stack_top(s) == 24);

    stack_pop(s);
    assert(*(int*) stack_top(s) == 10);

    stack_pop(s);
    assert(*(int*) stack_top(s) == -1);

    stack_pop(s);
    assert(stack_top(s) == NULL);

    stack_free(s);
}

void test_stack_push() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    stack *s = stack_init(sizeof(int));

    result = stack_push(s, &values[0]);
    assert(*result == 51);

    result = stack_push(s, &values[1]);
    assert(*result == 12);

    result = stack_push(s, &values[2]);
    assert(*result == -123);

    result = stack_push(s, &values[3]);
    assert(*result == 1000);

    result = stack_push(s, &values[4]);
    assert(*result == -1);

    assert(stack_size(s) == 5);

    stack_free(s);
}

void test_stack_push_void_ptrs() {
    void *d1 = malloc(10 * sizeof(void*));
    void *d2 = malloc(10 * sizeof(void*));
    void *d3 = malloc(10 * sizeof(void*));

    stack *s = stack_init(sizeof(void*));
    stack_push(s, &d1);
    stack_push(s, &d2);
    stack_push(s, &d3);
    assert(*(void**)stack_pop(s) == d3);
    assert(*(void**)stack_pop(s) == d2);
    assert(*(void**)stack_pop(s) == d1);

    stack_free(s);
    free(d3);
    free(d2);
    free(d1);
}

void test_stack_pop() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    stack *s = stack_init(sizeof(int));
    stack_push(s, &values[0]);
    stack_push(s, &values[1]);
    stack_push(s, &values[2]);
    stack_push(s, &values[3]);
    stack_push(s, &values[4]);

    assert(stack_size(s) == 5);

    result = stack_pop(s);
    assert(stack_size(s) == 4);
    assert(*result == -1);

    result = stack_pop(s);
    assert(stack_size(s) == 3);
    assert(*result == 1000);

    result = stack_pop(s);
    assert(stack_size(s) == 2);
    assert(*result == -123);

    result = stack_pop(s);
    assert(stack_size(s) == 1);
    assert(*result == 12);

    result = stack_pop(s);
    assert(stack_size(s) == 0);
    assert(*result == 51);

    result = stack_pop(s);
    assert(stack_size(s) == 0);
    assert(result == NULL);

    stack_free(s);
}

void test_stack_load() {
    bool empty;
    size_t size;
    int *top, *pushed, *popped;

    stack *s = stack_init(sizeof(int));

    for (int i = 0; i < TEST_LOAD; i++) {
        pushed = stack_push(s, &i);
        size = stack_size(s);
        empty = stack_empty(s);
        top = stack_top(s);
        assert(*pushed == i);
        assert(size == i + 1);
        assert(!empty);
        assert(*top == i);
    }

    for (int i = 0; i < TEST_LOAD / 2; i++) {
        top = stack_top(s);
        popped = stack_pop(s);
        size = stack_size(s);
        empty = stack_empty(s);
        assert(*popped == TEST_LOAD - i - 1);
        assert(size == TEST_LOAD - i - 1);
        assert(!empty);
        assert(*top == *popped);
    }

    stack_clear(s);
    size = stack_size(s);
    empty = stack_empty(s);
    assert(size == 0);
    assert(empty);

    stack_free(s);
}

void test_stack() {
    test_stack_init();
    test_stack_init_fail();
    test_stack_free();
    test_stack_size();
    test_stack_empty();
    test_stack_clear();
    test_stack_top();
    test_stack_push();
    test_stack_push_void_ptrs();
    test_stack_pop();
    test_stack_load();
}
