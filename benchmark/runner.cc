#include <chrono>
#include <iostream>

#include "benchmark.h"

void print_benchmark(std::string name, void (fn)()) {
    auto start = std::chrono::high_resolution_clock::now();
    fn();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto milliseconds = duration.count();
    std::cout << name << " " << milliseconds << "ms" << std::endl;
}

int main() {
    print_benchmark("[C (libdsa)] vector_push", bench_cc_vector_push);
    print_benchmark("[C++  (STL)] vector_push_back", bench_c_vector_push);
}
