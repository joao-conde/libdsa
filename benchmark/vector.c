#include "benchmark.h"

void* c_vector_init() {
    vector *v = vector_init(sizeof(size_t));
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        vector_push(v, &i);
    }
    return v;
}

void c_vector_free(void *data) {
    vector_free((vector*) data);
}

void c_vector_push(void *data) {
    vector *v = (vector*) data;
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        vector_push(v, &i);
    }
}

void c_vector_pop(void *data) {
    vector *v = (vector*) data;
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        vector_pop(v);
    }
}

void c_vector_set(void *data) {
    vector *v = (vector*) data;
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        vector_set(v, i, &i);
    }
}

void c_vector_resize(void *data) {
    vector *v = (vector*) data;
    vector_resize(v, 1);
}

void c_vector_insert(void *data) {
    vector *v = (vector*) data;
    size_t size = vector_size(v);
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        vector_insert(v, size + i, &i);
    }
}

void c_vector_erase(void *data) {
    vector *v = (vector*) data;
    size_t size = vector_size(v);
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        vector_erase(v, size - 1 - i);
    }
}

void c_vector_at(void *data) {
    vector *v = (vector*) data;
    for (size_t i = 0; i < VECTOR_LOAD; i++) {
        size_t *x = (size_t*) vector_at(v, i);
    }
}

void c_vector_clear(void *data) {
    vector *v = (vector*) data;
    vector_clear(v);
}
