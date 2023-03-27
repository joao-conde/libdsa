#include "benchmark.h"

void bc_list_push_back() {
    list *l = list_init(sizeof(size_t));
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_push_back(l, &i);
    }
    list_free(l);
}

void bc_list_push_front() {
    list *l = list_init(sizeof(size_t));
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_push_front(l, &i);
    }
    list_free(l);
}

void bc_list_push_pop_back() {
    list *l = list_init(sizeof(size_t));
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_push_back(l, &i);
    }
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_pop_back(l);
    }
    list_free(l);
}

void bc_list_push_pop_front() {
    list *l = list_init(sizeof(size_t));
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_push_front(l, &i);
    }
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_pop_front(l);
    }
    list_free(l);
}

void bc_list_insert() {
    list *l = list_init(sizeof(size_t));

    size_t dummy = 1;
    list_push_back(l, &dummy);

    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_insert(l, list_front(l), &i);
    }
    list_free(l);
}

void bc_list_insert_erase() {
    list *l = list_init(sizeof(size_t));

    size_t dummy = 1;
    list_push_back(l, &dummy);

    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_insert(l, list_front(l), &i);
    }
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_erase(l, list_front(l));
    }
    list_free(l);
}

void bc_list_push_clear() {
    list *l = list_init(sizeof(size_t));
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_push_back(l, &i);
    }
    list_clear(l);
}
