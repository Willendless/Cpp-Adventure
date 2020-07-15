#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    istream_iterator<string> is(cin);
    istream_iterator<string> eof;

    vector<string> input_vec;
    copy(is, eof, back_inserter(input_vec));

    sort(input_vec.begin(), input_vec.end());

    ostream_iterator<string> os(cout, " ");
    copy(input_vec.begin(), input_vec.end(), os);

    return 0;
}
