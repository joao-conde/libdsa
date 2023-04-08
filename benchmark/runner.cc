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

    // // benchmark map module
    // print_benchmark("map_insert", bc_map_insert, bcc_map_insert);
    // print_benchmark("map_erase", bc_map_insert_erase, bcc_map_insert_erase);
    // print_benchmark("map_get", bc_map_insert_get, bcc_map_insert_get);
    // print_benchmark("map_clear", bc_map_insert_clear, bcc_map_insert_clear);
    // print_benchmark("map_rehash", bc_map_insert_rehash, bcc_map_insert_rehash);

    // // benchmark pair module
    // print_benchmark("pair_first", bc_pair_first, bcc_pair_first);
    // print_benchmark("pair_second", bc_pair_second, bcc_pair_second);
    // print_benchmark("pair_set_first", bc_pair_set_first, bcc_pair_set_first);
    // print_benchmark("pair_set_second", bc_pair_set_second, bcc_pair_set_second);

    // // benchmark queue module
    // print_benchmark("queue_push", bc_queue_push, bcc_queue_push);
    // print_benchmark("queue_pop", bc_queue_push_pop, bcc_queue_push_pop);
    // print_benchmark("queue_clear", bc_queue_push_clear, bcc_queue_push_clear);

    // // benchmark stack module
    // print_benchmark("stack_push", bc_stack_push, bcc_stack_push);
    // print_benchmark("stack_pop", bc_stack_push_pop, bcc_stack_push_pop);

    // // benchmark vector module
    // print_benchmark("vector_push", bc_vector_push, bcc_vector_push);
    // print_benchmark("vector_pop", bc_vector_push_pop, bcc_vector_push_pop);
    // print_benchmark("vector_set", bc_vector_push_set, bcc_vector_push_set);
    // print_benchmark("vector_resize", bc_vector_push_resize, bcc_vector_push_resize);
    // print_benchmark("vector_insert", bc_vector_insert, bcc_vector_insert);
    // print_benchmark("vector_insert_erase", bc_vector_insert_erase, bcc_vector_insert_erase);
    // print_benchmark("vector_at", bc_vector_push_at, bcc_vector_push_at);
    // print_benchmark("vector_clear", bc_vector_push_clear, bcc_vector_push_clear);
}
