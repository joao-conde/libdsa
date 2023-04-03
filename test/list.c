#include <assert.h>
#include <stdint.h>

#include "../include/list.h"

#define TEST_LOAD 100000

void test_list_init() {
    list *l = list_init(sizeof(int));
    assert(list_empty(l));
    assert(list_front(l) == NULL);
    assert(list_back(l) == NULL);
    list_free(l);
}

void test_list_free() {
    list_free(NULL);

    list *l = list_init(sizeof(int));
    list_free(l);
}

void test_list_size() {
    float value = 3.5;
    list *l = list_init(sizeof(float));
    assert(list_size(l) == 0);

    list_node *pushed = list_push_back(l, &value);
    assert(list_size(l) == 1);
    assert(list_front(l) == pushed);
    assert(list_back(l) == pushed);

    list_push_back(l, &value);
    list_push_back(l, &value);
    assert(list_size(l) == 3);

    list_free(l);
}

void test_list_empty() {
    list *l = list_init(sizeof(int));
    assert(list_empty(l));

    int value = -10;
    list_push_back(l, &value);
    assert(!list_empty(l));

    list_pop_front(l);
    assert(list_empty(l));

    list_free(l);
}

void test_list_clear() {
    int values[2] = {15, 21};
    list *l = list_init(sizeof(int));
    assert(list_empty(l));

    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    assert(list_size(l) == 2);

    list_clear(l);
    assert(list_empty(l));

    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    assert(list_size(l) == 2);

    list_free(l);
}

void test_list_front() {
    int values[4] = {-1, 10, 24, 59};
    list *l = list_init(sizeof(int));

    assert(list_front(l) == NULL);

    list_push_back(l, &values[0]);
    assert(*(int*) list_front(l)->data == -1);

    list_push_back(l, &values[1]);
    assert(*(int*) list_front(l)->data == -1);

    list_push_front(l, &values[2]);
    assert(*(int*) list_front(l)->data == 24);

    list_push_front(l, &values[3]);
    assert(*(int*) list_front(l)->data == 59);

    list_pop_back(l);
    assert(*(int*) list_front(l)->data == 59);

    list_pop_front(l);
    assert(*(int*) list_front(l)->data == 24);

    list_pop_front(l);
    assert(*(int*) list_front(l)->data == -1);

    list_pop_front(l);
    assert(list_front(l) == NULL);

    list_free(l);
}

void test_list_back() {
    int values[4] = {-1, 10, 24, 59};
    list *l = list_init(sizeof(int));

    assert(list_back(l) == NULL);

    list_push_front(l, &values[0]);
    assert(*(int*) list_back(l)->data == -1);

    list_push_front(l, &values[1]);
    assert(*(int*) list_back(l)->data == -1);

    list_push_back(l, &values[2]);
    assert(*(int*) list_back(l)->data == 24);

    list_push_back(l, &values[3]);
    assert(*(int*) list_back(l)->data == 59);

    list_pop_front(l);
    assert(*(int*) list_back(l)->data == 59);

    list_pop_back(l);
    assert(*(int*) list_back(l)->data == 24);

    list_pop_back(l);
    assert(*(int*) list_back(l)->data == -1);

    list_pop_back(l);
    assert(list_back(l) == NULL);

    list_free(l);
}

void test_list_pointers() {
    list *l = list_init(sizeof(int));
    assert(list_front(l) == list_back(l));

    int value = 3;
    list_push_front(l, &value);
    assert(list_front(l) == list_back(l));

    list_push_front(l, &value);
    assert(list_front(l) != list_back(l));

    list_pop_back(l);
    assert(list_front(l) == list_back(l));

    list_free(l);
}

void test_list_push_back() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    list *l = list_init(sizeof(int));

    result = list_push_back(l, &values[0])->data;
    assert(*result == 51);

    result = list_push_back(l, &values[1])->data;
    assert(*result == 12);

    result = list_push_back(l, &values[2])->data;
    assert(*result == -123);

    result = list_push_back(l, &values[3])->data;
    assert(*result == 1000);

    result = list_push_back(l, &values[4])->data;
    assert(*result == -1);

    assert(list_size(l) == 5);

    list_free(l);
}

void test_list_push_back_fail() {
    list_node *result;
    list *l = list_init(PTRDIFF_MAX);

    result = list_push_back(l, NULL);
    assert(result == NULL);

    list_free(l);
}

