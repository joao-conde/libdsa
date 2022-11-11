#include <stdlib.h>

#include "../../include/vector.h"

#define ALLOC_FACTOR 2

struct Vector {
    unsigned int length;
    unsigned int capacity;
    void* data;
};

Vector* vector(size_t type_size, unsigned int capacity) {
    Vector* vector = malloc(sizeof(Vector));
    vector->length = 0;
    vector->capacity = capacity;
    vector->data = malloc(type_size * capacity);
    return vector;
}

unsigned int vector_length(Vector* vector) {
    return vector->length;
}

unsigned int vector_capacity(Vector* vector) {
    return vector->capacity;
}
