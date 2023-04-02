#ifndef INCLUDE_DEQUE_H_
#define INCLUDE_DEQUE_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct deque deque;

deque* deque_init(size_t type_size);

void deque_free(deque *dq);

size_t deque_length(const deque *dq);

bool deque_empty(const deque *dq);

void deque_clear(deque *dq);

void* deque_at(const deque *dq, size_t index);

void* deque_front(const deque *dq);

void* deque_back(const deque *dq);

void* deque_push_back(deque *dq, const void *value);

void* deque_push_front(deque *dq, const void *value);

void* deque_pop_back(deque *dq);

void* deque_pop_front(deque *dq);

#endif // INCLUDE_DEQUE_H_
