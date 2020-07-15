#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;

template <typename InputIterator, typename OutputIterator,
          typename ElemType, typename Comp>
OutputIterator filter(InputIterator first, InputIterator last,
                    OutputIterator out, const ElemType &val, Comp pred) {
    
    while ((first = find_if(first, last, bind2nd(pred, val))) != last) {
        cout << "found value: " << *first << endl;
        *out++ = *first++;
    }
    return out;
}

int main() {
    const int elem_size = 8;

    int ia[elem_size] = {12, 8, 43, 0, 6, 31, 21, 7};

    int ia2[elem_size];
    vector<int> ivec2(elem_size);

    filter(ia, ia + elem_size, ia2, elem_size, less<int>());

    cout << endl;

    filter(ia, ia + elem_size, back_inserter(ivec2), elem_size, greater<int>());

    return 0;
}
