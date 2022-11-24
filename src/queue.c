#include "../include/dequeue.h"
#include "../include/queue.h"

struct queue {
    dequeue *data;
};

queue* queue_init(size_t type_size) {
    queue *q = malloc(sizeof(queue));
    dequeue *data = dequeue_init(type_size);
    if (q == NULL || data == NULL) {
        dequeue_free(data);
        free(q);
        return NULL;
    }

    q->data = data;
    return q;
}

void queue_free(queue *q) {
    if (q != NULL) dequeue_free(q->data);
    free(q);
}

size_t queue_length(const queue *q) {
    return dequeue_length(q->data);
}

bool queue_is_empty(const queue *q) {
    return dequeue_is_empty(q->data);
}

void queue_clear(queue *q) {
    dequeue_clear(q->data);
}

void* queue_at(const queue *q, size_t index) {
    return dequeue_at(q->data, index);
}

void* queue_front(const queue *q) {
    return dequeue_front(q->data);
}

void* queue_back(const queue *q) {
    return dequeue_back(q->data);
}

void* queue_push(queue *q, const void *value) {
    return dequeue_push_back(q->data, value);
}

void* queue_pop(queue *q) {
    return dequeue_pop_front(q->data);
}
