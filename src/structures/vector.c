#include <stdlib.h>
#include <string.h>

#include "../../include/vector.h"

#define ALLOC_FACTOR 2

struct Vector {
    unsigned int length;
    unsigned int capacity;
    size_t type_size;
    void* data;
};

Vector* vector(size_t type_size, unsigned int capacity) {
    Vector* vector = malloc(sizeof(Vector));
    vector->length = 0;
    vector->capacity = capacity;
    vector->type_size = type_size;
    vector->data = malloc(type_size * capacity);
    return vector;
}

void vector_free(Vector* vector) {
    free(vector->data);
    free(vector);
}

unsigned int vector_length(Vector* vector) {
    return vector->length;
}

unsigned int vector_capacity(Vector* vector) {
    return vector->capacity;
}

void* vector_get(Vector* vector, unsigned int index) {
    if (index >= vector->length) return NULL;
    return vector->data + index;
}

void* vector_set(Vector* vector, unsigned int index, void* value) {
    if (index >= vector->length) return NULL;
    memcpy(vector->data, value, vector->type_size);
    return value;
}

void* vector_push(Vector* vector, void* value) {
    vector->length += 1;
    vector_set(vector, vector->length - 1, value);
    return value;
}
