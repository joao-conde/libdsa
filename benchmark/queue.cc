#include <queue>

#include "benchmark.h"

void bcc_queue_push() {
    std::queue<size_t> q;
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        q.push(i);
    }
}

void bcc_queue_push_pop() {
    std::queue<size_t> q;
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        q.push(i);
    }
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        q.pop();
    }
}

void bcc_queue_push_clear() {
    std::queue<size_t> q;
    for (size_t i = 0; i < QUEUE_LOAD; i++) {
        q.push(i);
    }
    std::queue<size_t> empty_q;
    std::swap(q, empty_q);
}
