#include <chrono>
#include <iostream>

#include "benchmark.h"

using namespace std;

void print_benchmark(string name, void (fn)()) {
    auto start = chrono::high_resolution_clock::now();
    fn();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << name << " " << duration << "ms" << endl; 
}

int main() {
    print_benchmark("[C (libdsa)] vector_push", bench_cc_vector_push);
    print_benchmark("[C++  (STL)] vector_push_back", bench_c_vector_push);
}