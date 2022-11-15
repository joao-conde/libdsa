#include <stdint.h>
#include <string.h>

#include "../../include/vector.h"

#define CAPACITY 256
#define ALLOC_FACTOR 2

struct vector {
    unsigned int length;
    unsigned int capacity;
    size_t type_size;
    void *data;
};

vector* vec(size_t type_size) {
    vector *v = malloc(sizeof(vector));
    void *data = malloc(type_size * CAPACITY);
    if (v == NULL || data == NULL) {
        free(data);
        free(v);
        return NULL;
    }

    v->length = 0;
    v->capacity = CAPACITY;
    v->type_size = type_size;
    v->data = data;
    return v;
}

vector* vec_with_capacity(size_t type_size, unsigned int capacity) {
    vector *v = malloc(sizeof(vector));
    void *data = malloc(type_size * capacity);
    if (v == NULL || data == NULL) {
        free(data);
        free(v);
        return NULL;
    }

    v->length = 0;
    v->capacity = capacity;
    v->type_size = type_size;
    v->data = data;
    return v;
}

vector* vec_from_array(size_t type_size, unsigned int length, const void *array) {
    unsigned int capacity = CAPACITY > length ? CAPACITY : length * ALLOC_FACTOR;

    vector *v = malloc(sizeof(vector));
    void *data = malloc(type_size * capacity);
    if (v == NULL || data == NULL) {
        free(data);
        free(v);
        return NULL;
    }

    memcpy(data, array, length * type_size);

    v->length = length;
    v->capacity = capacity;
    v->type_size = type_size;
    v->data = data;
    return v;
}

void vec_free(vector *v) {
    free(v->data);
    free(v);
}

unsigned int vec_length(const vector *v) {
    return v->length;
}

unsigned int vec_capacity(const vector *v) {
    return v->capacity;
}

bool vec_empty(const vector *v) {
    return v->length == 0;
}

void* vec_begin(const vector *v) {
    return v->data;
}

void* vec_end(const vector *v) {
    return (uint8_t*) v->data + v->length * v->type_size;
}

void* vec_at(const vector *v, unsigned int index) {
    if (index >= v->length) return NULL;
    return (uint8_t*) v->data + index * v->type_size;
}

void* vec_push(vector *v, void *value) {
    if (v->length >= v->capacity) {
        void *result = vec_resize(v, v->capacity * ALLOC_FACTOR);
        if (result == NULL) return NULL;
    }

    uint8_t *dest = (uint8_t*) v->data + v->length * v->type_size;
    v->length += 1;
    return memcpy(dest, value, v->type_size);
}

void* vec_pop(vector *v) {
    if (v->length == 0) return NULL;
    void *popped = (uint8_t*) v->data + (v->length - 1) * v->type_size;
    v->length -= 1;
    return popped;
}

void* vec_insert(vector *v, unsigned int index, void *value) {
    if (index > v->length) return NULL;
    if (v->length >= v->capacity) {
        void *result = vec_resize(v, v->capacity * ALLOC_FACTOR);
        if (result == NULL) return NULL;
    }
    void *pos = (uint8_t*) v->data + index * v->type_size;
    unsigned int to_copy = v->length - index;
    memmove(pos + v->type_size, pos, to_copy * v->type_size);
    v->length += 1;
    return memcpy(pos, value, v->type_size);
}

void* vec_erase(vector *v, unsigned int index) {
    if (index > v->length) return NULL;
    void *pos = (uint8_t*) v->data + index * v->type_size;
    unsigned int to_copy = v->length - index;
    v->length -= 1;
    return memmove(pos, pos + v->type_size, to_copy * v->type_size);
}

void* vec_resize(vector *v, unsigned int capacity) {
    void *data = realloc(v->data, v->type_size * capacity);
    if (data != NULL) v->data = data;

    v->length = v->length > capacity ? capacity : v->length;
    v->capacity = capacity;
    return data;
}
