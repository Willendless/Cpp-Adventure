# C project skeleton

## directory architecture

+ /bin
+ /build
+ /src
+ /tests
+ LICENSE
+ Makefile
+ README.md

## 库

+ 静态库：.o文件集合，用于中等和小项目
    + ar用于将目标文件添加到库中
    + ranlib用于更新库的符号表
+ 动态库：用于较大项目
    + `dlopen`
    + `dlsym`
    + `dlclose`
    + `cc -c *.c -o *.o`
    + `cc -shared -o *.so *.o`
    + `cc -Wall -g *.c -ldl -o [exe]`
    + 注：不同系统中使用`-ldl`选项的顺序不一定相同，对于ubuntu/debian必须在源文件后添加该参数。
        + `$(CC) $(CFLAGS) $(TEST_SRC) -ldl -o $(TESTS)`
+ 库的实现中尽量不用`assert`断言，函数如果存在参数为字符串，则同时应当有一个参数为字符串长度。

## 单元测试框架

+ 标准错误流的重定向输出到测试log文件中

### 关于Makefile

+ `$@`表示target
+ `$<`表示第一个依赖
+ `$^`表示所有依赖
+ ubuntu下`-ldl`需要在源文件之后使用的解决

```Makefile
TEST_SRC=$(wildcard tests/*_tests.c)
TEST_OBJ=$(patsubst %.c,%.o,$(TEST_SRC))
TESTS=$(patsubst %.c,%,$(TEST_SRC))

$(TESTS): $(TEST_OBJ)
	$(CC) $(CFLAGS) $@.o -o $@ -ldl
```
