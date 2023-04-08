#include "benchmark.h"

void* bc_queue_init() {
    queue *q = queue_init(sizeof(size_t));
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        queue_push(q, &i);
    }
    return q;
}

void bc_queue_free(void *data) {
    queue_free((queue*) data);
}

void bc_queue_push(void *data) {
    queue *q = (queue*) data;
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        queue_push(q, &i);
    }
}

void bc_queue_pop(void *data) {
    queue *q = (queue*) data;
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        queue_pop(q);
    }
}

void bc_queue_clear(void *data) {
    queue *q = (queue*) data;
    queue_clear(q);
}
