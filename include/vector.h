#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct vector vector;

vector* vector_init(size_t type_size);

vector* vector_with_capacity(size_t type_size, size_t capacity);

void vector_free(vector *v);

size_t vector_size(const vector *v);

size_t vector_capacity(const vector *v);

bool vector_empty(const vector *v);

void vector_clear(vector *v);

void* vector_at(const vector *v, size_t index);

void* vector_set(const vector *v, size_t index, const void *value);

void* vector_begin(const vector *v);

void* vector_back(const vector *v);

void* vector_end(const vector *v);

void* vector_push(vector *v, const void *value);

void* vector_pop(vector *v);

void* vector_insert(vector *v, size_t index, const void *value);

void* vector_erase(vector *v, size_t index);

void* vector_resize(vector *v, size_t capacity);

#endif // INCLUDE_VECTOR_H_
