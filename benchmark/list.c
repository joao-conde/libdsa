#include "benchmark.h"

void* c_list_init() {
    list *l = list_init(sizeof(size_t));
    for (size_t i = 0; i < LOAD; i++) {
        list_push_back(l, &i);
    }
    return l;
}

void c_list_free(void *data) {
    list_free((list*) data);
}

void c_list_push_back(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LOAD; i++) {
        list_push_back(l, &i);
    }
}

void c_list_push_front(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LOAD; i++) {
        list_push_front(l, &i);
    }
}

void c_list_pop_back(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LOAD; i++) {
        list_pop_back(l);
    }
}

void c_list_pop_front(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LOAD; i++) {
        list_pop_front(l);
    }
}

void c_list_insert(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LOAD; i++) {
        list_insert(l, list_front(l), &i);
    }
}

void c_list_erase(void *data) {
    list *l = (list*) data;
    for (size_t i = 0; i < LOAD; i++) {
        list_erase(l, list_front(l));
    }
}

void c_list_clear(void *data) {
    list *l = (list*) data;
    list_clear(l);
}
