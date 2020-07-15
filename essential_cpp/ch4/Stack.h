#include <vector>
#include <string>
using namespace std;
class Stack;

class Stack {
public:
    bool push(const string &elem);
    bool pop(string &elem);
    bool peek(string &elem);

    bool empty() { return _stack.empty(); }
    bool full();

    int size() { return _stack.size(); }

private:
    vector<string> _stack;
};

inline bool Stack::full()
{
    return _stack.size() == _stack.max_size();
}
