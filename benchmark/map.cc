#include <unordered_map>

#include "benchmark.h"

void* cc_map_init() {
    std::unordered_map<size_t, std::string> *m = new std::unordered_map<size_t, std::string>();
    for (size_t i = 0; i < LOAD; i++) {
        m->insert({i, "value"});
    }
    return m;
}

void cc_map_free(void *data) {
    delete ((std::unordered_map<size_t, std::string>*) data);
}

void cc_map_insert(void *data) {
    std::unordered_map<size_t, std::string> *m = (std::unordered_map<size_t, std::string>*) data;
    for (size_t i = LOAD; i < 2 * LOAD; i++) {
        m->insert({i, "value"});
    }
}

void cc_map_erase(void *data) {
    std::unordered_map<size_t, std::string> *m = (std::unordered_map<size_t, std::string>*) data;
    for (size_t i = 0; i < LOAD; i++) {
        m->erase(i);
    }
}

void cc_map_get(void *data) {
    std::unordered_map<size_t, std::string> *m = (std::unordered_map<size_t, std::string>*) data;
    for (size_t i = 0; i < LOAD; i++) {
        std::string x = m->at(i);
    }
}

void cc_map_clear(void *data) {
    std::unordered_map<size_t, std::string> *m = (std::unordered_map<size_t, std::string>*) data;
    m->clear();
}

void cc_map_rehash(void *data) {
    std::unordered_map<size_t, std::string> *m = (std::unordered_map<size_t, std::string>*) data;
    m->rehash(1);
}
