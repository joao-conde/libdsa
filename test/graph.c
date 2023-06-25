#include <assert.h>
#include <math.h>
#include <stdint.h>

#include "test.h"

#include "../include/graph.h"

void test_graph_init() {
    graph *g = graph_init(10);
    assert(graph_size(g) == 10);
    graph_free(g);
}

void test_graph_init_fail() {
    graph *g = graph_init(SIZE_MAX / 1000);
    assert(g == NULL);
}

void test_graph_free() {
    graph_free(NULL);

    graph *g = graph_init(10);
    graph_free(g);
}

void test_graph_size() {
    graph *g = graph_init(10);
    assert(graph_size(g) == 10);
    graph_free(g);

    g = graph_init(100);
    assert(graph_size(g) == 100);
    graph_free(g);
}

void test_graph_cost() {
    graph *g = graph_init(2);

    assert(graph_cost(g, 0, 0) == 0);
    assert(graph_cost(g, 0, 1) == INFINITY);
    assert(graph_cost(g, 1, 0) == INFINITY);
    assert(graph_cost(g, 1, 1) == 0);

    graph_free(g);
}

void test_graph_add() {
    graph *g = graph_init(2);

    assert(graph_cost(g, 0, 0) == 0);
    assert(graph_cost(g, 0, 1) == INFINITY);
    assert(graph_cost(g, 1, 0) == INFINITY);
    assert(graph_cost(g, 1, 1) == 0);

    graph_add(g, 0, 1, 1.5);
    assert(graph_cost(g, 0, 0) == 0);
    assert(graph_cost(g, 0, 1) == 1.5);
    assert(graph_cost(g, 1, 0) == INFINITY);
    assert(graph_cost(g, 1, 1) == 0);

    graph_free(g);
}

void test_graph_remove() {
    graph *g = graph_init(2);

    graph_add(g, 0, 1, 1.5);
    graph_add(g, 1, 0, 1.5);
    assert(graph_cost(g, 0, 0) == 0);
    assert(graph_cost(g, 0, 1) == 1.5);
    assert(graph_cost(g, 1, 0) == 1.5);
    assert(graph_cost(g, 1, 1) == 0);

    graph_remove(g, 0, 1);
    assert(graph_cost(g, 0, 0) == 0);
    assert(graph_cost(g, 0, 1) == INFINITY);
    assert(graph_cost(g, 1, 0) == 1.5);
    assert(graph_cost(g, 1, 1) == 0);

    graph_free(g);
}

void test_graph_dijkstra() {
    graph *g = graph_init(7);

    graph_add(g, 0, 1, 2);
    graph_add(g, 0, 2, 6);

    graph_add(g, 1, 0, 2);
    graph_add(g, 1, 3, 5);

    graph_add(g, 2, 1, 6);
    graph_add(g, 2, 3, 8);

    graph_add(g, 3, 1, 5);
    graph_add(g, 3, 2, 8);
    graph_add(g, 3, 4, 10);
    graph_add(g, 3, 5, 15);

    graph_add(g, 4, 3, 10);
    graph_add(g, 4, 5, 6);
    graph_add(g, 4, 6, 2);

    graph_add(g, 5, 3, 15);
    graph_add(g, 5, 4, 6);
    graph_add(g, 5, 6, 6);

    graph_add(g, 6, 4, 2);
    graph_add(g, 6, 5, 6);

    assert(graph_dijkstra(g, 0, 0) == 0);
    assert(graph_dijkstra(g, 0, 1) == 2); 
    assert(graph_dijkstra(g, 0, 2) == 6); 
    assert(graph_dijkstra(g, 0, 3) == 7); 
    assert(graph_dijkstra(g, 0, 4) == 17); 
    assert(graph_dijkstra(g, 0, 5) == 22); 
    assert(graph_dijkstra(g, 0, 6) == 19); 

    graph_free(g);
}

void test_graph_load() {

}

void test_graph() {
    test_graph_init();
    test_graph_init_fail();
    test_graph_free();
    test_graph_size();
    test_graph_cost();
    test_graph_add();
    test_graph_remove();
    test_graph_dijkstra();
    test_graph_load();
}
