// main.cpp StaticList类和DynamicList类的使用示例
#include <iostream>
#include "StaticList.h"
#include "DynamicList.h"

using namespace std;
using namespace WoodLib;


int main()
{
    // 没有将 List 类的拷贝构造和赋值 不定义之前运行这个部分；
#if 0
    //StaticList<int, 5> l;
    DynamicList<int> d1(5);
    DynamicList<int> d2(d1);

    for(int i=0; i<d1.capacity(); i++)
    {
        d1.insert(0, i);
        d2.insert(0, i*i);
    }

    for(int i=0; i<d1.length(); i++)
    {
        cout << d1[i] << " ";  // 这里实际打印出的是d2的内容
    }

    cout << endl;

    StaticList<int*, 5> s1;  // 存储指针类型
    StaticList<int*, 5> s2;

    for(int i=0; i<s1.capacity(); i++)
    {
        s1.insert(0, new int(i));
    }

    s2 = s1;

    for(int i=0; i<d1.length(); i++)
    {
        delete s1[i];
        delete s2[i];   // 这里会造成双重释放
    }
#endif

#if 0
    DynamicList<int> d1(5);
    DynamicList<int> d2(d1);   // 会去调用基类的 拷贝构造，但发现只有声明没有定义
    DynamicList<int> d3(5);

    d3 = d1;                   // 会去调用基类的 赋值函数，但发现只有声明没有定义

    // 线性表是个容器类，对比生活中的例子，我兜里有100块钱，
    // 复制/赋值就使得第二个兜里也有100元？？？
    // 这显然是不合理的，将这种思想平移到程序编码中，所以就
    // 采用这种在基类中对拷贝构造和赋值只声明不定义，使得所有
    // 派生类在发生拷贝构造和赋值行为时就编译报错不让通过！
#endif

    DynamicList<int> d1(5);

    for(int i=0; i<d1.capacity(); i++)
    {
        d1.insert(i);
    }

    for(int i=0; i<d1.length(); i++)
    {
        cout << d1[i] << " ";
    }

    cout << endl;

    return 0;
}



