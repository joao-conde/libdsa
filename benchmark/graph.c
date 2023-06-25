#include "benchmark.h"

#define GRAPH_SIZE 1000

void* c_graph_init() {
    graph *g = graph_init(GRAPH_SIZE);
    return g;
}

void c_graph_free(void *data) {
    graph_free((graph*) data);
}

void c_graph_cost(void *data) {
    graph *g = (graph*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        long double cost = graph_cost(g, i % GRAPH_SIZE, i % GRAPH_SIZE);
    }
}

void c_graph_add(void *data) {
    graph *g = (graph*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        graph_add(g, i % GRAPH_SIZE, i % GRAPH_SIZE, 1.5);
    }
}

void c_graph_remove(void *data) {
    graph *g = (graph*) data;
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        graph_remove(g, i % GRAPH_SIZE, i % GRAPH_SIZE);
    }
}
