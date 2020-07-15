# ch4

## 类基础

class定义由两部分组成：class的声明，以及紧接在声明之后的主体。

+ class主体内定义的member function自动被视为inline函数。
+ class主体外定义member function需要加上([class name]::)，成为class scope resolution(类作用域解析运算符)。也可在主体之外定义inline成员函数，则需要加上inline关键字。
+ 注意：类似于non-member inline function，inline member function函数也需要放于头文件中。

> class定义及其inline member function通常都会放在头文件中。non-inline member function应在程序代码文件中定义。

## 构造和析构函数

### class object初始化

1. 应用default constructor：`Triangular t;`
2. 应用两个参数的构造器`Triangular t(10, 3)`
3. 应用单一参数的构造器`Triangular t = 8`

#### default constructor

1. 不接受任何参数`Triangular::Triangular(){}`
2. 为每个参数提供默认值`Triangular::Triangular(int len=1, int bp=1){} // 同时支持默认、单一参数、两个参数的对象初始化`

#### 成员初始化列表

作用：初始化列表中初始化的类对象成员不需额外调用该类对象的无参初始化构造函数，直接调用拷贝构造函数初始化。

语法：
```c++
Triangular::Triangular(const Triangular &rhs)
  : _length(rhs._length),
    _beg_pos(rhs._beg_pos), _name("Triangluar")
{}
```

必须使用初始化列表初始化的成员类型：
1. 常量成员，只能初始化，不能赋值
2. 引用类型，不能重新赋值
3. 没有默认构造函数的类类型。

#### 成员逐一初始化

默认情形下的拷贝构造，类对象成员会被依次复制，称为memberwise initialization。

> 注意：若类包含指heap内存数组的指针，在默认拷贝构造的情况下，destructor时会将指针指向的空间释放。则原对象内该成员就会编程dangling pointer。解决方法是为该类实现拷贝构造器，使用独立的数组副本

若有必要为类编写copy constructor，则同样有必要为其编写copy assignment operator。

### mutable和const

在成员函数上标注const指明该member function不会更改class object的内容，编译器会检查每个声明为const的成员函数，查看是否修改class object的内容。

#### mutable data member

若某个类成员的修改不会改变类对象的状态，或称不会破坏对象的常量性(constness)。则通过将该对象标示为mutable，就可以在const函数中修改它。

### this指针

编译器自动将this指针加到每一个member function的参数列表。

### 静态类成员

静态类成员只有一份实体，因此需要在程序代码文件中提供定义。声明时也可提供初值。静态类成员和函数在主体外进行定义时，无须重复加上关键字static。

### 运算符重载与迭代器类

运算符重载规则：
+ 不可以引入新运算符。除., .*, ::, ?:外其它运算符均可重载。
+ 运算符的操作数不可改变。
+ 运算符的优先级不可改变。
+ 运算符函数的参数列表中，必须至少有一个参数为class类型。

运算符重载函数定义方式有两种，一种类似于member function，另一种类似non-member function，其参数列表显示表示this指针。

```c++
inline int Triangular_iterator::
operator*() const
{
    check_integrity();
    return Triangular::_elems[_index];
}

inline int
operator*(const Triangular_iterator &rhs)
{
    rhs.check_integrity();

    return Triangular::_elems[_index];
}
```

如果一个运算符和另一个性质相反，通常由后者实现前者。例如使用!=实现==。

后置的++/--版本的操作符实现，参数需要加上一个int类型形参。

*嵌套类型：*
```c++
class Triangular {
    typedef Triangular_iterator iterator;   // 嵌套类型
}
```
由于`Triangular_iterator`是嵌套类型，所以在`Triangular`外对其的所有访问操作都必须以class scope运算符加以限定。

### 友元

++需要修改其它类的私有成员时，需要将function或class指定为朋友(friend)，则对应function或class就具备了和class member function相同的访问权限。

另一种解决方式是引入public member function的getter方法导出私有成员。

### 函数对象

function object: 提供有function call运算符的class。通常用作泛型算法的参数。

语法：
`lt(ival)`，`lt`可以是函数，函数指针或者function object。当`lt`是function object时，编译器会将该语句转换为`lt.operator(ival)`
定义:
```bool operator()(int val) {}```

### 重载iostream运算符

定义:
```c++
ostream& operator<<(ostream &os, const Triangular &rhs)
istream& operator>>(istream &is, Triangular &rhs)
```

iostream运算符重载函数不设计成member function是因为，对于member function，其左操作数必须是隶属于同一个class的对象(由member function默认提供this指针)。

> 注意：当基于性能而非修改内容的目的使用传引用时要加上const关键字

### 类成员函数指针

语法：
```c++
typedef voie ([class scope]::*PtrType) (int);
PtrType pm = 0;
pm = &[class scope]::fibonacci;
```

使用类成员函数指针和类对象进行调用：

```c++
[class scope] a;
[class scope] *pa = &a;
PtrType pm = &[class scope]::func;
(a.*pm)(pa);    // 调用方式1
(pa->*pm)(pa);  // 调用方式2
```
其中`.*`和`->*`符号是pointer to member selection运算符
