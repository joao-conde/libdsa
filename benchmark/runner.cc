#include "benchmark.h"

int main() {
    print_benchmark_header();

    // benchmark deque module
    print_benchmark(
        "deque_push_back",
        c_deque_init,
        c_deque_free,
        c_deque_push_back,
        cc_deque_init,
        cc_deque_free,
        cc_deque_push_back);

    print_benchmark(
        "deque_push_front",
        c_deque_init,
        c_deque_free,
        c_deque_push_front,
        cc_deque_init,
        cc_deque_free,
        cc_deque_push_front);

    print_benchmark(
        "deque_pop_back",
        c_deque_init,
        c_deque_free,
        c_deque_pop_back,
        cc_deque_init,
        cc_deque_free,
        cc_deque_pop_back);

    print_benchmark(
        "deque_pop_front",
        c_deque_init,
        c_deque_free,
        c_deque_pop_front,
        cc_deque_init,
        cc_deque_free,
        cc_deque_pop_front);

    print_benchmark(
        "deque_at",
        c_deque_init,
        c_deque_free,
        c_deque_at,
        cc_deque_init,
        cc_deque_free,
        cc_deque_at);

    print_benchmark(
        "deque_clear",
        c_deque_init,
        c_deque_free,
        c_deque_clear,
        cc_deque_init,
        cc_deque_free,
        cc_deque_clear);

    // benchmark list module
    print_benchmark(
        "list_push_back",
        c_list_init,
        c_list_free,
        c_list_push_back,
        cc_list_init,
        cc_list_free,
        cc_list_push_back);

    print_benchmark(
        "list_push_front",
        c_list_init,
        c_list_free,
        c_list_push_front,
        cc_list_init,
        cc_list_free,
        cc_list_push_front);

    print_benchmark(
        "list_pop_back",
        c_list_init,
        c_list_free,
        c_list_pop_back,
        cc_list_init,
        cc_list_free,
        cc_list_pop_back);

    print_benchmark(
        "list_pop_front",
        c_list_init,
        c_list_free,
        c_list_pop_front,
        cc_list_init,
        cc_list_free,
        cc_list_pop_front);

    print_benchmark(
        "list_insert",
        c_list_init,
        c_list_free,
        c_list_insert,
        cc_list_init,
        cc_list_free,
        cc_list_insert);

    print_benchmark(
        "list_erase",
        c_list_init,
        c_list_free,
        c_list_erase,
        cc_list_init,
        cc_list_free,
        cc_list_erase);

    print_benchmark(
        "list_clear",
        c_list_init,
        c_list_free,
        c_list_clear,
        cc_list_init,
        cc_list_free,
        cc_list_clear);

    // benchmark map module
    print_benchmark(
        "map_insert",
        c_map_init,
        c_map_free,
        c_map_insert,
        cc_map_init,
        cc_map_free,
        cc_map_insert);

    print_benchmark(
        "map_erase",
        c_map_init,
        c_map_free,
        c_map_erase,
        cc_map_init,
        cc_map_free,
        cc_map_erase);

    print_benchmark(
        "map_get",
        c_map_init,
        c_map_free,
        c_map_get,
        cc_map_init,
        cc_map_free,
        cc_map_get);

    print_benchmark(
        "map_clear",
        c_map_init,
        c_map_free,
        c_map_clear,
        cc_map_init,
        cc_map_free,
        cc_map_clear);

    print_benchmark(
        "map_rehash",
        c_map_init,
        c_map_free,
        c_map_rehash,
        cc_map_init,
        cc_map_free,
        cc_map_rehash);

    // benchmark pair module
    print_benchmark(
        "pair_first",
        c_pair_init,
        c_pair_free,
        c_pair_first,
        cc_pair_init,
        cc_pair_free,
        cc_pair_first);

    print_benchmark(
        "pair_second",
        c_pair_init,
        c_pair_free,
        c_pair_second,
        cc_pair_init,
        cc_pair_free,
        cc_pair_second);

    print_benchmark(
        "pair_set_first",
        c_pair_init,
        c_pair_free,
        c_pair_set_first,
        cc_pair_init,
        cc_pair_free,
        cc_pair_set_first);

    print_benchmark(
        "pair_set_second",
        c_pair_init,
        c_pair_free,
        c_pair_set_second,
        cc_pair_init,
        cc_pair_free,
        cc_pair_set_second);

    // benchmark queue module
    print_benchmark(
        "queue_push",
        c_queue_init,
        c_queue_free,
        c_queue_push,
        cc_queue_init,
        cc_queue_free,
        cc_queue_push);

    print_benchmark(
        "queue_pop",
        c_queue_init,
        c_queue_free,
        c_queue_pop,
        cc_queue_init,
        cc_queue_free,
        cc_queue_pop);

    print_benchmark(
        "queue_clear",
        c_queue_init,
        c_queue_free,
        c_queue_clear,
        cc_queue_init,
        cc_queue_free,
        cc_queue_clear);

    // benchmark set module
    print_benchmark(
        "set_insert",
        c_set_init,
        c_set_free,
        c_set_insert,
        cc_set_init,
        cc_set_free,
        cc_set_insert);

    print_benchmark(
        "set_erase",
        c_set_init,
        c_set_free,
        c_set_erase,
        cc_set_init,
        cc_set_free,
        cc_set_erase);

    print_benchmark(
        "set_has",
        c_set_init,
        c_set_free,
        c_set_has,
        cc_set_init,
        cc_set_free,
        cc_set_has);

    print_benchmark(
        "set_clear",
        c_set_init,
        c_set_free,
        c_set_clear,
        cc_set_init,
        cc_set_free,
        cc_set_clear);

    print_benchmark(
        "set_rehash",
        c_set_init,
        c_set_free,
        c_set_rehash,
        cc_set_init,
        cc_set_free,
        cc_set_rehash);

    // benchmark stack module
    print_benchmark(
        "stack_push",
        c_stack_init,
        c_stack_free,
        c_stack_push,
        cc_stack_init,
        cc_stack_free,
        cc_stack_push);

    print_benchmark(
        "stack_pop",
        c_stack_init,
        c_stack_free,
        c_stack_pop,
        cc_stack_init,
        cc_stack_free,
        cc_stack_pop);

    // benchmark vector module
    print_benchmark(
        "vector_push",
        c_vector_init,
        c_vector_free,
        c_vector_push,
        cc_vector_init,
        cc_vector_free,
        cc_vector_push);

    print_benchmark(
        "vector_pop",
        c_vector_init,
        c_vector_free,
        c_vector_pop,
        cc_vector_init,
        cc_vector_free,
        cc_vector_pop);

    print_benchmark(
        "vector_set",
        c_vector_init,
        c_vector_free,
        c_vector_set,
        cc_vector_init,
        cc_vector_free,
        cc_vector_set);

    print_benchmark(
        "vector_resize",
        c_vector_init,
        c_vector_free,
        c_vector_resize,
        cc_vector_init,
        cc_vector_free,
        cc_vector_resize);

    print_benchmark(
        "vector_insert",
        c_vector_init,
        c_vector_free,
        c_vector_insert,
        cc_vector_init,
        cc_vector_free,
        cc_vector_insert);

    print_benchmark(
        "vector_erase",
        c_vector_init,
        c_vector_free,
        c_vector_erase,
        cc_vector_init,
        cc_vector_free,
        cc_vector_erase);

    print_benchmark(
        "vector_at",
        c_vector_init,
        c_vector_free,
        c_vector_at,
        cc_vector_init,
        cc_vector_free,
        cc_vector_at);

    print_benchmark(
        "vector_clear",
        c_vector_init,
        c_vector_free,
        c_vector_clear,
        cc_vector_init,
        cc_vector_free,
        cc_vector_clear);
}
