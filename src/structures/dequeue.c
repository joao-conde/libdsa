#include <stdint.h>
#include <string.h>

#include "../../include/dequeue.h"
#include "../../include/vector.h"

#define CHUNK_CAPACITY 256

struct dequeue {
    size_t length;
    size_t type_size;
    size_t front_chunk;
    size_t back_chunk;
    size_t front;
    size_t back;
    vector *chunks;
};

void *get_element(dequeue *dq, size_t chunk, size_t offset) {
    return vector_at(dq->chunks, chunk) + offset * dq->type_size;
}

bool decrement_front(dequeue *dq) {
    // if it reaches -1 we need to allocate new chunk and set to max
    if (dq->front > 0) {
        dq->front -= 1;
        return true;
    }

    void *chunk = malloc(CHUNK_CAPACITY * dq->type_size);
    if (chunk == NULL) return false;

    vector_insert(dq->chunks, 0, chunk);
    dq->back_chunk += 1;
    dq->front_chunk = 0;
    dq->front = CHUNK_CAPACITY - 1;
    return true;
}

void* increment_front(dequeue *dq) {
    void *popped = get_element(dq, dq->front_chunk, dq->front);
    dq->front += 1;
    if (dq->front < CHUNK_CAPACITY) return popped;

    dq->front = 0;
    dq->front_chunk += 1;
    return popped;
}

bool increment_back(dequeue *dq) {
    dq->back += 1;
    if (dq->back < CHUNK_CAPACITY) return true;

    void *chunk = malloc(CHUNK_CAPACITY * dq->type_size);
    if (chunk == NULL) return false;

    vector_push(dq->chunks, chunk);
    dq->back_chunk = vector_length(dq->chunks) - 1;
    dq->back = 0;
    return true;
}

void* decrement_back(dequeue *dq) {
    void *popped = get_element(dq, dq->back_chunk, dq->back);
    if (dq->back > 0) {
        dq->back -= 1;
        return popped;
    }

    dq->back = CHUNK_CAPACITY - 1;
    dq->back_chunk -= 1;
    return popped;
}

dequeue* dequeue_init(size_t type_size) {
    // checks for overflow of amount of requested memory
    if (type_size && CHUNK_CAPACITY > (SIZE_MAX / type_size)) return NULL;

    dequeue *self = malloc(sizeof(dequeue));
    void *chunks = vector_init(sizeof(void*));
    void *chunk = malloc(CHUNK_CAPACITY * type_size);
    if (self == NULL || chunks == NULL || chunk == NULL) {
        free(chunk);
        vector_free(chunks);
        free(self);
        return NULL;
    }

    vector_push(chunks, chunk);

    self->length = 0;
    self->type_size = type_size;
    self->front_chunk = 0;
    self->back_chunk = 0;
    self->front = 0;
    self->back = 0;
    self->chunks = chunks;
    return self;
}

void dequeue_free(dequeue *dq) {
    if (dq != NULL) vector_free(dq->chunks);
    free(dq);
}

size_t dequeue_length(const dequeue *dq) {
    return dq->length;
}

bool dequeue_is_empty(const dequeue *dq) {
    return dq->length == 0;
}

void* dequeue_front(const dequeue *dq) {
    if (dequeue_is_empty(dq)) return NULL;
    void *chunk = vector_at(dq->chunks, dq->front_chunk);
    void *front = chunk + dq->front * dq->type_size;
    return front;
}

void* dequeue_back(const dequeue *dq) {
    if (dequeue_is_empty(dq)) return NULL;
    void *chunk = vector_at(dq->chunks, dq->back_chunk);
    void *back = chunk + dq->back * dq->type_size;
    return back;
}

void* dequeue_push_back(dequeue *dq, const void *value) {
    if (dequeue_is_empty(dq)) {
        dq->front = 0;
        dq->back = 0;
    } else {
        increment_back(dq);
    }

    dq->length += 1;

    void *chunk = vector_at(dq->chunks, dq->back_chunk);
    void *dst = chunk + dq->back * dq->type_size;
    void *pushed = memcpy(dst, value, dq->type_size);
    return pushed;
}

void* dequeue_push_front(dequeue *dq, const void *value) {
    if (dequeue_is_empty(dq)) {
        dq->front = 0;
        dq->back = 0;
    } else {
        decrement_front(dq);
    }

    dq->length += 1;


    uint8_t *chunk = vector_at(dq->chunks, dq->front_chunk);
    uint8_t *dst = chunk + dq->front * dq->type_size;
    void *pushed = memcpy(dst, value, dq->type_size);
    return pushed;
}

void* dequeue_pop_back(dequeue *dq) {
    if (dequeue_is_empty(dq)) return NULL;
    void *popped = decrement_back(dq);
    dq->length -= 1;
    return popped;
}

void* dequeue_pop_front(dequeue *dq) {
    if (dequeue_is_empty(dq)) return NULL;
    void *popped = increment_front(dq);
    dq->length -= 1;
    return popped;
}
