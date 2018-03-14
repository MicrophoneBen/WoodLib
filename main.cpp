// main.cpp  归并排序、快速排序使用示例
#include <iostream>
#include "Sort.h"

using namespace std;
using namespace WoodLib;

int main()
{
    int array1[] = {8, 8, 16, 10, 99, 8, 8, 8};
    int len1 = sizeof(array1) / sizeof(array1[0]);

    Sort::quickSort(array1, len1);   // static成员函数直接通过类名调用

    for(int i=0; i<len1; i++)
    {
        cout << array1[i] << " ";
    }

    cout << endl;

    int array2[] = {8, 8, 16, 10, 99, 8, 8, 8};
    int len2 = sizeof(array2) / sizeof(array2[0]);

    Sort::quickSort(array2, len2, false);

    for(int i=0; i<len2; i++)
    {
        cout << array2[i] << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
8 8 8 8 8 10 16 99
99 16 10 8 8 8 8 8
*/
