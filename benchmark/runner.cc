#include "benchmark.h"

int main() {
    print_benchmark_header();

    // benchmark deque module
    print_benchmark(
        "deque_push_back",
        bc_deque_init,
        bc_deque_free,
        bc_deque_push_back,
        bcc_deque_init,
        bcc_deque_free,
        bcc_deque_push_back);

    print_benchmark(
        "deque_push_front",
        bc_deque_init,
        bc_deque_free,
        bc_deque_push_front,
        bcc_deque_init,
        bcc_deque_free,
        bcc_deque_push_front);

    print_benchmark(
        "deque_pop_back",
        bc_deque_init,
        bc_deque_free,
        bc_deque_pop_back,
        bcc_deque_init,
        bcc_deque_free,
        bcc_deque_pop_back);

    print_benchmark(
        "deque_pop_front",
        bc_deque_init,
        bc_deque_free,
        bc_deque_pop_front,
        bcc_deque_init,
        bcc_deque_free,
        bcc_deque_pop_front);

    print_benchmark(
        "deque_at",
        bc_deque_init,
        bc_deque_free,
        bc_deque_at,
        bcc_deque_init,
        bcc_deque_free,
        bcc_deque_at);

    print_benchmark(
        "deque_clear",
        bc_deque_init,
        bc_deque_free,
        bc_deque_clear,
        bcc_deque_init,
        bcc_deque_free,
        bcc_deque_clear);

    // benchmark list module
    print_benchmark(
        "list_push_back",
        bc_list_init,
        bc_list_free,
        bc_list_push_back,
        bcc_list_init,
        bcc_list_free,
        bcc_list_push_back);

    print_benchmark(
        "list_push_front",
        bc_list_init,
        bc_list_free,
        bc_list_push_front,
        bcc_list_init,
        bcc_list_free,
        bcc_list_push_front);

    print_benchmark(
        "list_pop_back",
        bc_list_init,
        bc_list_free,
        bc_list_pop_back,
        bcc_list_init,
        bcc_list_free,
        bcc_list_pop_back);

    print_benchmark(
        "list_pop_front",
        bc_list_init,
        bc_list_free,
        bc_list_pop_front,
        bcc_list_init,
        bcc_list_free,
        bcc_list_pop_front);

    print_benchmark(
        "list_insert",
        bc_list_init,
        bc_list_free,
        bc_list_insert,
        bcc_list_init,
        bcc_list_free,
        bcc_list_insert);

    print_benchmark(
        "list_erase",
        bc_list_init,
        bc_list_free,
        bc_list_erase,
        bcc_list_init,
        bcc_list_free,
        bcc_list_erase);

    print_benchmark(
        "list_clear",
        bc_list_init,
        bc_list_free,
        bc_list_clear,
        bcc_list_init,
        bcc_list_free,
        bcc_list_clear);

    // benchmark map module
    print_benchmark(
        "map_insert",
        bc_map_init,
        bc_map_free,
        bc_map_insert,
        bcc_map_init,
        bcc_map_free,
        bcc_map_insert);

    print_benchmark(
        "map_erase",
        bc_map_init,
        bc_map_free,
        bc_map_erase,
        bcc_map_init,
        bcc_map_free,
        bcc_map_erase);

    print_benchmark(
        "map_get",
        bc_map_init,
        bc_map_free,
        bc_map_get,
        bcc_map_init,
        bcc_map_free,
        bcc_map_get);

    print_benchmark(
        "map_clear",
        bc_map_init,
        bc_map_free,
        bc_map_clear,
        bcc_map_init,
        bcc_map_free,
        bcc_map_clear);

    print_benchmark(
        "map_rehash",
        bc_map_init,
        bc_map_free,
        bc_map_rehash,
        bcc_map_init,
        bcc_map_free,
        bcc_map_rehash);

    // benchmark pair module
    print_benchmark(
        "pair_first",
        bc_pair_init,
        bc_pair_free,
        bc_pair_first,
        bcc_pair_init,
        bcc_pair_free,
        bcc_pair_first);

    print_benchmark(
        "pair_second",
        bc_pair_init,
        bc_pair_free,
        bc_pair_second,
        bcc_pair_init,
        bcc_pair_free,
        bcc_pair_second);

    print_benchmark(
        "pair_set_first",
        bc_pair_init,
        bc_pair_free,
        bc_pair_set_first,
        bcc_pair_init,
        bcc_pair_free,
        bcc_pair_set_first);

    print_benchmark(
        "pair_set_second",
        bc_pair_init,
        bc_pair_free,
        bc_pair_set_second,
        bcc_pair_init,
        bcc_pair_free,
        bcc_pair_set_second);

    // benchmark queue module
    print_benchmark(
        "queue_push",
        bc_queue_init,
        bc_queue_free,
        bc_queue_push,
        bcc_queue_init,
        bcc_queue_free,
        bcc_queue_push);

    print_benchmark(
        "queue_pop",
        bc_queue_init,
        bc_queue_free,
        bc_queue_pop,
        bcc_queue_init,
        bcc_queue_free,
        bcc_queue_pop);

    print_benchmark(
        "queue_clear",
        bc_queue_init,
        bc_queue_free,
        bc_queue_clear,
        bcc_queue_init,
        bcc_queue_free,
        bcc_queue_clear);

    // benchmark stack module
    print_benchmark(
        "stack_push",
        bc_stack_init,
        bc_stack_free,
        bc_stack_push,
        bcc_stack_init,
        bcc_stack_free,
        bcc_stack_push);

    print_benchmark(
        "stack_pop",
        bc_stack_init,
        bc_stack_free,
        bc_stack_pop,
        bcc_stack_init,
        bcc_stack_free,
        bcc_stack_pop);

    // benchmark vector module
    print_benchmark(
        "vector_push",
        bc_vector_init,
        bc_vector_free,
        bc_vector_push,
        bcc_vector_init,
        bcc_vector_free,
        bcc_vector_push);

    print_benchmark(
        "vector_pop",
        bc_vector_init,
        bc_vector_free,
        bc_vector_pop,
        bcc_vector_init,
        bcc_vector_free,
        bcc_vector_pop);

    print_benchmark(
        "vector_set",
        bc_vector_init,
        bc_vector_free,
        bc_vector_set,
        bcc_vector_init,
        bcc_vector_free,
        bcc_vector_set);

    print_benchmark(
        "vector_resize",
        bc_vector_init,
        bc_vector_free,
        bc_vector_resize,
        bcc_vector_init,
        bcc_vector_free,
        bcc_vector_resize);

    print_benchmark(
        "vector_insert",
        bc_vector_init,
        bc_vector_free,
        bc_vector_insert,
        bcc_vector_init,
        bcc_vector_free,
        bcc_vector_insert);

    print_benchmark(
        "vector_erase",
        bc_vector_init,
        bc_vector_free,
        bc_vector_erase,
        bcc_vector_init,
        bcc_vector_free,
        bcc_vector_erase);

    print_benchmark(
        "vector_at",
        bc_vector_init,
        bc_vector_free,
        bc_vector_at,
        bcc_vector_init,
        bcc_vector_free,
        bcc_vector_at);

    print_benchmark(
        "vector_clear",
        bc_vector_init,
        bc_vector_free,
        bc_vector_clear,
        bcc_vector_init,
        bcc_vector_free,
        bcc_vector_clear);
}
