#ifndef TRIANGULAR_H_
#define TRIANGULAR_H_

#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

class Triangular_iterator {
public:
    Triangular_iterator(int index) : _index(index - 1){}
    bool operator==(const Triangular_iterator&) const;
    bool operator!=(const Triangular_iterator&) const;
    int operator*() const;
    Triangular_iterator& operator++();
    Triangular_iterator operator++(int);

private:
    int _index;
    void check_integrity() const;
};

class Triangular {
public:
    typedef Triangular_iterator iterator;
    friend class Triangular_iterator;
    Triangular(int bp = 1, int len = 1);
    static bool is_elem(int);
    static void gen_elements(int length);
    static void gen_elems_to_value(int value);

    iterator begin() const { return iterator(_beg_pos); }
    iterator end() const { return iterator(_beg_pos + _length); }

private:
    static const int   _max_elem = 1024;
    static vector<int> _elems;
    int _beg_pos;
    int _length;
};

inline int Triangular_iterator::
operator*() const
{
    check_integrity();
    cout << "> index: " << _index << " val: ";
    return Triangular::_elems[_index];
}

inline bool Triangular_iterator::
operator==(const Triangular_iterator &rhs) const
{
    return _index == rhs._index;
}

inline bool Triangular_iterator::
operator!=(const Triangular_iterator &rhs) const
{
    return !(*this == rhs);
}

inline void Triangular_iterator::
check_integrity() const
{
    if (_index >= Triangular::_max_elem)
        exit(-1);
    
    if (_index >= Triangular::_elems.size())
        Triangular::gen_elements(_index + 1);

}

inline Triangular_iterator& Triangular_iterator::
operator++()
{
    ++_index;
    check_integrity();
    return *this;
}

inline Triangular_iterator Triangular_iterator::
operator++(int)
{
    Triangular_iterator tmp = *this;
    ++_index;
    check_integrity();
    return tmp;
}

#endif
