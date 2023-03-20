#include "benchmark.h"

void bc_queue_push() {
    queue *q = queue_init(sizeof(size_t));
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        queue_push(q, &i);
    }
    queue_free(q);
}

void bc_queue_push_pop() {
    queue *q = queue_init(sizeof(size_t));
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        queue_push(q, &i);
    }
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        queue_pop(q);
    }
    queue_free(q);
}

void bc_queue_push_clear() {
    queue *q = queue_init(sizeof(size_t));
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        queue_push(q, &i);
    }
    queue_clear(q);
    queue_free(q);
}
