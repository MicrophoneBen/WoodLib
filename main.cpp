// main.cpp  排序类与数组类的关系，数组类中直接调用排序方法对数组内元素进行排序
#include <iostream>
#include "StaticArray.h"
#include "DynamicArray.h"

using namespace std;
using namespace WoodLib;

int main()
{
    // 静态数组类对象
    StaticArray<int, 5> s_array;

    for(int i=0; i<s_array.length(); i++)
    {
        s_array[i] = rand() % 100;   // 产生100以内的随机数
    }

    for(int i=0; i<s_array.length(); i++)
    {
        cout << s_array[i] << " ";
    }

    cout << endl;

    s_array.bubbleSort();    // 冒泡排序（顺序）

    for(int i=0; i<s_array.length(); i++)
    {
        cout << s_array[i] << " ";
    }

    cout << endl;

    s_array.quickSort(false);  // 快速排序（逆序）

    for(int i=0; i<s_array.length(); i++)
    {
        cout << s_array[i] << " ";
    }

    cout << endl << endl;

    // 动态数组类对象
    DynamicArray<int> d_array(5);

    for(int i=0; i<d_array.length(); i++)
    {
        d_array[i] = rand() % 100;
    }

    for(int i=0; i<d_array.length(); i++)
    {
        cout << d_array[i] << " ";
    }

    cout << endl;

    d_array.insertSort();    // 插入排序（顺序）

    for(int i=0; i<d_array.length(); i++)
    {
        cout << d_array[i] << " ";
    }

    cout << endl;

    d_array.mergeSort(false);  // 归并排序（逆序）

    for(int i=0; i<d_array.length(); i++)
    {
        cout << d_array[i] << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
41 67 34 0 69
0 34 41 67 69
69 67 41 34 0

24 78 58 62 64
24 58 62 64 78
78 64 62 58 24
*/
