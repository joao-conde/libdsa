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

    vec->length = length;
    vec->capacity = capacity;
    vec->type_size = type_size;
    vec->data = data;
    for (int i = 0; i < length; i++) {
        uint8_t *dest = (uint8_t*) vec->data + i * type_size;
        uint8_t *src = (uint8_t*) array + i * type_size;
        memcpy(dest, src, type_size);
    }
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
    memcpy(dest, value, vec->type_size);
    vec->length += 1;
    return value;
}

void* vector_resize(Vector *vec, unsigned int capacity) {
    void *data = realloc(vec->data, vec->type_size * capacity);
    if (data != NULL) vec->data = data;

    vec->length = vec->length > capacity ? capacity : vec->length;
    vec->capacity = capacity;
    return data;
}
