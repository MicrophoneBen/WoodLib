// main.cpp  堆排序使用示例
#include <iostream>
#include "Sort.h"

using namespace std;
using namespace WoodLib;

int main()
{
    int array[] = {5, 4, 58, 56, 0, 12};

    Sort::Heap(array, sizeof(array)/sizeof(array[0]));

    for(unsigned int i=0; i<sizeof(array)/sizeof(array[0]); i++)
    {
        cout << array[i] << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
0 4 5 12 56 58
*/
