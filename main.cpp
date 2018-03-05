// main.cpp LinkList类的使用示例
#include <iostream>
#include "LinkList.h"

using namespace std;
using namespace WoodLib;

// Test1类没有继承Object要使用LinkList::find()查找就必须有 == 操作符函数
class Test1
{
    int i;

public:
    Test1(int i = 0) : i(i) { }

    bool operator ==(const Test1& obj)
    {
        return (i == obj.i);
    }
};

// Test2类有继承Object 没有 == 操作符函数使用LinkList::find()查找至少编译不会直接报错
class Test2 : public Object
{
    int i;

public:
    Test2(int i = 0) : i(i) { }
};

// Object只是保证编译不直接报错，但逻辑上的比较正确还是要自己根据情况重载 == 造成符
class Test3 : public Object
{
    int i;

public:
    Test3(int i = 0) : i(i) { }

    bool operator ==(const Test3& obj)
    {
        return (i == obj.i);
    }
};

int main()
{
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

    cout << "list.find(4) => " << list.find(4) << endl;

    list.reverse();

    for(int i=0; i<list.length(); i++)    // 单链表的遍历时间复杂度是 O(n*n)，不是线性的，效率太低
    {
        cout << list.get(i) << " ";
    }

    cout << endl;

    cout << "list.find(4) => " << list.find(4) << endl;

    // 自定义类型 Test1 的查找
    Test1 t1(1), t2(2), t3(3);

    // Test1类没有继承Object要使用查找就必须有 == 操作符函数
    LinkList<Test1> list2;

    list2.insert(t1);
    list2.insert(t2);
    list2.insert(t3);

    cout << "list2.find(t3) =>" << list2.find(t3) << endl;

    // 自定义类型 Test2 的查找
    Test2 t4(4), t5(5), t6(6);

    // Test2类有继承Object 没有 == 操作符函数至少编译不会直接报错
    LinkList<Test2> list3;

    list3.insert(t4);
    list3.insert(t5);
    list3.insert(t6);

    cout << "list3.find(t6) =>" << list3.find(t6) << endl;

    // 自定义类型 Test3 的查找
    Test3 t7(7), t8(8), t9(9);

    // Test2类有继承Object 没有 == 操作符函数至少编译不会直接报错
    LinkList<Test3> list4;

    list4.insert(t7);
    list4.insert(t8);
    list4.insert(t9);

    cout << "list4.find(t9) =>" << list4.find(t9) << endl;

    return 0;
}
/* 运行结果
0 1 2 3 4
list.find(4) => 4
4 3 2 1 0
list.find(4) => 0
list2.find(t3) =>2
list3.find(t6) =>-1
list4.find(t9) =>2
*/



