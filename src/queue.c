#include "../include/deque.h"
#include "../include/queue.h"

struct queue {
    deque *data;
};

queue* queue_init(size_t type_size) {
    queue *q = malloc(sizeof(queue));
    deque *data = deque_init(type_size);
    if (q == NULL || data == NULL) {
        deque_free(data);
        free(q);
        return NULL;
    }

    q->data = data;
    return q;
}

void queue_free(queue *q) {
    if (q != NULL) deque_free(q->data);
    free(q);
}

size_t queue_length(const queue *q) {
    return deque_length(q->data);
}

bool queue_is_empty(const queue *q) {
    return deque_is_empty(q->data);
}

void queue_clear(queue *q) {
    deque_clear(q->data);
}

void* queue_at(const queue *q, size_t index) {
    return deque_at(q->data, index);
}

void* queue_front(const queue *q) {
    return deque_front(q->data);
}

void* queue_back(const queue *q) {
    return deque_back(q->data);
}

void* queue_push(queue *q, const void *value) {
    return deque_push_back(q->data, value);
}

void* queue_pop(queue *q) {
    return deque_pop_front(q->data);
}
