#include "benchmark.h"

void bc_vector_push() {
    vector *v = vector_init(sizeof(size_t));
    for (size_t i = 0; i < VECTOR_PUSHES; i++) {
        vector_push(v, &i);
    }
    vector_free(v);
}

void bc_vector_push_pop() {
    vector *v = vector_init(sizeof(size_t));
    for (size_t i = 0; i < VECTOR_PUSHES; i++) {
        vector_push(v, &i);
    }
    for (size_t i = 0; i < VECTOR_PUSHES; i++) {
        vector_pop(v);
    }
    vector_free(v);
}

void bc_vector_push_clear() {
    vector *v = vector_init(sizeof(size_t));
    for (size_t i = 0; i < VECTOR_PUSHES; i++) {
        vector_push(v, &i);
    }
    vector_clear(v);
    vector_free(v);
}

void bc_vector_push_at() {
    vector *v = vector_init(sizeof(size_t));
    for (size_t i = 0; i < VECTOR_PUSHES; i++) {
        vector_push(v, &i);
        size_t *x = (size_t*) vector_at(v, i);
    }
    vector_free(v);
}

void bc_vector_push_set() {
    vector *v = vector_init(sizeof(size_t));
    for (size_t i = 0; i < VECTOR_PUSHES; i++) {
        vector_push(v, &i);
        vector_set(v, i, &i);
    }
    vector_free(v);
}

void bc_vector_push_resize() {
    vector *v = vector_init(sizeof(size_t));
    for (size_t i = 0; i < VECTOR_PUSHES; i++) {
        vector_push(v, &i);
    }
    vector_resize(v, 1);
    vector_free(v);
}

void bc_vector_insert() {
    vector *v = vector_init(sizeof(size_t));
    for (size_t i = 0; i < VECTOR_INSERTS; i++) {
        vector_insert(v, 0, &i);
    }
    vector_free(v);
}

void bc_vector_insert_erase() {
    vector *v = vector_init(sizeof(size_t));
    for (size_t i = 0; i < VECTOR_INSERTS; i++) {
        vector_insert(v, 0, &i);
    }
    for (size_t i = 0; i < VECTOR_INSERTS; i++) {
        vector_erase(v, 0);
    }
    vector_free(v);
}
