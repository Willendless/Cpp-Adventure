#include <iostream>
#include <vector>
using namespace std;


inline bool is_size_ok(int size) {
    return size < 1024 && size > 0;
}

const vector<int> * fibon_seq(int size) {
    const int MAX_SIZE = 1024;

    static vector<int> elems;

    if (!is_size_ok(size))
        return 0;
    
    for (int i = elems.size(); i < size; ++i) {
        if (i == 0 || i == 1)
            elems.push_back(1);
        else
            elems.push_back(elems[i - 1] + elems[i - 2]);
    }

    return &elems;
}

bool fibon_elem(int pos, int &elem) {
    
    const vector<int> *vec = fibon_seq(pos);

    if (!vec) {
        elem = 0;
        return false;
    }

    elem = (*vec)[pos - 1];
    return true;
}

int main() {
    int pos;

    cout << "Pos: ";
    while (cin >> pos) {
        int elem;
        if (fibon_elem(pos, elem))
            cout << "element # " << pos
                 << " is " << elem << endl;
        else
            cout << "Fail to calc" << endl;
        cout << "Pos: ";
    }

    return 0;
}
