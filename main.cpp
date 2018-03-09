// StaticStack 基于顺序存储结构栈的使用示例
#include <iostream>
#include "StaticStack.h"

using namespace std;
using namespace WoodLib;

class Test
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
    StaticStack<Test, 10> s1;

    // 顺序栈的严重缺陷，创建顺序栈对象时，若栈中存储的数据元素是类类型时
    // 会调用N次构造函数，对象销毁时又会调用N次析构函数。明明没有压栈，但
    // 却也会发生N次构造N次析构，这样效率是很底下的；

    // 原因就是因为顺序栈是使用原生数组作为存储空间的，所以栈对象在创建时
    // 数组的各个元素肯定也有个初始化的过程，当数组类型为类类型时自然就会
    // 调用构造函数了，销毁时自然也就会调用析构函数了！

    // 问题根源就在于顺序栈的这个存储空间会随着对象的创建而每个数组元素都
    // 初始化一遍，从这入手，那么我用链表来作为存储空间这个问题不就迎刃而解
    // 了吗！---> 这就是链式栈了！

    cout << "s1.size() = " << s1.size() << endl;

    return 0;
}
/* 运行结果
Test::Test()
Test::Test()
Test::Test()
Test::Test()
Test::Test()
Test::Test()
Test::Test()
Test::Test()
Test::Test()
Test::Test()
s1.size() = 0
Test::~Test()
Test::~Test()
Test::~Test()
Test::~Test()
Test::~Test()
Test::~Test()
Test::~Test()
Test::~Test()
Test::~Test()
Test::~Test()
*/
