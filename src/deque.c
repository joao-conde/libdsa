#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "../include/deque.h"
#include "../include/vector.h"

#define CHUNK_CAPACITY 256

struct deque {
    size_t length;
    size_t type_size;
    size_t front_chunk;
    size_t back_chunk;
    size_t front;
    size_t back;
    vector *chunks;
};

deque* deque_init(size_t type_size) {
    // checks for overflow of amount of requested memory
    if (type_size && CHUNK_CAPACITY > PTRDIFF_MAX / type_size) return NULL;

    deque *dq = malloc(sizeof(deque));
    void *chunks = vector_init(sizeof(void*));
    void *chunk = malloc(CHUNK_CAPACITY * type_size);
    if (dq == NULL || chunks == NULL || chunk == NULL) {
        free(chunk);
        vector_free(chunks);
        free(dq);
        return NULL;
    }

    // saves the first and only chunk pointer for now
    vector_push(chunks, &chunk);

    dq->length = 0;
    dq->type_size = type_size;
    dq->front_chunk = 0;
    dq->back_chunk = 0;
    dq->front = 0;
    dq->back = 0;
    dq->chunks = chunks;
    return dq;
}

void deque_free(deque *dq) {
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

size_t deque_length(const deque *dq) {
    return dq->length;
}

bool deque_is_empty(const deque *dq) {
    return dq->length == 0;
}

void deque_clear(deque *dq) {
    dq->length = 0;
    dq->front_chunk = 0;
    dq->back_chunk = 0;
    dq->front = 0;
    dq->back = 0;
}

void* deque_at(const deque *dq, size_t index) {
    if (index >= dq->length) return NULL;
    size_t i = dq->front_chunk * CHUNK_CAPACITY + dq->front + index;
    size_t chunk_i = i / CHUNK_CAPACITY;
    size_t value_i = i % CHUNK_CAPACITY;
    void *chunk = *(void**)vector_at(dq->chunks, chunk_i);
    void *value = (uint8_t*) chunk + value_i * dq->type_size;
    return value;
}

void* deque_front(const deque *dq) {
    return deque_at(dq, 0);
}

void* deque_back(const deque *dq) {
    if (deque_is_empty(dq)) return deque_front(dq);
    return deque_at(dq, dq->length - 1);
}

void* deque_push_back(deque *dq, const void *value) {
    // if current back chunk is in use, allocate
    // a new one in the back
    if (dq->back_chunk == vector_length(dq->chunks) - 1) {
        void *chunk = malloc(CHUNK_CAPACITY * dq->type_size);
        if (chunk == NULL) return NULL;
        vector_push(dq->chunks, &chunk);
    }

    // if we reached the end of the current back chunk,
    // update back and back chunk indexes accordingly
    if (dq->back == CHUNK_CAPACITY - 1) {
        dq->back_chunk += 1;
        dq->back = 0;
    } else {
        dq->back += deque_is_empty(dq) ? 0 : 1;
    }

    dq->length += 1;
    void *dst = deque_at(dq, dq->length - 1);
    return memcpy(dst, value, dq->type_size);
}

void* deque_push_front(deque *dq, const void *value) {
    // if current front chunk is in use, allocate
    // a new one in the front
    if (dq->front_chunk == 0) {
        void *chunk = malloc(CHUNK_CAPACITY * dq->type_size);
        if (chunk == NULL) return NULL;
        vector_insert(dq->chunks, 0, &chunk);
        dq->front_chunk += 1;
        dq->back_chunk += 1;
    }

    // if we cross our current front chunk, update front
    // and front chunk indexes accordingly
    if (dq->front == 0) {
        dq->front_chunk -= 1;
        dq->front = CHUNK_CAPACITY - 1;
    } else {
        dq->front -= deque_is_empty(dq) ? 0 : 1;
    }

    dq->length += 1;
    void *dst = deque_at(dq, 0);
    return memcpy(dst, value, dq->type_size);
}

void* deque_pop_back(deque *dq) {
    if (deque_is_empty(dq)) return NULL;

    void *popped = deque_at(dq, dq->length - 1);

    // if the current back chunk is empty after the pop, update
    // indexes to point to the last element of the previous chunk
    if (dq->back == 0) {
        dq->back_chunk -= 1;
        dq->back = CHUNK_CAPACITY - 1;
    } else {
        dq->back -= 1;
    }

    dq->length -= 1;
    return popped;
}

void* deque_pop_front(deque *dq) {
    if (deque_is_empty(dq)) return NULL;

    void *popped = deque_at(dq, 0);

    // if the current front chunk is empty after the pop, update
    // indexes to point to the first element of the next chunk
    if (dq->front == CHUNK_CAPACITY - 1) {
        dq->front_chunk += 1;
        dq->front = 0;
    } else {
        dq->front += 1;
    }

    dq->length -= 1;
    return popped;
}
