#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct vector vector;

vector* vec(size_t type_size);

vector* vec_with_capacity(size_t type_size, unsigned int capacity);

vector* vec_from_array(size_t type_size, unsigned int length, const void *array);

void vec_free(vector *vector);

unsigned int vec_length(const vector *vector);

unsigned int vec_capacity(const vector *vector);

bool vec_empty(const vector *v);

void* vec_at(const vector *vector, unsigned int index);

void* vec_begin(const vector *v);

void* vec_end(const vector *v);

void* vec_push(vector *vector, void *value);

void* vec_pop(vector *vector);

void* vec_insert(vector *vector, unsigned int index, void *value);

void* vec_erase(vector *vector, unsigned int index);

void* vec_resize(vector *v, unsigned int capacity);

#endif // INCLUDE_VECTOR_H_
