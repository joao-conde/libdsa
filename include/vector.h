#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <stdlib.h>

typedef struct Vector Vector;

Vector* vector(size_t type_size, unsigned int capacity);
unsigned int vector_length(Vector* vector);
unsigned int vector_capacity(Vector* vector);

#endif // INCLUDE_VECTOR_H_
