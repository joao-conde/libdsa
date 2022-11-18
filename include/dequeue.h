#ifndef INCLUDE_DEQUEUE_H_
#define INCLUDE_DEQUEUE_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct dequeue dequeue;

dequeue* dequeue_init(size_t type_size);

void dequeue_free(dequeue *d);

size_t dequeue_length(const dequeue *d);

bool dequeue_is_empty(const dequeue *d);

void* dequeue_front(const dequeue *d);

void* dequeue_back(const dequeue *d);

void* dequeue_push_back(dequeue *d, const void *value);

void* dequeue_push_front(dequeue *d, const void *value);

void* dequeue_pop_back(dequeue *d);

void* dequeue_pop_front(dequeue *d);

#endif // INCLUDE_DEQUEUE_H_
