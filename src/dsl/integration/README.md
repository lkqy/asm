# 接入方法

参考单元测试 https://gitlab.ushareit.me/sprs/platform/asm/blob/hekang/test/dsl/test_integration.cpp

## 表达式变量、常量
以_, a~z 开头的token为变量

以A~Z 开头的token为函数

支持常量类型，比如1=>long, -1.0=>double, +2.0=>double


# 表达式支持的功能

1、+ - * / % ^(幂运算) 支持5种类型的数值类型及对应的数组类型

2、> >= == < <= != 支持四种类型的数值类型及对应的数组类型、string

3、and、or、in

4、 IF

5、 Log: 对数

6、 如有需要可扩展函数支持
