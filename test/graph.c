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

void test_graph() {
    test_graph_init();
    test_graph_init_fail();
    test_graph_free();
    test_graph_size();
    test_graph_cost();
    test_graph_add();
    test_graph_remove();
}
