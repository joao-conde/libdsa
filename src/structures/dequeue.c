#include <stdint.h>

#include "../../include/dequeue.h"

#define CHUNK_CAPACITY 256

struct dequeue {
    size_t length;
    size_t type_size;
    size_t nchunks;
    void *front;
    void *back;
    void **chunks;
};

dequeue* dequeue_init(size_t type_size) {
    dequeue *self = malloc(sizeof(dequeue));
    void **chunks = malloc(sizeof(void*));
    void *data = malloc(CHUNK_CAPACITY * type_size);
    if (self == NULL || chunks == NULL || data == NULL) {
        free(data);
        free(chunks);
        free(self);
        return NULL;
    }

    chunks[0] = data;

    self->length = 0;
    self->type_size = type_size;
    self->front = NULL;
    self->back = NULL;
    self->nchunks = 1;
    self->chunks = chunks;
    return self;
}

void dequeue_free(dequeue *dq) {
    if (dq != NULL) {
        for (int i = 0; i < dq->nchunks; i++) free(dq->chunks[i]);
        free(dq->chunks);
    }
    free(dq);
}

size_t dequeue_length(const dequeue *dq) {
    return dq->length;
}

bool dequeue_is_empty(const dequeue *dq) {
    return dq->length == 0;
}

void* dequeue_front(const dequeue *dq) {
    return dq->front;
}

void* dequeue_back(const dequeue *dq) {
    return dq->back;
}

void* dequeue_push_back(dequeue *dq, const void *value);

void* dequeue_push_front(dequeue *dq, const void *value);

void* dequeue_pop_back(dequeue *dq);

void* dequeue_pop_front(dequeue *dq);
