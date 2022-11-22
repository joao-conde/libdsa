#ifndef INCLUDE_QUEUE_H_
#define INCLUDE_QUEUE_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct queue queue;

queue* queue_init(size_t type_size);

void queue_free(queue *q);

size_t queue_length(const queue *q);

bool queue_is_empty(const queue *q);

void queue_clear(queue *q);

void* queue_at(const queue *q, size_t index);

void* queue_front(const queue *q);

void* queue_back(const queue *q);

void* queue_push(queue *q, const void *value);

void* queue_pop(queue *q);

#endif // INCLUDE_QUEUE_H_
