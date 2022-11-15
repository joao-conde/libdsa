#include <stdint.h>
#include <string.h>

#include "../../include/vector.h"

#define CAPACITY 256
#define ALLOC_FACTOR 2

struct Vector {
    unsigned int length;
    unsigned int capacity;
    size_t type_size;
    void *data;
};

Vector* vector(size_t type_size) {
    Vector *vec = malloc(sizeof(Vector));
    void *data = malloc(type_size * CAPACITY);
    if (vec == NULL || data == NULL) {
        free(data);
        free(vec);
        return NULL;
    }

    vec->length = 0;
    vec->capacity = CAPACITY;
    vec->type_size = type_size;
    vec->data = data;
    return vec;
}

Vector* vector_with_capacity(size_t type_size, unsigned int capacity) {
    Vector *vec = malloc(sizeof(Vector));
    void *data = malloc(type_size * capacity);
    if (vec == NULL || data == NULL) {
        free(data);
        free(vec);
        return NULL;
    }

    vec->length = 0;
    vec->capacity = capacity;
    vec->type_size = type_size;
    vec->data = data;
    return vec;
}

Vector* vector_from_array(size_t type_size, unsigned int length, const void *array) {
    unsigned int capacity = CAPACITY > length ? CAPACITY : length * ALLOC_FACTOR;

    Vector *vec = malloc(sizeof(Vector));
    void *data = malloc(type_size * capacity);
    if (vec == NULL || data == NULL) {
        free(data);
        free(vec);
        return NULL;
    }

    memcpy(data, array, length * type_size);

    vec->length = length;
    vec->capacity = capacity;
    vec->type_size = type_size;
    vec->data = data;
    return vec;
}

void vector_free(Vector *vec) {
    free(vec->data);
    free(vec);
}

unsigned int vector_length(const Vector *vec) {
    return vec->length;
}

unsigned int vector_capacity(const Vector *vec) {
    return vec->capacity;
}

bool vector_empty(const Vector *vec) {
    return vec->length == 0;
}

void* vector_begin(const Vector *vec) {
    return vec->data;
}

void* vector_end(const Vector *vec) {
    return (uint8_t*) vec->data + vec->length * vec->type_size;
}

void* vector_at(const Vector *vec, unsigned int index) {
    if (index >= vec->length) return NULL;
    return (uint8_t*) vec->data + index * vec->type_size;
}

void* vector_push(Vector *vec, void *value) {
    if (vec->length >= vec->capacity) {
        void *result = vector_resize(vec, vec->capacity * ALLOC_FACTOR);
        if (result == NULL) return NULL;
    }

    uint8_t *dest = (uint8_t*) vec->data + vec->length * vec->type_size;
    vec->length += 1;
    return memcpy(dest, value, vec->type_size);
}

void* vector_pop(Vector *vec) {
    if (vec->length == 0) return NULL;
    void *popped = (uint8_t*) vec->data + (vec->length - 1) * vec->type_size;
    vec->length -= 1;
    return popped;
}

void* vector_insert(Vector *vec, unsigned int index, void *value) {
    if (index > vec->length) return NULL;
    if (vec->length >= vec->capacity) {
        void *result = vector_resize(vec, vec->capacity * ALLOC_FACTOR);
        if (result == NULL) return NULL;
    }
    void *pos = (uint8_t*) vec->data + index * vec->type_size;
    unsigned int to_copy = vec->length - index;
    memmove(pos + vec->type_size, pos, to_copy * vec->type_size);
    vec->length += 1;
    return memcpy(pos, value, vec->type_size);
}

void* vector_erase(Vector *vec, unsigned int index) {
    if (index > vec->length) return NULL;
    void *pos = (uint8_t*) vec->data + index * vec->type_size;
    unsigned int to_copy = vec->length - index;
    vec->length -= 1;
    return memmove(pos, pos + vec->type_size, to_copy * vec->type_size);
}

void* vector_resize(Vector *vec, unsigned int capacity) {
    void *data = realloc(vec->data, vec->type_size * capacity);
    if (data != NULL) vec->data = data;

    vec->length = vec->length > capacity ? capacity : vec->length;
    vec->capacity = capacity;
    return data;
}
