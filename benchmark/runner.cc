#include "benchmark.h"

int main() {
    print_benchmark_header();
    print_benchmark("vector_push", bc_vector_push, bcc_vector_push);
    print_benchmark("vector_pop", bc_vector_push_pop, bcc_vector_push_pop);
    print_benchmark("vector_clear", bc_vector_push_clear, bcc_vector_push_clear);
    print_benchmark("vector_at", bc_vector_push_at, bcc_vector_push_at);
    print_benchmark("vector_set", bc_vector_push_set, bcc_vector_push_set);
    print_benchmark("vector_resize", bc_vector_push_resize, bcc_vector_push_resize);
    print_benchmark("vector_insert", bc_vector_insert, bcc_vector_insert);
    print_benchmark("vector_insert_erase", bc_vector_insert_erase, bcc_vector_insert_erase);
}
