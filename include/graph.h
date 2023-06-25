#ifndef INCLUDE_GRAPH_H_
#define INCLUDE_GRAPH_H_

#include <stdlib.h>

typedef struct graph graph;

graph* graph_init(size_t size);

void graph_free(graph *g);

size_t graph_size(const graph *g);

long double graph_cost(const graph *g, size_t src, size_t dst);

void graph_add(graph *g, size_t src, size_t dst, long double cost);

void graph_remove(graph *g, size_t src, size_t dst);

long double graph_dijkstra(const graph *g, size_t src, size_t dst);

#endif // INCLUDE_GRAPH_H_
