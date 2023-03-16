#include <stack>

using namespace std;

int main() {
    int nelements = 100000000;
    bool is_empty;
    size_t length;
    int top, *pushed, *popped;
    
    stack<int> s;

    for (int i = 0; i < nelements; i++) {
        s.push(i);
        length = s.size();
        is_empty = s.empty();
        top = s.top();
    }

    for (int i = 0; i < nelements / 2; i++) {
        top = s.top();
        s.pop();
        length = s.size();
        is_empty = s.empty();
    }
}