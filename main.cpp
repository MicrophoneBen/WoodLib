// main.cpp 代码阶段测试并优化
#include <iostream>
#include "SmartPointer.h"
#include "SharedPointer.h"

using namespace std;
using namespace WoodLib;

class Test : public Object
{
public:
    int m_i;

public:
    Test(int i = 0) : m_i(i)
    {
        cout << "Test::Test()" << endl;
    }

    ~Test()
    {
        cout << "Test::~Test()" << endl;
    }

    void print()
    {
        cout << "m_i = " << m_i << endl;
    }

    void setMi(int i)
    {
        m_i = i;
    }
};

int main()
{
    Test* pt1 = new Test(0);
    cout << "pt1 = " << pt1 << endl;
    pt1->print();

    SmartPointer<Test> ps1(pt1);
    ps1->setMi(100);             // 智能指针调用所指向的类中的函数

    ps1->print();
    cout << "ps1.get() = " << ps1.get() << endl;
    cout << "ps1.isNull() = " << ps1.isNull() << endl;
    cout << endl;

    SmartPointer<Test> ps2(ps1);

    cout << "ps1.get() = " << ps1.get() << endl;
    cout << "ps2.get() = " << ps2.get() << endl;
    cout << "ps1.isNull() = " << ps1.isNull() << endl;
    cout << "ps2.isNull() = " << ps2.isNull() << endl;
    cout << endl;

    Test* pt2 = new Test();
    Test* pt3 = new Test();

    SharedPointer<Test> ps3 = pt2;
    SharedPointer<Test> ps4(pt3);

    cout << "ps3 == ps4 ==> :" << (ps3 == ps4) << endl;
    cout << "ps3.get() = " << ps3.get() << endl;
    cout << "ps4.get() = " << ps4.get() << endl;

    ps4 = ps3;

    cout << "ps3 == ps4 ==> :" << (ps3 == ps4) << endl;
    cout << "ps3.get() = " << ps3.get() << endl;
    cout << "ps4.get() = " << ps4.get() << endl;

    //const SharedPointer<Test> ps5 = new Test();
    //ps5->m_i = 1;  // error 说明与原生指针一样const对象不能作为左值

    return 0;
}
/* 运行结果
Test::Test()
pt1 = 0x26f10b8
m_i = 0
m_i = 100
ps1.get() = 0x26f10b8
ps1.isNull() = 0

ps1.get() = 0
ps2.get() = 0x26f10b8
ps1.isNull() = 1
ps2.isNull() = 0

Test::Test()
Test::Test()
ps3 == ps4 ==> :0
ps3.get() = 0x26f10c8
ps4.get() = 0x26f10d8
Test::~Test()
ps3 == ps4 ==> :1
ps3.get() = 0x26f10c8
ps4.get() = 0x26f10c8
Test::~Test()
Test::~Test()
*/
