#include <stdint.h>
#include <string.h>

#include "../include/dequeue.h"
#include "../include/vector.h"

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

    // saves the first and only chunk pointer for now
    vector_push(chunks, &chunk);

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
    if (dq != NULL && dq->chunks != NULL) {
        // free each allocated chunk
        for (int i = 0; i < vector_length(dq->chunks); i++) {
            void *chunk = *(void**)vector_at(dq->chunks, i);
            free(chunk);
        }

        // free the chunks container
        vector_free(dq->chunks);
    }

    free(dq);
}

size_t dequeue_length(const dequeue *dq) {
    return dq->length;
}

bool dequeue_is_empty(const dequeue *dq) {
    return dq->length == 0;
}

void dequeue_clear(dequeue *dq) {
    dq->length = 0;
    dq->front_chunk = 0;
    dq->back_chunk = 0;
    dq->front = 0;
    dq->back = 0;
}

void* dequeue_at(const dequeue *dq, size_t index) {
    if (index >= dq->length) return NULL;
    size_t i = dq->front_chunk * CHUNK_CAPACITY + dq->front + index;
    size_t chunk_i = i / CHUNK_CAPACITY;
    size_t value_i = i % CHUNK_CAPACITY;
    void *chunk = *(void**)vector_at(dq->chunks, chunk_i);
    void *value = (uint8_t*) chunk + value_i * dq->type_size;
    return value;
}

void* dequeue_front(const dequeue *dq) {
    return dequeue_at(dq, 0);
}

void* dequeue_back(const dequeue *dq) {
    if (dequeue_is_empty(dq)) return dequeue_front(dq);
    return dequeue_at(dq, dq->length - 1);
}

void* dequeue_push_back(dequeue *dq, const void *value) {
    if (!dequeue_is_empty(dq)) {
        dq->back += 1;

        // if current back chunk capacity has been reached
        // allocate a new one in the back and update back
        // and back chunk indexes accordingly
        if (dq->back >= CHUNK_CAPACITY) {
            void *chunk = malloc(CHUNK_CAPACITY * dq->type_size);
            if (chunk == NULL) return NULL;

            vector_push(dq->chunks, &chunk);
            dq->back_chunk = vector_length(dq->chunks) - 1;
            dq->back = 0;
        }
    }

    dq->length += 1;
    void *dst = dequeue_at(dq, dq->length - 1);
    void *pushed = memcpy(dst, value, dq->type_size);
    return pushed;
}

void* dequeue_push_front(dequeue *dq, const void *value) {
    if (!dequeue_is_empty(dq)) {
        // if current front chunk capacity has been reached
        // allocate a new one in the front and update front,
        // front chunk and back chunk indexes accordingly
        if (dq->front == 0) {
            void *chunk = malloc(CHUNK_CAPACITY * dq->type_size);
            if (chunk == NULL) return NULL;

            vector_insert(dq->chunks, 0, &chunk);
            dq->back_chunk += 1;
            dq->front_chunk = 0;
            dq->front = CHUNK_CAPACITY;
        }

        dq->front -= 1;
    }

    dq->length += 1;
    void *dst = dequeue_at(dq, 0);
    void *pushed = memcpy(dst, value, dq->type_size);
    return pushed;
}

void* dequeue_pop_back(dequeue *dq) {
    if (dequeue_is_empty(dq)) return NULL;

    void *popped = dequeue_at(dq, dq->length - 1);

    // if the current back chunk is empty after the pop, update
    // indexes to point to the last element of the next previous chunk
    if (dq->back == 0) {
        dq->back = CHUNK_CAPACITY;
        dq->back_chunk -= 1;
    }

    dq->back -= 1;
    dq->length -= 1;
    return popped;
}

void* dequeue_pop_front(dequeue *dq) {
    if (dequeue_is_empty(dq)) return NULL;

    void *popped = dequeue_at(dq, 0);

    // if the current front chunk is empty after the pop, update
    // indexes to point to the first element of the next chunk
    dq->front += 1;
    if (dq->front >= CHUNK_CAPACITY) {
        dq->front = 0;
        dq->front_chunk += 1;
    }

    dq->length -= 1;
    return popped;
}
