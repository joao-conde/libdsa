#include <stdint.h>
#include <string.h>

#include "../../include/vector.h"

#define CAPACITY 256
#define ALLOC_FACTOR 2

struct vector {
    size_t length;
    size_t capacity;
    size_t type_size;
    void *data;
};

vector* vector_init(size_t type_size) {
    return vector_with_capacity(type_size, CAPACITY);
}

vector* vector_with_capacity(size_t type_size, size_t capacity) {
    // checks for overflow of amount of requested memory
    if (type_size && capacity > SIZE_MAX / type_size) return NULL;

    vector *self = malloc(sizeof(vector));
    void *data = malloc(capacity * type_size);
    if (self == NULL || data == NULL) {
        free(data);
        free(self);
        return NULL;
    }

    self->length = 0;
    self->capacity = capacity;
    self->type_size = type_size;
    self->data = data;
    return self;
}

vector* vector_from_array(size_t type_size, size_t length, const void *array) {
    // computes vector capacity based on the array to copy length
    // if the vector would be at capacity by copying the original
    // array then we allocate a bigger one
    size_t capacity = CAPACITY > length ? CAPACITY : length * ALLOC_FACTOR;

    vector *self = vector_with_capacity(type_size, capacity);
    if (self == NULL) return NULL;

    // copies the array contents to internal data buffer
    memcpy(self->data, array, length * type_size);
    self->length = length;

    return self;
}

void vector_free(vector *v) {
    if (v != NULL) free(v->data);
    free(v);
}

size_t vector_length(const vector *v) {
    return v->length;
}

size_t vector_capacity(const vector *v) {
    return v->capacity;
}

bool vector_is_empty(const vector *v) {
    return v->length == 0;
}

void* vector_begin(const vector *v) {
    return v->data;
}

void* vector_back(const vector *v) {
    if (vector_is_empty(v)) return vector_begin(v);
    return (uint8_t*) v->data + (v->length - 1) * v->type_size;
}

void* vector_end(const vector *v) {
    return (uint8_t*) v->data + v->length * v->type_size;
}

void* vector_at(const vector *v, size_t index) {
    if (index >= v->length) return NULL;
    return (uint8_t*) v->data + index * v->type_size;
}

void* vector_set(const vector *v, size_t index, const void *value) {
    if (index >= v->length) return NULL;
    void *dst = (uint8_t*) v->data + index * v->type_size;
    return memcpy(dst, value, v->type_size);
}

void* vector_push(vector *v, const void *value) {
    // if the vector is at capacity already we resize it
    // if the resizing fails the push operation halts
    if (v->length >= v->capacity) {
        size_t capacity = v->capacity > 0 ? v->capacity * ALLOC_FACTOR : CAPACITY;
        void *resized = vector_resize(v, capacity);
        if (resized == NULL) return NULL;
    }

    void *dst = (uint8_t*) v->data + v->length * v->type_size;
    v->length += 1;
    return memcpy(dst, value, v->type_size);
}

void* vector_pop(vector *v) {
    if (vector_is_empty(v)) return NULL;
    v->length -= 1;
    return (uint8_t*) v->data + v->length * v->type_size;
}

void* vector_insert(vector *v, size_t index, const void *value) {
    if (index > v->length) return NULL;

    // if the vector is at capacity already we resize it
    // if the resizing fails the insert operation halts
    if (v->length >= v->capacity) {
        size_t capacity = v->capacity > 0 ? v->capacity * ALLOC_FACTOR : CAPACITY;
        void *resized = vector_resize(v, capacity);
        if (resized == NULL) return NULL;
    }

    // computes the number of elements to copy and the
    // position of insertion
    size_t to_copy = v->length - index;
    void *pos = (uint8_t*) v->data + index * v->type_size;

    // shifts all elements right from the insertion position forward
    // and sets the insertion position to the inserted value
    // halts the insert operation if this shift fails
    void *moved = memmove(pos + v->type_size, pos, to_copy * v->type_size);
    if (moved == NULL) return NULL;

    v->length += 1;
    return memcpy(pos, value, v->type_size);
}

void* vector_erase(vector *v, size_t index) {
    if (index > v->length) return NULL;

    // computes the number of elements to copy and the
    // position of deletion
    size_t to_copy = v->length - index;
    void *pos = (uint8_t*) v->data + index * v->type_size;

    // shifts all elements left from the deletion position forward
    // halts the insert operation if this shift fails
    void *moved = memmove(pos, pos + v->type_size, to_copy * v->type_size);
    if (moved == NULL) return NULL;

    v->length -= 1;

    // returns a pointer to the position of the erased
    // element where a new element resides
    return moved;
}

void vector_clear(vector *v) {
    v->length = 0;
}

void* vector_resize(vector *v, size_t capacity) {
    // checks for overflow of amount of requested memory
    if (v->type_size && capacity > SIZE_MAX / v->type_size) return NULL;

    // attempts to resize the internal data buffer
    // failure is detected if a NULL pointer is returned
    // and the resizing was not of zero bytes
    void *data = realloc(v->data, v->type_size * capacity);
    if (capacity != 0 && data == NULL) return NULL;

    v->length = v->length > capacity ? capacity : v->length;
    v->capacity = capacity;
    v->data = data;
    return data;
}
