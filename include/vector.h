#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <stdlib.h>

#define OUT_OF_BOUNDS -1

typedef struct Vector Vector;

Vector* vector(size_t type_size, unsigned int capacity);
void vector_free(Vector* vector);
unsigned int vector_length(Vector* vector);
unsigned int vector_capacity(Vector* vector);
void* vector_get(Vector* vector, unsigned int index);
void* vector_set(Vector* vector, unsigned int index, void* value);
void* vector_push(Vector* vector, void* value);

#endif // INCLUDE_VECTOR_H_
