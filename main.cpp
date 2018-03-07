// main.cpp 代码阶段测试并优化
#include <iostream>
#include "LinkList.h"
#include "StaticLink.h"
#include "DynamicArray.h"

using namespace std;
using namespace WoodLib;

#if 0
class Test : public Object
{
    int m_id;

public:
    Test(int id = 0)
    {
        m_id = id;
    }

    ~Test()
    {
        if(1 == m_id)
        {
            // 故意在析构函数中抛出异常
            // 因为QtCreator编译器不允许析构函数中抛出异常
            // 还没有捕抓到这个异常时程序就被编译器异常结束了
            // 我做这个测试在linux的g++下完成的
            throw m_id;
        }
    }
};
#endif

int main()
{
#if 0
    // 问题2：LinkList 中 remove() 、clear() 没做到异常安全
    LinkList<Test> list;

    Test t0(0), t1(1), t2(2);

    try
    {
        list.insert(t0);
        list.insert(t1);  // t1 在析构时抛出异常
        list.insert(t2);

        list.remove(1);   // 移除链表中第 1 个结点
                          // 当前的代码能确保 remove() 异常安全 ???
    }
    catch(const int& e)
    {
        cout << e << endl; // 1,表示 m_id 为 1

        // expected 2, but 3 <== 这就是问题
        // 期待应该是 2 的,但结果还是 3
        // 明明移除了一个链表长度应该是 2 的,但发现却还是 3
        // 原因就是移除的那个结点析构函数中抛出了一个移除,导致其没有正常移除
        // 这就说明我当前的这个 WoodLib 对于这个情况还是不能做到异常安全！！！
        cout << list.length() << endl;
    }
#endif

#if 0
    // 问题3： LinkList中遍历操作与删除操作混合使用
    LinkList<int> list;

    for(int i=0; i<5; i++)
    {
        list.insert(i);
    }

    for(list.move(0); !list.isEnd(); list.next())
    {
        if( list.current() == 3 )
        {
            list.remove(list.find(list.current()));

            // 当前代码这一步输出的是个随机值不是期望的4,这就是问题！！！
            // 已经移除了这个结点,但是m_current还指着这个删除的结点
            // 所以就输出了一个随机值,原因就是 remove() 中的问题！！！
            cout << list.current() << endl;
        }
    }

    for(int i=0; i<list.length(); i++)
    {
        cout << list.get(i) << " ";
    }

    cout << endl;

#endif

#if 1
    // StaticLink类 析构函数追踪
    StaticLink<int, 5> s_list;

    for(int i=0; i<s_list.capacity(); i++)
    {
        s_list.insert(i);
    }

    for(s_list.move(0); !s_list.isEnd(); s_list.next())
    {
        cout << s_list.current() << " ";
    }

    cout << endl;
#endif

#if 0
    // 3*3 二维数组
    DynamicArray< DynamicArray<int> > d;

    d.resize(3);

    for(int i=0; i<d.length(); i++)
    {
        d[i].resize(3);
    }

    for(int i=0; i<d.length(); i++)
    {
        for(int j=0; j<d[i].length(); j++)
        {
            d[i][j] = i*d[i].length() + j;
        }
    }

    for(int i=0; i<d.length(); i++)
    {
        for(int j=0; j<d[i].length(); j++)
        {
            cout << d[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl;

    // 不规则数组
    DynamicArray< DynamicArray<int> > d2;

    d2.resize(3);

    for(int i=0; i<d2.length(); i++)
    {
        d2[i].resize(i+1);
    }

    for(int i=0; i<d2.length(); i++)
    {
        for(int j=0; j<d2[i].length(); j++)
        {
            d2[i][j] = i*d2[i].length() + j;
        }
    }

    for(int i=0; i<d2.length(); i++)
    {
        for(int j=0; j<d2[i].length(); j++)
        {
            cout << d2[i][j] << " ";
        }

        cout << endl;
    }

#endif

    return 0;
}
/* 运行结果
0 1 2
3 4 5
6 7 8

0
2 3
6 7 8
*/
