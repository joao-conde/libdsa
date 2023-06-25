#include <math.h>
#include <stdint.h>

#include "../include/graph.h"

struct graph {
    size_t size;
    long double *matrix;
};

graph* graph_init(size_t size) {
    graph *g = (graph*) malloc(sizeof(graph));
    long double *matrix = (long double*) malloc(sizeof(long double) * size * size);
    if (g == NULL || matrix == NULL) {
        free(matrix);
        free(g);
        return NULL;
    }

    for (size_t r = 0; r < size; r++) {
        for (size_t c = 0; c < size; c++) {
            matrix[r * size + c] = r == c ? 0 : INFINITY;
        }
    }

    g->size = size;
    g->matrix = matrix;
    return g;
}

void graph_free(graph *g) {
    if (g != NULL) free(g->matrix);
    free(g);
}

size_t graph_size(const graph *g) {
    return g->size;
}

long double graph_cost(const graph *g, size_t src, size_t dst) {
    return g->matrix[src * g->size + dst];
}

void graph_add(graph *g, size_t src, size_t dst, long double cost) {
    g->matrix[src * g->size + dst] = cost;
}

void graph_remove(graph *g, size_t src, size_t dst) {
    g->matrix[src * g->size + dst] = INFINITY;
}
