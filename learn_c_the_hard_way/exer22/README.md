# c scope

+ 避免`shadow`变量
+ 避免使用过多全局变量。若要使用，则利用`static`关键字并使用accessor函数访问。
    + 不包括常量，因为常量是`read_only`的。
+ `extern`关键字用于头文件中，表明从另一个源文件中获取该变量。
+ 不要再函数内部静声明静态变量，并发线程访问情况下往往会出问题。
+ 避免重用函数参数。
