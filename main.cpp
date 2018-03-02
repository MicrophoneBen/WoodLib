// main.cpp Object类使用示例
#include <iostream>
#include "Object.h"

using namespace std;
using namespace WoodLib;

// 有一个隐藏的指向虚函数表的指针
class Test : public Object
{
protected:
    int* m_pointer;

public:
    Test(int* pointer = NULL) : m_pointer(pointer)
    {
        cout << "Test::Test()" << endl;
    }

    ~Test()
    {
        delete m_pointer;    // 这个delete使用的是内置的
        cout << "Test::~Test()" << endl;
    }
};

// 有一个隐藏的指向虚函数表的指针
class Child : public Test
{
public:
    Child(int* pointer = NULL) : Test(pointer)
    {
        cout << "Child::Child()" << endl;
    }

    ~Child()
    {
        cout << "Child::~Child()" << endl;
    }
};

int main()
{
    Test* t1 = new Test();   // Object重载的new只是对继承自Object的类的创建有效
    Child* c1 = new Child(); // 重载的new -> Object() -> Test() -> Child()

    cout << "t1 = " << t1 << endl;
    cout << "c1 = " << c1 << endl;

    int* p = new int;      // 内置类型即基本类型还是使用系统的 new
    cout << "p = " << p << endl;

    delete t1;             // delete也同理

    delete c1;             // 先调用子类析构函数->父类析构函数->顶层父类析构函数
                           // 再调用重载的delete运算符函数释放推内存

                           // 这里也就证明了作为父类的析构函数一定要提供实现,即使
                           // 是纯虚析构函数也要提供实现，否则编译就直接报错
    delete p;

    return 0;
}
/* 运行结果
Object::operator new: 8           // 包含一个指向虚函数表的指针
Test::Test()
Object::operator new: 8          // 重载的new
Test::Test()                     // （也调用了顶层父类的构造只不过没打印而已）Test类构造
Child::Child()                   // 子类自己的构造
t1 = 0x2f210b8
c1 = 0x2f210c8
p = 0x2f210d8
Test::~Test()                     // 同下面分析过程
Object::~Object()
Object::operator delete:0x2f210b8
Child::~Child()                   // 子类析构
Test::~Test()                     // 父类析构
Object::~Object()                 // 顶层父类析构
Object::operator delete:0x2f210c8 // 重载的delete
*/
