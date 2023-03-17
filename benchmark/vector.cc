#include <vector>

#include "benchmark.h"

void bench_cc_vector_push() {
    std::vector<int> v;
    for (std::size_t i = 0; i < ITER_VECTOR_PUSH; i++) {
        v.push_back(i);
    }
}
