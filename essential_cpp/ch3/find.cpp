#include <iostream>
#include <vector>
using namespace std;

template <typename IteratorType, typename elemType>
IteratorType
find(IteratorType first, IteratorType last, const elemType &value) {
    for (; first != last; ++first) {
        if (*first == value)
            return first;
    }

    return last;
}

int main() {
    const int asize = 8;
    int ia[asize] = {1, 1, 2, 3, 5, 8, 13, 21};

    vector<int> ivec(ia, ia + asize);
    vector<int>::iterator it;
    it = find(ivec.begin(), ivec.end(), 5);
    if (it != ivec.end())
        cout << "find it!" << endl;

    return 0;
}
