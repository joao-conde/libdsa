#include "benchmark.h"

void* c_heap_init() {
    heap *h = heap_init(sizeof(size_t));
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        heap_push(h, &i);
    }
    return h;
}

void c_heap_free(void *data) {
    heap_free((heap*) data);
}

void c_heap_max(void *data) {
    heap *h = (heap*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        size_t *max = (size_t*) heap_max(h);
    }
}

void c_heap_push(void *data) {
    heap *h = (heap*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        heap_push(h, &i);
    }
}

void c_heap_pop(void *data) {
    heap *h = (heap*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        heap_pop(h);
    }
}

void c_heap_clear(void *data) {
    heap *h = (heap*) data;
    heap_clear(h);
}
