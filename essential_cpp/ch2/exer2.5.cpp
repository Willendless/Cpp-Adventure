#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline float max(float a, float b) {
    return a > b ? a : b;
}

inline string max(const string &a, const string &b) {
    return a > b ? a : b ;
}

inline int max(const vector<int> &vec) {
    return *max_element(vec.begin(), vec.end());
}

inline float max(const vector<float> &vec) {
    return *max_element(vec.begin(), vec.end());
}

inline string max(const vecotr<string> &vec) {
    return *max_element(vec.begin(), vec.end());
}

inline int max(const int *arr, int len) {
    return *max_element(arr, arr + len);
}

inline float max(const float *arr, int len) {
    return *max_element(arr, arr + len);
}

inline string max(const string *arr, int len) {
    return *max_element(arr, arr + len);
}

int main() {

}
