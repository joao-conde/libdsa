#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct vector vector;

vector* vec(size_t type_size);

vector* vec_with_capacity(size_t type_size, size_t capacity);

vector* vec_from_array(size_t type_size, size_t length, const void *array);

void vec_free(vector *v);

size_t vec_length(const vector *v);

size_t vec_capacity(const vector *v);

bool vec_empty(const vector *v);

void* vec_at(const vector *v, size_t index);

void* vec_set(const vector *v, size_t index, const void *value);

void* vec_begin(const vector *v);

void* vec_back(const vector *v);

void* vec_end(const vector *v);

void* vec_push(vector *v, const void *value);

void* vec_pop(vector *v);

void* vec_insert(vector *v, size_t index, const void *value);

void* vec_erase(vector *v, size_t index);

void vec_clear(vector *v);

void* vec_resize(vector *v, size_t capacity);

#endif // INCLUDE_VECTOR_H_
