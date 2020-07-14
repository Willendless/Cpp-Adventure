#include<iostream>
#include<vector>

using namespace std;


void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void bubble_sort(vector<int> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = vec.size() - 1; j > i; --j) {
            if (vec[j] < vec[j - 1]) {
                swap(vec[j], vec[j - 1]);
            }
        }
    }
}

void display(const vector<int> &vec, ostream &os = cout) {
    for (int i = 0; i < vec.size(); ++i) {
        os << vec[i] << " ";
    }
    os << endl;
}

int main() {

    int ia[] = {8, 34, 3, 13, 1, 21, 5, 2};
    vector<int> vec(ia, ia + 8);

    bubble_sort(vec);

    display(vec);

    return 0;
}
