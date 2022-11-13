#include <stdint.h>
#include <stdio.h>
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
    vector->length = 0;
    vector->capacity = CAPACITY;
    vector->type_size = type_size;
    vector->data = malloc(type_size * CAPACITY);
    return vector;
}

Vector* vector_with_capacity(size_t type_size, unsigned int capacity) {
    Vector* vector = malloc(sizeof(Vector));
    vector->length = 0;
    vector->capacity = capacity;
    vector->type_size = type_size;
    vector->data = malloc(type_size * capacity);
    return vector;
}

Vector* vector_from_array(size_t type_size, unsigned int length, void* array) {
    Vector* vector = malloc(sizeof(Vector));
    vector->length = length;
    vector->capacity = CAPACITY >= length ? CAPACITY : length * ALLOC_FACTOR;
    vector->type_size = type_size;
    vector->data = malloc(type_size * vector->capacity);
    for (int i = 0; i < length; i++) {
        memcpy((uint8_t*) vector->data + i * type_size, (uint8_t*) array + i * type_size, type_size);
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
    vector->length += 1;
    memcpy((uint8_t*) vector->data + vector->length * vector->type_size, value, vector->type_size);
    return value;
}
