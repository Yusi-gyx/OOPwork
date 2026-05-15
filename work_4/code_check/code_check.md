# 代码审阅作业

* 正确性
  1、在*AgentCompany::resetCTO*函数中*new_ctp*变量会在运行到函数外时销毁，而*AgentCompany*类中的*cto*对象最后进行析构时会对同一块地址进行双重释放。应该定义并使用深拷贝构造函数。
* 运行效率
  1、*AgentCompany::resetCTO*函数中拷贝可以使用移动构造函数，使得拷贝过程中时间、内存开销更小。
* 设计合理性
  1、将*AgentCompany::getCEO*函数中返回值改为*CEOAgent*之后，应该将*Agent*设计为抽象类，将它的*work*函数和析构函数均设计为纯虚函数。通过指针、引用使用对象可以更加灵活，代码更加简洁。
