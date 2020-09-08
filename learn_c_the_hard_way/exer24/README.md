# c文件IO

+ `char *fgets(char *s, int size, FILE *stream);`
    + `scanf`读取字符串前无法指定buffer的长度
    + `fgets`读取最多size-1个字符到s中，若读到`\n`，则也会包含在s中
    + 若成功，返回指向`s`的指针
+ `fscanf()`返回成功读取的数目。
+ 枚举类型的最后一个成员可以作为遍历的结尾。


> 读取字符串时使用`fgets()`  
> 避免使用gets()
