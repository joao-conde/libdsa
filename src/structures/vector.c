#include <stdint.h>
#include <string.h>

#include "../../include/vector.h"

#define CAPACITY 256
#define ALLOC_FACTOR 2

struct vector {
    unsigned int length;
    unsigned int capacity;
    size_t type_size;
    void *data;
};

vector* vec(size_t type_size) {
    vector *v = malloc(sizeof(vector));
    void *data = calloc(CAPACITY, type_size);
    if (v == NULL || data == NULL) {
        free(data);
        free(v);
        return NULL;
    }

    v->length = 0;
    v->capacity = CAPACITY;
    v->type_size = type_size;
    v->data = data;
    return v;
}

vector* vec_with_capacity(size_t type_size, unsigned int capacity) {
    vector *v = malloc(sizeof(vector));
    void *data = calloc(capacity, type_size);
    if (v == NULL || data == NULL) {
        free(data);
        free(v);
        return NULL;
    }

    v->length = 0;
    v->capacity = capacity;
    v->type_size = type_size;
    v->data = data;
    return v;
}

vector* vec_from_array(size_t type_size, unsigned int length, const void *array) {
    // computes vector capacity based on the array to copy length
    // if the vector would be at capacity by copying the original
    // array then we allocate a bigger one
    unsigned int capacity = CAPACITY > length ? CAPACITY : length * ALLOC_FACTOR;

    vector *v = malloc(sizeof(vector));
    void *data = calloc(capacity, type_size);
    if (v == NULL || data == NULL) {
        free(data);
        free(v);
        return NULL;
    }

    // copies the array to copy contents to internal data buffer
    memcpy(data, array, length * type_size);

    v->length = length;
    v->capacity = capacity;
    v->type_size = type_size;
    v->data = data;
    return v;
}

void vec_free(vector *v) {
    free(v->data);
    free(v);
}

unsigned int vec_length(const vector *v) {
    return v->length;
}

unsigned int vec_capacity(const vector *v) {
    return v->capacity;
}

bool vec_empty(const vector *v) {
    return v->length == 0;
}

void* vec_begin(const vector *v) {
    return v->data;
}

void* vec_end(const vector *v) {
    return (uint8_t*) v->data + v->length * v->type_size;
}

void* vec_at(const vector *v, unsigned int index) {
    if (index >= v->length) return NULL;
    return (uint8_t*) v->data + index * v->type_size;
}

void* vec_push(vector *v, const void *value) {
    // if the vector is at capacity already we resize it
    // if the resizing fails the push operation halts
    if (v->length >= v->capacity) {
        unsigned int capacity = v->capacity > 0 ? v->capacity * ALLOC_FACTOR : CAPACITY;
        void *resized = vec_resize(v, capacity);
        if (resized == NULL) return NULL;
    }

    uint8_t *dest = (uint8_t*) v->data + v->length * v->type_size;
    v->length += 1;

    // returns a pointer to the pushed value
    void *pushed = memcpy(dest, value, v->type_size);
    return pushed;
}

void* vec_pop(vector *v) {
    if (v->length == 0) return NULL;

    v->length -= 1;

    // returns a pointer to the popped element
    void *popped = (uint8_t*) v->data + v->length * v->type_size;
    return popped;
}

void* vec_insert(vector *v, unsigned int index, const void *value) {
    if (index > v->length) return NULL;

    // if the vector is at capacity already we resize it
    // if the resizing fails the insert operation halts
    if (v->length >= v->capacity) {
        unsigned int capacity = v->capacity > 0 ? v->capacity * ALLOC_FACTOR : CAPACITY;
        void *resized = vec_resize(v, capacity);
        if (resized == NULL) return NULL;
    }

    // computes the number of elements to copy and the
    // position of insertion
    unsigned int to_copy = v->length - index;
    void *pos = (uint8_t*) v->data + index * v->type_size;

    // shifts all elements right from the insertion position forward
    // and sets the insertion position to the inserted value
    // halts the insert operation if this shift fails
    void *moved = memmove(pos + v->type_size, pos, to_copy * v->type_size);
    if (moved == NULL) return NULL;

    v->length += 1;

    // returns a pointer to the inserted value
    void *inserted = memcpy(pos, value, v->type_size);
    return inserted;
}

void* vec_erase(vector *v, unsigned int index) {
    if (index > v->length) return NULL;

    // computes the number of elements to copy and the
    // position of deletion
    unsigned int to_copy = v->length - index;
    void *pos = (uint8_t*) v->data + index * v->type_size;

    // shifts all elements left from the deletion position forward
    // halts the insert operation if this shift fails
    void *moved = memmove(pos, pos + v->type_size, to_copy * v->type_size);
    if (moved == NULL) return NULL;

    v->length -= 1;

    // returns a pointer to the position of the erased
    // element where a new vector element resides
    return moved;
}

void* vec_resize(vector *v, unsigned int capacity) {
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
