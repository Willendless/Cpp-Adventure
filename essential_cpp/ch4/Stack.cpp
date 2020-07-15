#include "Stack.h"
#include <iostream>
using namespace std;

bool
Stack::push(const string &elem) {
    if (full()) return false;

    _stack.push_back(elem);
    return true;
}

bool
Stack::pop(string &elem) {
    if (empty()) return false;

    elem = _stack[size() - 1];
    _stack.pop_back();
    return true;
}

bool
Stack::peek(string &elem) {
    if (empty()) return false;

    elem = _stack[size() - 1];
    return true;
}

int main() {
    Stack stack;
    stack.push("!");
    stack.push("World");
    stack.push("Hello");

    while (!stack.empty()) {
        string elem;
        if (!stack.pop(elem)) {
            cout << "Pop failed" << endl;
            exit(-1);
        }
        cout << "> " << elem << endl;
    }
    return 0;
}
