#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <stdlib.h>

typedef struct Vector Vector;

Vector* vector(size_t type_size);

Vector* vector_with_capacity(size_t type_size, unsigned int capacity);

Vector* vector_from_array(size_t type_size, unsigned int length, const void *array);

void vector_free(Vector *vector);

unsigned int vector_length(const Vector *vector);

unsigned int vector_capacity(const Vector *vector);

void* vector_at(const Vector *vector, unsigned int index);

void* vector_push(Vector *vector, void *value);

void* vector_resize(Vector *vec, unsigned int capacity);

#endif // INCLUDE_VECTOR_H_
