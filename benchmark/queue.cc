#include <queue>

#include "benchmark.h"

void* bcc_queue_init() {
    std::queue<size_t> *q = new std::queue<size_t>();
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        q->push(i);
    }
    return q;
}

void bcc_queue_free(void *data) {
    free((std::queue<size_t>*) data);
}

void bcc_queue_push(void *data) {
    std::queue<size_t> *q = (std::queue<size_t>*) data;
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        q->push(i);
    }
}

void bcc_queue_pop(void *data) {
    std::queue<size_t> *q = (std::queue<size_t>*) data;
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        q->pop();
    }
}

void bcc_queue_clear(void *data) {
    std::queue<size_t> *q = (std::queue<size_t>*) data;
    std::queue<size_t> empty_q;
    std::swap(*q, empty_q);
}
