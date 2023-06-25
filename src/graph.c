#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "../include/graph.h"
#include "../include/heap.h"
#include "../include/pair.h"

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

#include <stdio.h>
bool min_heap_fn(const void *a, const void *b) {
    pair *p1 = (pair*) a;
    pair *p2 = (pair*) b;
    return pair_first(p1) >= pair_first(p2);
}

long double graph_dijkstra(const graph *g, size_t src, size_t dst) {
    bool visited[g->size];
    long double distances[g->size];
    for (size_t i = 0; i < g->size; i++) {
        visited[i] = false;
        distances[i] = INFINITY;
    }

    long double cost = 0;
    pair *source = pair_init(&cost, &src, sizeof(long double), sizeof(size_t));

    heap *pq = heap_init(PAIR_SIZE, min_heap_fn);
    heap_push(pq, source);

    while (!heap_empty(pq)) {
        pair *top = (pair*) heap_top(pq);
        heap_pop(pq);

        long double cur_cost = *(long double*) pair_first(top);
        size_t cur_node = *(size_t*) pair_second(top);

        if (visited[cur_node]) {
            continue;
        }
        visited[cur_node] = true;

        for (size_t i = 0; i < g->size; i++) {
            long double alt = distances[cur_node] + cur_cost;
            if (alt < distances[i]) {
                distances[i] = alt;
            }
            heap_push(pq, pair_init(distances + i, &i, sizeof(long double), sizeof(size_t)));
        }
    }

    for (size_t i = 0; i < g->size; i++) printf("%Lf, ", distances[i]);
    printf("\n");

    return distances[dst];
}