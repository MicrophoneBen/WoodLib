// main.cpp  对于数据量庞大的对象排序时采用的工程方法：代理模式
#include <iostream>
#include <ctime>      // for clock_t 时间相关的
#include "Object.h"
#include "Sort.h"

using namespace std;
using namespace WoodLib;

// Test 类对象将占用较大的内存空间
// 为了排序需重载比较运算符
struct Test : public Object
{
    // 若直接对这个排序,涉及到数据交换是很庞大的
    int id;
    int data1[1000];
    double data2[500];

    bool operator <(const Test& rhs)
    {
        return this->id < rhs.id;
    }

    bool operator >(const Test& rhs)
    {
        return this->id > rhs.id;
    }

    bool operator <=(const Test& rhs)
    {
        return this->id <= rhs.id;
    }

    bool operator >=(const Test& rhs)
    {
        return this->id >= rhs.id;
    }
};

// Test 的代理类
// TestProxy 本身并不携带大量的数据
//（sizeof(TestProxy) ==8），而 sizeof(Test)==8008，都带了一个虚函数表指针
class TestProxy : public Object
{
protected:
    Test* m_pTest; // 指向 Test 类的指针 能代理的关键

public:
    // 代理类中还是很有必要提供能访问到原生类中数据的接口
    int id()
    {
        return m_pTest->id;
    }

    int* data1()
    {
        return m_pTest->data1;
    }

    double* data2()
    {
        return m_pTest->data2;
    }

    Test& test() const // 该函数能被 const 和非 const 的 Proxy 对象所调用。
    {
        return *m_pTest;
    }

    bool operator <(const TestProxy& rhs)
    {
        return test() < rhs.test();
    }

    bool operator >(const TestProxy& rhs)
    {
        return test() > rhs.test();
    }

    bool operator <=(const TestProxy& rhs)
    {
        return test() <= rhs.test();
    }

    bool operator >=(const TestProxy& rhs)
    {
        return test() >= rhs.test();
    }

    // 赋值，传参是被代理的类，因为对代理操作本意就是想对被代理的类操作
    // 返回值也是 被代理的类的对象，并且还是传参本身
    Test& operator =(Test& test)
    {
        m_pTest = &test;
        return test;
    }
};

Test t[1000];       // 构造 1000 个 Test 对象（大对象）
TestProxy pt[1000]; // 构造 1000 个 Test 的代理类对象（小对象）

int main()
{
    for(int i=0; i<1000; i++)
    {
        t[i].id = i;
        pt[i] = t[i];  // 用 pt 来代理 t 调用 TestProxy 类的赋值运算符
    }

    // 测试排序大对象（时间花在大对象的交换上）
    // 因为前面 id 是升序赋值的,所以升序排序测试用时间为 0 注意用降序才能对比效率
    clock_t begin = clock();  // 滴答数

    Sort::bubbleSort(t, sizeof(t)/sizeof(t[0]), false); // 不用代理直接冒泡降序交换
    clock_t end = clock();

    cout <<"Time elapse: " << end - begin << endl;

    // 测试排序代理对象（代理类比较小，交换花费的时间少）
    // 注意,只排序代理类的数据,而并不对被代理的数据进行真正的排序,所以速度快
    // 因为上面已经降序排序了,所以这里用升序 才能对比效率
    begin = clock();

    Sort::bubbleSort(pt, sizeof(pt)/sizeof(pt[0]), true); // 用代理直接冒泡升序交换

    end = clock();
    cout <<"Time elapse: " << end - begin << endl;

    for(int i=0; i<1000; i++)
    {
        cout << t[i].id << " " << pt[i].id() << endl;
    }

    return 0;
}
/* 运行结果
Time elapse: 850
Time elapse: 15 <==（与上面时间对比,效率提升了 56 倍）
999 0
998 1
...
0 999
*/
