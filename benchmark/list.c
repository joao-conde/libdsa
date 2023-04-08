#include "benchmark.h"

void* bc_list_init() {
    list *l = list_init(sizeof(size_t));
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_push_back(l, &i);
    }
    return l;
}

void bc_list_free(void *data) {
    list_free((list*) data);
}

void bc_list_push_back(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_push_back(l, &i);
    }
}

void bc_list_push_front(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_push_front(l, &i);
    }
}

void bc_list_pop_back(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_pop_back(l);
    }
}

void bc_list_pop_front(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_pop_front(l);
    }
}

void bc_list_insert(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_insert(l, list_front(l), &i);
    }
}

void bc_list_erase(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        list_erase(l, list_front(l));
    }
}

void bc_list_clear(void *data) {
    list *l = (list*) data;
    list_clear(l);
}
