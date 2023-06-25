#include <math.h>

#include "benchmark.h"

#define GRAPH_SIZE 1000

void* cc_graph_init() {
    long double **g = new long double*[GRAPH_SIZE];
    for (size_t r = 0; r < GRAPH_SIZE; r++) {
        g[r] = new long double[GRAPH_SIZE];
        for (size_t c = 0; c < GRAPH_SIZE; c++) {
            g[r][c] = r == c ? 0 : INFINITY;
        }
    }
    return g;
}

void cc_graph_free(void *data) {
    delete ((long double **) data);
}

void cc_graph_cost(void *data) {
    long double **g = ((long double **) data);
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        long double cost = g[i % GRAPH_SIZE][i % GRAPH_SIZE];
    }
}

void cc_graph_add(void *data) {
    long double **g = ((long double **) data);
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        g[i % GRAPH_SIZE][i % GRAPH_SIZE] = 1.5;
    }
}

void cc_graph_remove(void *data) {
    long double **g = ((long double **) data);
    for (size_t i = 0; i < BENCH_LOAD; i++) {
        g[i % GRAPH_SIZE][i % GRAPH_SIZE] = INFINITY;
    }
}
