#include "benchmark.h"

int main() {
    print_benchmark_header();

    // benchmark deque module
    print_benchmark("deque_push_back", bc_deque_push_back, bcc_deque_push_back);
    print_benchmark("deque_push_front", bc_deque_push_front, bcc_deque_push_front);
    print_benchmark("deque_pop_back", bc_deque_push_pop_back, bcc_deque_push_pop_back);
    print_benchmark("deque_pop_front", bc_deque_push_pop_front, bcc_deque_push_pop_front);
    print_benchmark("deque_at", bc_deque_push_at, bcc_deque_push_at);
    print_benchmark("deque_clear", bc_deque_push_clear, bcc_deque_push_clear);

    // benchmark list module
    print_benchmark("list_push_back", bc_list_push_back, bcc_list_push_back);
    print_benchmark("list_push_front", bc_list_push_front, bcc_list_push_front);
    print_benchmark("list_pop_back", bc_list_push_pop_back, bcc_list_push_pop_back);
    print_benchmark("list_pop_front", bc_list_push_pop_front, bcc_list_push_pop_front);
    print_benchmark("list_insert", bc_list_insert, bcc_list_insert);
    print_benchmark("list_erase", bc_list_insert_erase, bcc_list_insert_erase);

    // benchmark pair module
    print_benchmark("pair_first", bc_pair_first, bcc_pair_first);
    print_benchmark("pair_second", bc_pair_second, bcc_pair_second);
    print_benchmark("pair_set_first", bc_pair_set_first, bcc_pair_set_first);
    print_benchmark("pair_set_second", bc_pair_set_second, bcc_pair_set_second);

    // benchmark vector module
    print_benchmark("vector_push", bc_vector_push, bcc_vector_push);
    print_benchmark("vector_pop", bc_vector_push_pop, bcc_vector_push_pop);
    print_benchmark("vector_set", bc_vector_push_set, bcc_vector_push_set);
    print_benchmark("vector_resize", bc_vector_push_resize, bcc_vector_push_resize);
    print_benchmark("vector_insert", bc_vector_insert, bcc_vector_insert);
    print_benchmark("vector_insert_erase", bc_vector_insert_erase, bcc_vector_insert_erase);
    print_benchmark("vector_at", bc_vector_push_at, bcc_vector_push_at);
    print_benchmark("vector_clear", bc_vector_push_clear, bcc_vector_push_clear);
}
