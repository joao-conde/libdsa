#include "benchmark.h"

int main() {
    print_benchmark_header();

    // benchmark pair module
    print_benchmark("pair_first", bc_pair_first, bcc_pair_first);
    print_benchmark("pair_second", bc_pair_second, bcc_pair_second);
    print_benchmark("pair_set_first", bc_pair_set_first, bcc_pair_set_first);
    print_benchmark("pair_set_second", bc_pair_set_second, bcc_pair_set_second);

    // benchmark vector module
    print_benchmark("vector_push", bc_vector_push, bcc_vector_push);
    print_benchmark("vector_pop", bc_vector_push_pop, bcc_vector_push_pop);
    print_benchmark("vector_clear", bc_vector_push_clear, bcc_vector_push_clear);
    print_benchmark("vector_at", bc_vector_push_at, bcc_vector_push_at);
    print_benchmark("vector_set", bc_vector_push_set, bcc_vector_push_set);
    print_benchmark("vector_resize", bc_vector_push_resize, bcc_vector_push_resize);
    print_benchmark("vector_insert", bc_vector_insert, bcc_vector_insert);
    print_benchmark("vector_insert_erase", bc_vector_insert_erase, bcc_vector_insert_erase);
}
