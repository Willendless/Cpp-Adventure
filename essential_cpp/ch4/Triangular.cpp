#include <vector>
#include <algorithm>
#include <iostream>
#include "Triangular.h"
using namespace std;

vector<int> Triangular::_elems;

Triangular::
Triangular(int bp, int len)
: _length(len), _beg_pos(bp)
{
    _length = len > 0 ? len : 1;
    _beg_pos = _beg_pos > 0 ? _beg_pos : 1;
}

bool Triangular::
is_elem(int value) 
{
    if (!_elems.size()
        || _elems[_max_elem - 1] < value)
        gen_elems_to_value(value);
    
    vector<int>::iterator found_it;
    vector<int>::iterator end_it = _elems.end();

    found_it = find(_elems.begin(), end_it, value);
    return found_it != end_it;
}

void Triangular::
gen_elems_to_value(int value)
{
    if (!_elems.size())
        _elems.push_back(1);
    
    int i = _elems.size();

    while (_elems[i - 1] < value
           && i < _max_elem) {
        ++i;
        cout << "> push in: " << (i * (i + 1)) / 2 << "\n";
        _elems.push_back((i * (i + 1)) / 2);
    }
}

void Triangular::
gen_elements(int length)
{
    if (length < 0 || length > _max_elem)
        return;
    
    if (_elems.size() < length) {
        int i = _elems.size() + 1;
        for (; i <= length; ++i)
            _elems.push_back((i * (i + 1)) / 2);
    }
}

int main() {
    Triangular t(2, 10);
    t.gen_elems_to_value(4950);

    cout << "> is 3 in: " << t.is_elem(3) << "\n";

    cout << "> is 4950 in: " << t.is_elem(4950) << "\n";

    Triangular::iterator it =  t.begin();
    Triangular::iterator end = t.end();

    for (; it != end; ++it)
        cout << *it << endl;
    cout << endl;

    return 0;
}
