// main.cpp  String 字符串类使用示例
#include <iostream>
#include "WoodString.h"

using namespace std;
using namespace WoodLib;

void test1()
{
    cout << "test1() begin..." << endl;

    String s;

    s = 'L';

    cout << s.str() << endl;         // L
    cout << s.length() << endl;      // 1
    cout << (s == 'L') << endl;      // 1
    cout << (s > "M") << endl;       // 0 字典顺序比较

    s += "i yao";

    cout << s.str() << endl;         // Li yao
    cout << s.length() << endl;      // 6
    cout << (s == "Li yao") << endl; // 1

    cout << "test1() end..." << endl;
}

void test2()
{
    cout << "test2() begin..." << endl;

    String a[] = {"E", "D", "C", "B", "A"};
    String min = a[0];

    // 找出最小的字符
    for(unsigned int i=0; i<sizeof(a)/sizeof(a[0]); i++)
    {
        if( min > a[i] )
        {
            min = a[i];
        }
    }

    cout << min.str() << endl;   // A

    cout << "test2() end..." << endl;
}

int main()
{
    test1();
    test2();

    return 0;
}
/* 运行结果
test1() begin...
L
1
1
0
Li yao
6
1
test1() end...
test2() begin...
A
test2() end...
*/
