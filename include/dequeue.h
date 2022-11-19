#ifndef INCLUDE_DEQUEUE_H_
#define INCLUDE_DEQUEUE_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct dequeue dequeue;

dequeue* dequeue_init(size_t type_size);

void dequeue_free(dequeue *dq);

size_t dequeue_length(const dequeue *dq);

bool dequeue_is_empty(const dequeue *dq);

void* dequeue_front(const dequeue *dq);

void* dequeue_back(const dequeue *dq);

void* dequeue_push_back(dequeue *dq, const void *value);

void* dequeue_push_front(dequeue *dq, const void *value);

void* dequeue_pop_back(dequeue *dq);

void* dequeue_pop_front(dequeue *dq);

#endif // INCLUDE_DEQUEUE_H_
