// main.cpp StaticArray类和DynamicArray类的使用示例
#include <iostream>
#include "DynamicArray.h"
#include "StaticArray.h"

using namespace std;
using namespace WoodLib;

int main()
{
    DynamicArray<int> d1(5);

    cout << "d1.length() = " << d1.length() << endl;

    for(int i=0; i<d1.length(); i++)
    {
        d1[i] = i;
    }

    for(int i=0; i<d1.length(); i++)
    {
        cout << d1[i] << " ";
    }

    cout << endl;

    try
    {
        d1[8] = 1;
    }
    catch(const IndexOutOfBoundsException& e)
    {
        cout << e.getMessage() << endl;
        cout << e.getLocation() << endl;

        d1.resize(10);
        d1[8] = 1;
    }

    cout << "d1.length() = " << d1.length() << endl;

    for(int i=0; i<d1.length(); i++)
    {
        cout << d1[i] << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
d1.length() = 5
0 1 2 3 4
Parameter index is invalid ...
..\Array.h:61
Object::~Object()
d1.length() = 10
0 1 2 3 4 64644 41405056 41353408 1 0
Object::~Object()
*/



