// main.cpp StaticList类和DynamicList类的使用示例
#include <iostream>
#include "StaticList.h"
#include "DynamicList.h"

using namespace std;
using namespace WoodLib;

class Test   // 测试用无实际用途
{
private:
    int* m_value;

public:
    Test()
    {
        cout << "Test()" << endl;
        m_value = new int;
    }

    Test(int value)
    {
        m_value = new int;
        *m_value = value;
        cout << "Test(int value)" << endl;
    }

    void setValue(int value)
    {
        *m_value = value;
        cout << "void setValue(int value)" << endl;
    }

    int getValue() const
    {
        return *m_value;
    }

    Test& operator=(const Test& obj)
    {
        delete m_value;

        m_value = new int;

        *m_value = *obj.m_value;

        cout << "Test& operator=(const Test& obj)" << endl;
        return *this;
    }

    ~Test()
    {
        delete m_value;
        cout << "~Test()" << endl;
    }
};


int main()
{
    //StaticList<int, 5> l;
    DynamicList<int> l(5);

    for(int i=0; i<l.capacity(); i++)
    {
        //l[i] = i;      // 这样m_length不会变化,这也体现了与数组的不同点
        l.insert(0, i);  // 每次都在头部插入
    }

    l[0] *=l[0];         // 平方

    for(int i=0; i<l.length(); i++)
    {
        cout << l[i] << " ";
    }

    cout << endl;

    try
    {
        l[5] = 5;        // 越界异常
    }
    catch(const Exception& e)
    {
        cout << e.getMessage() << endl;
        cout << e.getLocation() << endl;

        l.resize(10);
        l.insert(5, 50);
    }

    l[5] = 5;

    for(int i=0; i<l.length(); i++)
    {
        cout << l[i] << " ";
    }

    cout << endl;

    l.resize(3);

    for(int i=0; i<l.length(); i++)
    {
        cout << l[i] << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
16 3 2 1 0
Parameter index is invalid ...
..\SequenceList.h:100
Object::~Object()
16 3 2 1 0 5 43305632 43253952 0 0
16 3 2
Object::~Object()
*/


