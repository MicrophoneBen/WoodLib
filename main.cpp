// main.cpp LinkList类的使用示例
#include <iostream>
#include "LinkList.h"

using namespace std;
using namespace WoodLib;

class Test
{
public:
    Test()
    {
        throw 0;  // 在构造函数中抛异常，故意制造出来的！
    }
};

int main()
{
    // 测试1
    LinkList<int> list;

    for(int i=0; i<5; i++)
    {
        list.insert(i);
    }

    for(int i=0; i<list.length(); i++)
    {
        cout << list.get(i) << " ";
    }

    cout << endl;

    list.remove(2);

    list.set(0, 100);

    for(int i=0; i<list.length(); i++)
    {
        cout << list.get(i) << " ";
    }

    cout << endl;

    list.clear();

    for(int i=0; i<list.length(); i++)
    {
        cout << list.get(i) << " ";
    }

    // 测试2
    // 如果LinkList类不采用借尸还魂来解决Test抛异常的话，
    // LinkList的使用者会以为这个异常是LinkList类设计的
    // 问题，因为他们认为自己并没有调用Test的构造函数，所
    // 以不会怀疑是Test类设计的问题，而是LinkList类的问题。
    LinkList<Test> lt;

    Test t;  // 这样就会抛出异常了,这样就很明显与WoodLib库无关了

    return 0;
}
/* 运行结果
Object::operator new: 12
Object::operator new: 12
Object::operator new: 12
Object::operator new: 12
Object::operator new: 12
0 1 2 3 4
Object::~Object()
Object::operator delete:0x2e710e8
100 1 3 4
Object::~Object()
Object::operator delete:0x2e710b8
Object::~Object()
Object::operator delete:0x2e710d0
Object::~Object()
Object::operator delete:0x2e71100
Object::~Object()
Object::operator delete:0x2e71118

This application has requested the Runtime to terminate it in an unusual way.
Please contact the application's support team for more information.
terminate called after throwing an instance of 'int'
*/



