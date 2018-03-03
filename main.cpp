// main.cpp Object类使用示例
#include <iostream>
#include "Object.h"
#include "SmartPointer.h"
#include "Exception.h"

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
    SmartPointer<Test> s = new Test();

    cout << "------ 1 ------" << endl;

    SmartPointer<Test>* ps = &s;

    cout << "------ 2 ------" << endl;

    SmartPointer<Test>* ps1 = new SmartPointer<Test>();

    cout << "------ 3 ------" << endl;

    SmartPointer<Test>* ps2 = new SmartPointer<Test>(new Test);

    cout << "------ 4 ------" << endl;

    cout << s.isNull() << endl;
    cout << ps->isNull() << endl;
    cout << ps1->isNull() << endl;   // 因为ps1->m_pointer为NULL
    cout << ps2->isNull() << endl;   // 因为ps2->m_pointer = new Test

    cout << "------ 5 ------" << endl;

    delete ps1;
    cout << "------ 6 ------" << endl;
    delete ps2;
    //delete ps;     // 这里就会发生多重释放的问题,因为s随着main()退出
                     // 会自动释放而ps就是指向的 s ，所以这里释放就会
                     // 造成后面 s 释放双重释放问题

                     // 结论：指向智能指针类变量的指针不需要手动释放
                     // 但指向堆空间上面的智能指针类的指针需要手动释放

                     // s 是个智能指针局部变量，ps指向的就是一个局部变量
                     // ps1 和 ps2 指向的是指向堆上面的智能指能指针

    cout << "------ 7 ------" << endl;

    InvalidOperationException* e = new InvalidOperationException();

    delete e;

    cout << "------ 8 ------" << endl;

    return 0;
}
/* 运行结果
Object::operator new: 8
Test::Test()
SmartPointer()
------ 1 ------
------ 2 ------
Object::operator new: 8
SmartPointer()
------ 3 ------
Object::operator new: 8
Test::Test()
Object::operator new: 8
SmartPointer()
------ 4 ------
0
0
1
0
------ 5 ------
~SmartPointer()
Object::~Object()
Object::operator delete:0x2ed10c8
------ 6 ------
~SmartPointer()
Test::~Test()
Object::~Object()
Object::operator delete:0x2ed10d8    // m_pointer指向的堆内存(Test)的释放
Object::~Object()
Object::operator delete:0x2ed10e8    // ps2指向的堆内存(智能指针)的释放
------ 7 ------
Object::operator new: 12
Object::~Object()
Object::operator delete:0x32210c8
------ 8 ------
~SmartPointer()                      // s的释放一样是ps所指向的智能指针的释放
Test::~Test()
Object::~Object()
Object::operator delete:0x2ed10b8
Object::~Object()
*/
