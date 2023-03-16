#include <vector>

using namespace std;

int main() {
    int random, nelements = 1000000;
    bool is_empty;
    size_t length, capacity;
    int at, *set, *pushed, *popped, back;

    vector<int>::iterator inserted, erased, begin, end;

    vector<int> v;

    for (int i = 0; i < nelements; i++) {
        v.push_back(i);
        length = v.size();
        capacity = v.capacity();
        is_empty = v.empty();
        at = v.at(i);
        v[i] = i;
        begin = v.begin();
        back = v.back();
        end = v.end();
    }

    for (int i = 0; i < nelements / 2; i++) {
        v.pop_back();
        length = v.size();
        capacity = v.capacity();
        is_empty = v.empty();
        at = v.at(i);
        v[i] = i;
        begin = v.begin();
        back = v.back();
        end = v.end();
    }

    v.clear();
    length = v.size();
    is_empty = v.empty();
    capacity = v.capacity();

    for (int i = 0; i < nelements; i++) {
        length = v.size();
        inserted = v.insert(v.begin() + i, i);
        length = v.size();
        capacity = v.capacity();
        is_empty = v.empty();
        at = v.at(i);
        v[i] = i;
        back = v.back();
        end = v.end();
    }

    for (int i = 0; i < nelements / 2; i++) {
        length = v.size();
        erased = v.erase(v.begin() + i);
        length = v.size();
        capacity = v.capacity();
        is_empty = v.empty();
        at = v.at(i);
        v[i] = i;
        back = v.back();
        end = v.end();
    }

    v.resize(100000);
    length = v.size();
    is_empty = v.empty();
    capacity = v.capacity();

    v.resize(1000);
    length = v.size();
    is_empty = v.empty();
    capacity = v.capacity();

    v.resize(1);
    length = v.size();
    is_empty = v.empty();
    capacity = v.capacity();

    v.resize(0);
    length = v.size();
    is_empty = v.empty();
    capacity = v.capacity();
}
