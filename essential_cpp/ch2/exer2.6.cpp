#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
inline T max(T a, T b) {
    return a > b ? a : b;
}

template <typename vecT>
inline vecT max(vector<vecT> &vec) {
    return *max_element(vec.begin(), vec.end());
}

template <typename arrT>
inline arrT max(arrT *arr, int len) {
    return *max_element(arr, arr + len);
}
