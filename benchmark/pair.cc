#include "benchmark.h"

void* cc_pair_init() {
    std::pair<std::string, std::string> *p = new std::pair<std::string, std::string>();
    p->first = "first";
    p->second = "second";
    return p;
}

void cc_pair_free(void *data) {
    delete ((std::pair<std::string, std::string>*) data);
}

void cc_pair_first(void *data) {
    std::pair<std::string, std::string> *p = (std::pair<std::string, std::string>*) data;
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        std::string first = p->first;
    }
}

void cc_pair_second(void *data) {
    std::pair<std::string, std::string> *p = (std::pair<std::string, std::string>*) data;
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        std::string second = p->second;
    }
}

void cc_pair_set_first(void *data) {
    std::pair<std::string, std::string> *p = (std::pair<std::string, std::string>*) data;
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        p->first = "key";
    }
}

void cc_pair_set_second(void *data) {
    std::pair<std::string, std::string> *p = (std::pair<std::string, std::string>*) data;
    for (size_t i = 0; i < PAIR_LOAD; i++) {
        p->second = "value";
    }
}
