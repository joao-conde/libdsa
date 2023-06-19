#ifndef INCLUDE_HEAP_H_
#define INCLUDE_HEAP_H_

#include <stdbool.h>
#include <stdlib.h>

typedef bool (lt_fn)(const void* a, const void* b);

typedef struct heap heap;

heap* heap_init(size_t type_size, lt_fn *lesser);

void heap_free(heap *h);

size_t heap_size(const heap *h);

bool heap_empty(const heap *h);

void heap_clear(heap *h);

void* heap_top(const heap *h);

void heap_push(heap *h, const void *value);

void heap_pop(heap *h);

#endif // INCLUDE_HEAP_H_