void test_list_push_front() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    list *l = list_init(sizeof(int));

    result = list_push_front(l, &values[0])->data;
    assert(*result == 51);

    result = list_push_front(l, &values[1])->data;
    assert(*result == 12);

    result = list_push_front(l, &values[2])->data;
    assert(*result == -123);

    result = list_push_front(l, &values[3])->data;
    assert(*result == 1000);

    result = list_push_front(l, &values[4])->data;
    assert(*result == -1);

    assert(list_size(l) == 5);

    list_free(l);
}

void test_list_push_front_fail() {
    list_node *result;
    list *l = list_init(PTRDIFF_MAX);

    result = list_push_front(l, NULL);
    assert(result == NULL);

    list_free(l);
}

void test_list_pop_back() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    list *l = list_init(sizeof(int));
    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);
    list_push_back(l, &values[3]);
    list_push_back(l, &values[4]);

    result = list_back(l)->data;
    assert(*result == -1);
    assert(list_size(l) == 5);

    list_pop_back(l);
    result = list_back(l)->data;
    assert(*result == 1000);
    assert(list_size(l) == 4);

    list_pop_back(l);
    result = list_back(l)->data;
    assert(*result == -123);
    assert(list_size(l) == 3);

    list_pop_back(l);
    result = list_back(l)->data;
    assert(*result == 12);
    assert(list_size(l) == 2);

    list_pop_back(l);
    result = list_back(l)->data;
    assert(*result == 51);
    assert(list_size(l) == 1);

    list_pop_back(l);
    assert(list_back(l) == NULL);
    assert(list_size(l) == 0);

    list_free(l);
}

void test_list_pop_front() {
    int *result, values[5] = {51, 12, -123, 1000, -1};
    list *l = list_init(sizeof(int));
    list_push_front(l, &values[0]);
    list_push_front(l, &values[1]);
    list_push_front(l, &values[2]);
    list_push_front(l, &values[3]);
    list_push_front(l, &values[4]);

    result = list_front(l)->data;
    assert(*result == -1);
    assert(list_size(l) == 5);

    list_pop_front(l);
    result = list_front(l)->data;
    assert(*result == 1000);
    assert(list_size(l) == 4);

    list_pop_front(l);
    result = list_front(l)->data;
    assert(*result == -123);
    assert(list_size(l) == 3);

    list_pop_front(l);
    result = list_front(l)->data;
    assert(*result == 12);
    assert(list_size(l) == 2);

    list_pop_front(l);
    result = list_front(l)->data;
    assert(*result == 51);
    assert(list_size(l) == 1);

    list_pop_front(l);
    assert(list_front(l) == NULL);
    assert(list_size(l) == 0);

    list_free(l);
}

void test_list_insert() {
    int values[4] = {15, 21, 30, 69};
    list *l = list_init(sizeof(int));
    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);
    list_push_back(l, &values[3]);
    assert(list_size(l) == 4);

    list_node *inserted, *pos, *next, *front, *back;

    front = list_front(l);
    back = list_back(l);
    pos = front;
    next = pos->next;
    inserted = list_insert(l, pos, &values[0]);
    assert(pos->next == inserted);
    assert(next->prev == inserted);
    assert(inserted->prev == pos);
    assert(inserted->next == next);
    assert(list_size(l) == 5);
    assert(list_front(l) == front);
    assert(list_back(l) == back);

    front = list_front(l);
    back = list_back(l);
    pos = front->next->next;
    next = pos->next;
    inserted = list_insert(l, pos, &values[0]);
    assert(pos->next == inserted);
    assert(next->prev == inserted);
    assert(inserted->prev == pos);
    assert(inserted->next == next);
    assert(list_size(l) == 6);
    assert(list_front(l) == front);
    assert(list_back(l) == back);

    front = list_front(l);
    back = list_back(l);
    pos = back;
    inserted = list_insert(l, pos, &values[0]);
    assert(back->next == inserted);
    assert(inserted->prev == pos);
    assert(inserted->next == NULL);
    assert(list_size(l) == 7);
    assert(list_front(l) == front);
    assert(list_back(l) == inserted);

    list_free(l);
}

void test_list_insert_fail() {
    list_node *result;
    list *l = list_init(PTRDIFF_MAX);

    result = list_insert(l, NULL, NULL);
    assert(result == NULL);

    list_free(l);
}

