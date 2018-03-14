// main.cpp  冒泡排序、希尔排序使用示例
#include <iostream>
#include "Sort.h"

using namespace std;
using namespace WoodLib;

int main()
{
    int array1[] = {8, 1, 0, 10, 99, 55, 12, 16};
    int len1 = sizeof(array1) / sizeof(array1[0]);

    Sort::bubbleSort(array1, len1);   // static成员函数直接通过类名调用

    for(int i=0; i<len1; i++)
    {
        cout << array1[i] << " ";
    }

    cout << endl;

    int array2[] = {8, 1, 0, 10, 99, 55, 12, 16};
    int len2 = sizeof(array2) / sizeof(array2[0]);

    Sort::shellSort(array2, len2, false);

    for(int i=0; i<len2; i++)
    {
        cout << array2[i] << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
0 1 8 10 12 16 55 99
99 55 16 12 10 8 1 0
*/
