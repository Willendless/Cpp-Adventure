# defensive programming

## strategies

+ never trust the input
    + 对每一个参数，识别precondition，是否会导致failure或者返回error。对于库，返回error更好
    + 对failure情况，增加`assert(test && message)`调用
    + 对error情况，返回error码或者使用宏给出错误信息
    + 将precondition文档化
    + 函数返回时，总是验证error code
    + 一致地使用error code
+ prevent errors
+ fail early and openly
    + 返回错误码=>使用宏，并处理错误
    + 中断程序=>使用`assert(test && message)`
        + 较少使用，通常无法恢复的灾难性的错误时使用
+ document assumptions: 同时将invariant和postcondition文档化
    + invariant: 当函数运行时必须保持的一些状态，例如对于有序数据结构，在处理过程中仍需要保证有序。
    + postcondition: 函数运行结果和退出值得保证。
    + 对于invariant和postcondition通常在文档中说明。较好的方式是尽量使用`assert`同时剩下的用文档记录。
+ prevention over documentation
+ automate everything
    + 测试和验证
    + 构建进程
    + 软件部署
    + 系统管理
    + 错误报告
+ simplify and clarify
+ question authority
