#include <unordered_map>

#include "benchmark.h"

void* bcc_map_init() {
    std::unordered_map<size_t, std::string> *m = new std::unordered_map<size_t, std::string>();
    for (size_t i = 0; i < MAP_LOAD; i++) {
        m->insert({i, "value"});
    }
    return m;
}

void bcc_map_free(void *data) {
    delete ((std::unordered_map<size_t, std::string>*) data);
}

void bcc_map_insert(void *data) {
    std::unordered_map<size_t, std::string> *m = (std::unordered_map<size_t, std::string>*) data;
    for (size_t i = MAP_LOAD; i < 2 * MAP_LOAD; i++) {
        m->insert({i, "value"});
    }
}

void bcc_map_erase(void *data) {
    std::unordered_map<size_t, std::string> *m = (std::unordered_map<size_t, std::string>*) data;
    for (size_t i = 0; i < MAP_LOAD; i++) {
        m->erase(i);
    }
}

void bcc_map_get(void *data) {
    std::unordered_map<size_t, std::string> *m = (std::unordered_map<size_t, std::string>*) data;
    for (size_t i = 0; i < MAP_LOAD; i++) {
        std::string x = m->at(i);
    }
}

void bcc_map_clear(void *data) {
    std::unordered_map<size_t, std::string> *m = (std::unordered_map<size_t, std::string>*) data;
    m->clear();
}

void bcc_map_rehash(void *data) {
    std::unordered_map<size_t, std::string> *m = (std::unordered_map<size_t, std::string>*) data;
    m->rehash(1);
}
