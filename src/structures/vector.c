#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/vector.h"

#define CAPACITY 256
#define ALLOC_FACTOR 2

struct Vector {
    unsigned int length;
    unsigned int capacity;
    size_t type_size;
    void* data;
};

Vector* vector(size_t type_size) {
    Vector* vector = malloc(sizeof(Vector));
    void* data = malloc(type_size * CAPACITY);
    if (vector == NULL || data == NULL) {
        free(data);
        free(vector);
        return NULL;
    }

    vector->length = 0;
    vector->capacity = CAPACITY;
    vector->type_size = type_size;
    vector->data = data;
    return vector;
}

Vector* vector_with_capacity(size_t type_size, unsigned int capacity) {
    Vector* vector = malloc(sizeof(Vector));
    void* data = malloc(type_size * capacity);
    if (vector == NULL || data == NULL) {
        free(data);
        free(vector);
        return NULL;
    }

    vector->length = 0;
    vector->capacity = capacity;
    vector->type_size = type_size;
    vector->data = data;
    return vector;
}

Vector* vector_from_array(size_t type_size, unsigned int length, void* array) {
    unsigned int capacity = CAPACITY > length ? CAPACITY : length * ALLOC_FACTOR;

    Vector* vector = malloc(sizeof(Vector));
    void* data = malloc(type_size * capacity);
    if (vector == NULL || data == NULL) {
        free(data);
        free(vector);
        return NULL;
    }

    vector->length = length;
    vector->capacity = capacity;
    vector->type_size = type_size;
    vector->data = data;
    for (int i = 0; i < length; i++) {
        uint8_t *dest = (uint8_t*) vector->data + i * type_size;
        uint8_t *src = (uint8_t*) array + i * type_size;
        memcpy(dest, src, type_size);
    }
    return vector;
}

void vector_free(Vector* vector) {
    free(vector->data);
    free(vector);
}

unsigned int vector_length(const Vector* vector) {
    return vector->length;
}

unsigned int vector_capacity(const Vector* vector) {
    return vector->capacity;
}

void* vector_at(Vector* vector, unsigned int index) {
    if (index >= vector->length) return NULL;
    return (uint8_t*) vector->data + index * vector->type_size;
}

void* vector_push(Vector* vector, void* value) {
    // @TODO implement resizing for push
    uint8_t *dest = (uint8_t*) vector->data + vector->length * vector->type_size;
    memcpy(dest, value, vector->type_size);
    vector->length += 1;
    return value;
}
