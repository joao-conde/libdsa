#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct vector vector;

vector* vec(size_t type_size);

vector* vec_with_capacity(size_t type_size, unsigned int capacity);

vector* vec_from_array(size_t type_size, unsigned int length, const void *array);

void vec_free(vector *v);

unsigned int vec_length(const vector *v);

unsigned int vec_capacity(const vector *v);

bool vec_empty(const vector *v);

void* vec_at(const vector *v, unsigned int index);

void* vec_begin(const vector *v);

void* vec_end(const vector *v);

void* vec_push(vector *v, void *value);

void* vec_pop(vector *v);

void* vec_insert(vector *v, unsigned int index, void *value);

void* vec_erase(vector *v, unsigned int index);

void* vec_resize(vector *v, unsigned int capacity);

#endif // INCLUDE_VECTOR_H_
