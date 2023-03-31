#include <unordered_map>

#include "benchmark.h"

void bcc_map_insert() {
    std::unordered_map<size_t, std::string> m;
    for (size_t i = 0; i < MAP_LOAD; i++) {
        m.insert({i, "value"});
    }
}

void bcc_map_insert_erase() {
    std::unordered_map<size_t, std::string> m;
    for (size_t i = 0; i < MAP_LOAD; i++) {
        m.insert({i, "value"});
    }
    for (size_t i = 0; i < MAP_LOAD; i++) {
        m.erase(i);
    }
}

void bcc_map_insert_get() {
    std::unordered_map<size_t, std::string> m;
    for (size_t i = 0; i < MAP_LOAD; i++) {
        m.insert({i, "value"});
        std::string x = m[i];
    }
}

void bcc_map_insert_clear() {
    std::unordered_map<size_t, std::string> m;
    for (size_t i = 0; i < MAP_LOAD; i++) {
        m.insert({i, "value"});
    }
    m.clear();
}

void bcc_map_insert_rehash() {
    std::unordered_map<size_t, std::string> m;
    for (size_t i = 0; i < MAP_LOAD; i++) {
        m.insert({i, "value"});
    }
    m.rehash(1);
}
