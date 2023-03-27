#include <list>

#include "benchmark.h"

void bcc_list_push_back() {
    std::list<size_t> l;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        l.push_back(i);
    }
}

void bcc_list_push_front() {
    std::list<size_t> l;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        l.push_front(i);
    }
}

void bcc_list_push_pop_back() {
    std::list<size_t> l;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        l.push_back(i);
    }
    for (size_t i = 0; i < LIST_LOAD; i++) {
        l.pop_back();
    }
}

void bcc_list_push_pop_front() {
    std::list<size_t> l;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        l.push_front(i);
    }
    for (size_t i = 0; i < LIST_LOAD; i++) {
        l.pop_front();
    }
}

void bcc_list_insert() {
    std::list<size_t> l;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        l.insert(l.begin(), i);
    }
}

void bcc_list_insert_erase() {
    std::list<size_t> l;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        l.insert(l.begin(), i);
    }
    for (size_t i = 0; i < LIST_LOAD; i++) {
        l.erase(l.begin());
    }
}

void bcc_list_push_clear() {
    std::list<size_t> l;
    for (size_t i = 0; i < LIST_LOAD; i++) {
        l.push_back(i);
    }
    l.clear();
}
