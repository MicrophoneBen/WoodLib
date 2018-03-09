// LinkStack 基于链式存储结构栈（简称链式栈）的使用示例
#include <iostream>
#include "LinkStack.h"

using namespace std;
using namespace WoodLib;

class Test : public Object
{
public:
    Test()
    {
        cout << "Test::Test()" << endl;
    }

    ~Test()
    {
        cout << "Test::~Test()" << endl;
    }
};

int main()
{
    LinkStack<Test> l1;    // 没有构造函数的调用

    cout << "l1.size() = " << l1.size() << endl << endl;

    LinkStack<int> l2;

    try
    {
        l2.pop();
    }
    catch(const Exception& e)
    {
        cout << e.getMessage() << endl;
        cout << e.getLocation() << endl;
    }

    cout << "l2.push(): ";
    for(int i=0; i<10; i++)
    {
        cout << i*i << " ";
        l2.push(i*i);
    }

    cout << endl << "l2.size() = " << l2.size() << endl;

    cout << "l2.pop(): ";
    while( l2.size() > 0 )
    {
        cout << l2.top() << " ";
        l2.pop();
    }

    cout << endl;

    return 0;
}

/* 运行结果
l1.size() = 0

No element in current stack ...
..\LinkStack.h:37
l2.push(): 0 1 4 9 16 25 36 49 64 81
l2.size() = 10
l2.pop(): 81 64 49 36 25 16 9 4 1 0
*/
