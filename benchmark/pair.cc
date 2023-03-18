#include "benchmark.h"

void bcc_pair_first() {
    std::pair<std::string, std::string> p("first", "second");
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        std::string first = p.first;
    }
}

void bcc_pair_second() {
    std::pair<std::string, std::string> p("first", "second");
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        std::string second = p.second;
    }
}

void bcc_pair_set_first() {
    std::pair<std::string, std::string> p("first", "second");
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        p.first = "key";
    }
}

void bcc_pair_set_second() {
    std::pair<std::string, std::string> p("first", "second");
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        p.second = "value";
    }
}
