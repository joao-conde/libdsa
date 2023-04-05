#include <stdint.h>
#include <string.h>

#include "internal/vector.h"

#include "../include/vector.h"

struct vector {
    size_t size;
    size_t capacity;
    size_t type_size;
    void *data;
};

vector* vector_init(size_t type_size) {
    return vector_with_capacity(type_size, CAPACITY);
}

vector* vector_with_capacity(size_t type_size, size_t capacity) {
    // checks for overflow of amount of requested memory
    if (type_size && capacity > PTRDIFF_MAX / type_size) return NULL;

    vector *v = (vector*) malloc(sizeof(vector));
    void *data = malloc(capacity * type_size);
    if (v == NULL || data == NULL) {
        free(data);
        free(v);
        return NULL;
    }

    v->size = 0;
    v->capacity = capacity;
    v->type_size = type_size;
    v->data = data;
    return v;
}

void vector_free(vector *v) {
    if (v != NULL) free(v->data);
    free(v);
}

size_t vector_size(const vector *v) {
    return v->size;
}

size_t vector_capacity(const vector *v) {
    return v->capacity;
}

bool vector_empty(const vector *v) {
    return v->size == 0;
}

void vector_clear(vector *v) {
    v->size = 0;
}

void* vector_at(const vector *v, size_t index) {
    if (index >= v->size) return NULL;
    return (uint8_t*) v->data + index * v->type_size;
}

void* vector_set(const vector *v, size_t index, const void *value) {
    if (index >= v->size) return NULL;
    void *dst = (uint8_t*) v->data + index * v->type_size;
    return memcpy(dst, value, v->type_size);
}

void* vector_begin(const vector *v) {
    if (vector_empty(v)) return v->data;
    return vector_at(v, 0);
}

void* vector_back(const vector *v) {
    if (vector_empty(v)) return vector_begin(v);
    return vector_at(v, v->size - 1);
}

void* vector_end(const vector *v) {
    return (uint8_t*) vector_back(v) + v->type_size;
}

void* vector_push(vector *v, const void *value) {
    // if the vector is at capacity already we resize it
    // if the resizing fails the push operation halts
    if (v->size >= v->capacity) {
        size_t capacity = v->capacity > 0 ? v->capacity * ALLOC_FACTOR : CAPACITY;
        void *resized = vector_resize(v, capacity);
        if (resized == NULL) return NULL;
    }

    void *dst = (uint8_t*) v->data + v->size * v->type_size;
    v->size += 1;
    return memcpy(dst, value, v->type_size);
}

void* vector_pop(vector *v) {
    if (vector_empty(v)) return NULL;
    v->size -= 1;
    return (uint8_t*) v->data + v->size * v->type_size;
}

void* vector_insert(vector *v, size_t index, const void *value) {
    if (index > v->size) return NULL;

    // if the vector is at capacity already we resize it
    // if the resizing fails the insert operation halts
    if (v->size >= v->capacity) {
        size_t capacity = v->capacity > 0 ? v->capacity * ALLOC_FACTOR : CAPACITY;
        void *resized = vector_resize(v, capacity);
        if (resized == NULL) return NULL;
    }

    // computes the number of elements to copy and the
    // position of insertion
    size_t to_copy = v->size - index;
    uint8_t *pos = (uint8_t*) v->data + index * v->type_size;

    // shifts all elements right from the insertion position forward
    // and sets the insertion position to the inserted value
    // halts the insert operation if this shift fails
    void *moved = memmove(pos + v->type_size, pos, to_copy * v->type_size);
    if (moved == NULL) return NULL;

    v->size += 1;
    return memcpy(pos, value, v->type_size);
}

void* vector_erase(vector *v, size_t index) {
    if (index > v->size) return NULL;

    // computes the number of elements to copy and the
    // position of deletion
    size_t to_copy = v->size - index;
    uint8_t *pos = (uint8_t*) v->data + index * v->type_size;

    // shifts all elements left from the deletion position forward
    // halts the insert operation if this shift fails
    void *moved = memmove(pos, pos + v->type_size, to_copy * v->type_size);
    if (moved == NULL) return NULL;

    // returns a pointer to the position of the erased
    // element where a new element resides
    v->size -= 1;
    return moved;
}

void* vector_resize(vector *v, size_t capacity) {
    // checks for overflow of amount of requested memory
    if (v->type_size && capacity > PTRDIFF_MAX / v->type_size) return NULL;

    // attempts to resize the internal data buffer
    // failure is detected if a NULL pointer is returned
    // and the resizing was not of zero bytes
    void *data = realloc(v->data, v->type_size * capacity);
    if (capacity != 0 && data == NULL) return NULL;

    v->size = v->size > capacity ? capacity : v->size;
    v->capacity = capacity;
    v->data = data;
    return data;
}
