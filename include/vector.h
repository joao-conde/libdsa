#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <stdlib.h>

#define OUT_OF_BOUNDS -1

typedef struct Vector Vector;

Vector* vector(size_t type_size);
Vector* vector_with_capacity(size_t type_size, unsigned int capacity);
Vector* vector_from_array(size_t type_size, unsigned int length, void *array);
void vector_free(Vector *vector);
unsigned int vector_length(const Vector *vector);
unsigned int vector_capacity(const Vector *vector);
void* vector_at(Vector *vector, unsigned int index);
void* vector_push(Vector *vector, void *value);

#endif // INCLUDE_VECTOR_H_
