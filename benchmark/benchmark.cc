#include <chrono>
#include <iomanip>

#include "benchmark.h"

int64_t benchmark(void* (init_fn)(), void (free_fn)(void*), void (fn)(void*)) {
    // sets up necessary test data for the function being benchmarked
    void *data = init_fn();

    // runs the function being benchmarked recording starting and ending times
    auto start = std::chrono::high_resolution_clock::now();
    fn(data);
    auto end = std::chrono::high_resolution_clock::now();

    // cleans up test data
    free_fn(data);

    // converts the duration to milliseconds and returns it
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    int64_t milliseconds = duration.count();
    return milliseconds;
}

void print_benchmark_header() {
    std::cout << std::right << std::setw(TABLE_WIDTH) << "benchmark" << TABLE_SEPARATOR;
    std::cout << std::right << std::setw(TABLE_WIDTH) << "c (ms)" << TABLE_SEPARATOR;
    std::cout << std::right << std::setw(TABLE_WIDTH) << "cc (ms)" << TABLE_SEPARATOR;
    std::cout << std::right << std::setw(TABLE_WIDTH) << "diff (ms)";
    std::cout << std::endl;
}

void print_benchmark(
    std::string name,
    void* (c_init)(),
    void (c_free)(void*),
    void (c_fn)(void*),
    void* (cc_init)(),
    void (cc_free)(void*),
    void (cc_fn)(void*)) {
    // time the execution of the C version with libdsa and the C++ STL one
    // and compute the difference in execution time
    int64_t c = benchmark(c_init, c_free, c_fn);
    int64_t cc = benchmark(cc_init, cc_free, cc_fn);
    int64_t diff = cc - c;

    // print benchmark information and final results
    std::cout << std::right << std::setw(TABLE_WIDTH) << name << TABLE_SEPARATOR;
    std::cout << std::right << std::setw(TABLE_WIDTH) << std::to_string(c) << TABLE_SEPARATOR;
    std::cout << std::right << std::setw(TABLE_WIDTH) << std::to_string(cc) << TABLE_SEPARATOR;
    std::cout << std::right << std::setw(TABLE_WIDTH) << std::to_string(diff) << endl;
}
