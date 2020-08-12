# Debug macros

## C Error-Handling Problem

当遇到runtime error时，c程序通过返回error codes并且设置一个全局`errno`来处理错误。这意味着以下重复的代码模式：

+ 调用函数
+ 验证返回值是否有错
+ 如果有错则清理分配的所有资源
+ 打印错误信息

过去，c程序遇到错误时直接退出并依赖于os回收资源。但如果需要保证程序的可靠性，例如编写web服务器程序这就成了一个问题。其它语言依赖异常机制，这需要构造一个基于栈的能够返回任意数量值的返回系统，而c语言的函数仅能返回一个值。

## Debug macros

作者使用c宏实现了一个基本的debugging和error-handling系统。实现方式基于c语言惯例：当error发生，使用`goto`跳转到标签`error:`，并由标签处的代码释放资源。

## 功能

1. debug: 输出debug信息(文件名，行，格式化字符串)
2. log：输出log信息(同debug，但分成err，warn，info三类)
3. check
    + assert true：`check()`，`check_debug()`
    + unreached code: `sentinel()`
    + null ptr: `check_mem()`

## Extra credit

1. 通过`#define NDEBUG`关闭debug相关宏使用
2. Makefile中通过在`CFLAGS`中添加`-DNDEBUG`关闭debug相关宏使用
    + `CFLAGS="-DNDEBUG" make ex19`
3. 当前函数名__func__，当前文件名__FILE__，当前行__LINE__