void test_list_erase() {
    int values[4] = {15, 21, 30, 69};
    list *l = list_init(sizeof(int));
    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);
    list_push_back(l, &values[3]);
    list_push_back(l, &values[0]);
    list_push_back(l, &values[1]);
    list_push_back(l, &values[2]);
    list_push_back(l, &values[3]);
    assert(list_size(l) == 8);

    list_node *prev, *pos, *next, *front, *back;

    front = list_front(l);
    back = list_back(l);
    pos = front;
    next = pos->next;
    list_erase(l, pos);
    assert(next->prev == NULL);
    assert(list_size(l) == 7);
    assert(list_front(l) == next);
    assert(list_back(l) == back);

    front = list_front(l);
    back = list_back(l);
    pos = front->next->next;
    prev = pos->prev;
    next = pos->next;
    list_erase(l, pos);
    assert(prev->next == next);
    assert(next->prev == prev);
    assert(list_size(l) == 6);
    assert(list_front(l) == front);
    assert(list_back(l) == back);

    front = list_front(l);
    back = list_back(l);
    pos = back;
    prev = pos->prev;
    list_erase(l, pos);
    assert(prev->next == NULL);
    assert(list_size(l) == 5);
    assert(list_front(l) == front);
    assert(list_back(l) == prev);

    list_free(l);
}

void test_list_load() {
    bool empty;
    size_t size;
    list_node *pushed, *inserted, *erased, *front, *back, *current;

    list *l = list_init(sizeof(int));

    for (int i = 0; i < TEST_LOAD; i++) {
        pushed = list_push_back(l, &i);
        size = list_size(l);
        empty = list_empty(l);
        front = list_front(l);
        back = list_back(l);
        assert(*(int*)pushed->data == i);
        assert(size == i + 1);
        assert(!empty);
        assert(*(int*)front->data == 0);
        assert(*(int*)back->data == i);
    }

    for (int i = 0; i < TEST_LOAD - 1; i++) {
        list_pop_back(l);
        size = list_size(l);
        empty = list_empty(l);
        front = list_front(l);
        back = list_back(l);
        assert(size == TEST_LOAD - i - 1);
        assert(!empty);
        assert(*(int*)front->data == 0);
        assert(*(int*)back->data == TEST_LOAD - i - 2);
    }

    list_pop_back(l);
    size = list_size(l);
    empty = list_empty(l);
    assert(size == 0);
    assert(empty);
    assert(list_front(l) == NULL);
    assert(list_back(l) == NULL);

    for (int i = 0; i < TEST_LOAD; i++) {
        pushed = list_push_front(l, &i);
        size = list_size(l);
        empty = list_empty(l);
        front = list_front(l);
        back = list_back(l);
        assert(*(int*)pushed->data == i);
        assert(size == i + 1);
        assert(!empty);
        assert(*(int*)front->data == i);
        assert(*(int*)back->data == 0);
    }

    for (int i = 0; i < TEST_LOAD - 1; i++) {
        list_pop_front(l);
        size = list_size(l);
        empty = list_empty(l);
        front = list_front(l);
        back = list_back(l);
        assert(size == TEST_LOAD - i - 1);
        assert(!empty);
        assert(*(int*)front->data == TEST_LOAD - i - 2);
        assert(*(int*)back->data == 0);
    }

    list_pop_front(l);
    size = list_size(l);
    empty = list_empty(l);
    assert(size == 0);
    assert(empty);
    assert(list_front(l) == NULL);
    assert(list_back(l) == NULL);

    current = list_push_front(l, &pushed);
    for (int i = 0; i < TEST_LOAD - 1; i++) {
        inserted = list_insert(l, current, &i);
        size = list_size(l);
        empty = list_empty(l);
        front = list_front(l);
        back = list_back(l);
        assert(*(int*)inserted->data == i);
        assert(size == i + 2);
        assert(!empty);
        assert(front == current);
        assert(*(int*)back->data == 0);
    }

    current = list_front(l);
    for (int i = 0; i < TEST_LOAD - 1; i++) {
        erased = current;
        current = current->next != NULL ? current->next : current->prev;
        list_erase(l, erased);
        size = list_size(l);
        empty = list_empty(l);
        front = list_front(l);
        back = list_back(l);
        assert(size == TEST_LOAD - i - 1);
        assert(!empty);
        assert(front != NULL);
        assert(back != NULL);
    }

    list_pop_front(l);
    size = list_size(l);
    empty = list_empty(l);
    assert(size == 0);
    assert(empty);
    assert(list_front(l) == NULL);
    assert(list_back(l) == NULL);

    list_free(l);
}

void test_list() {
    test_list_init();
    test_list_free();
    test_list_size();
    test_list_empty();
    test_list_clear();
    test_list_front();
    test_list_back();
    test_list_pointers();
    test_list_push_back();
    test_list_push_front();
    test_list_push_front_fail();
    test_list_pop_back();
    test_list_pop_front();
    test_list_insert();
    test_list_insert_fail();
    test_list_erase();
    test_list_load();
}
