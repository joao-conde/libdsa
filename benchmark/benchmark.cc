#include <chrono>
#include <iomanip>

#include "benchmark.h"

int64_t benchmark(void (fn)()) {
    auto start = std::chrono::high_resolution_clock::now();
    fn();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    int64_t milliseconds = duration.count();
    return milliseconds;
}

void print_benchmark_header() {
    std::cout << std::right << std::setw(TABLE_WIDTH) << "benchmark,";
    std::cout << std::right << std::setw(TABLE_WIDTH) << "c (libdsa),";
    std::cout << std::right << std::setw(TABLE_WIDTH) << "cc (stl),";
    std::cout << std::right << std::setw(TABLE_WIDTH) << "diff";
    std::cout << std::endl;
}

void print_benchmark(std::string name, void (c_fn)(), void (cc_fn)()) {
    int64_t c = benchmark(c_fn);
    int64_t cc = benchmark(cc_fn);
    int64_t diff = cc - c;

    std::cout << std::right << std::setw(TABLE_WIDTH) << name + ",";
    std::cout << std::right << std::setw(TABLE_WIDTH) << std::to_string(c) + "ms,";
    std::cout << std::right << std::setw(TABLE_WIDTH) << std::to_string(cc) + "ms,";
    std::cout << std::right << std::setw(TABLE_WIDTH) << std::to_string(diff) + "ms";
    std::cout << std::endl;
}
