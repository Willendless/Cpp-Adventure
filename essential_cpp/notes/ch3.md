# ch3 泛型编程风格

标准模板库(STL)由容器和泛型算法两部分组成。泛型算法通过1.function template技术以操作不同类型的对象，2.iterator操作不同容器。

## 使用iterator抽象

对于vector和数组我们可以使用指针索引的方式实现泛型函数，但是对于list，由于其内元素并非存储于连续地址空间中，因此为vector和数组实现的泛型函数无法复用。为解决这个问题，使用iterator在底层指针操作之上提供了一层抽象，取代程序原本的“指针直接操作”方式以达到通用性。在iterator抽象层，我们能够将原本的指针操作例如`++，*，!=`等运算符重载，以达到想用的功能。

## 泛型算法

+ search algorithm: find(), count(), adjacent_find()
+ sorting and ordering algorithm: sort(), rotate(), random_shuffle(), reverse()
+ copy,deletion,substitution algorithm: copy(), remove(), remove_if()
+ relational algorithm: equal(), includes(), mismatch()
+ generation and mutation algorithm: fill(), for_each(), generate()
+ numeric algorithm: accumulate(), adjacent_difference(), partial_sum()
+ set algorithm: set_union(), set_difference()

所有容器类及string类的通用操作如下：

+ equality(==)和inequality(!=)
+ assignment(=)运算符，将某个容器复制给另一个容器
+ empty()
+ size()
+ clear()

## 顺序性容器

+ vector
+ list
+ deque

## Map

输入key/value: `words["abc"]=1`

遍历map:
```c++
map<string, int>::iterator it = words.begin();
for (; it != words.end(); ++it) {
    cout << "key: " << it->first
         << "value: " << it->second << endl;
}
```

查询某个key是否在map中的三种方法：
1. 将key当成索引，但若key不在map中，则会自动加入map
2. 利用map的find()函数，若key在其中则会返回指向key/value形成的pair的iterator，否则返回指向end()的iterator
3. 利用map的count()函数，返回查询key出现的次数

## Set

对于任何key，Set只存储一份。默认情况下，set元素按所属类型的less-than运算符进行排列。

## Iterator Inserter

`#include <iterator>`

使用Iterator Inserter修改容器的赋值运算符的行为：
+ back_inserter(): 以push_back()取代赋值
+ inserter(): 以insert()取代赋值，insert()接受两个参数，一个是插入的容器，另一个是插入起点位置迭代器
+ front_inserter(): 以push_front()取代赋值，仅适用于list和deque

## iostream Iterator

`#include <iterator>`

将istream_iterator绑定至标准输入设备。
```
istream_iterator<string> is(cin);
istream_iterator<string> eof;           // 表示last即EOF的iterator

ostream_iterator<string> os(cout, " ")  // 第二个参数指明分隔符
```
