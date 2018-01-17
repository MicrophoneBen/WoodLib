#include <iostream>
#include "SmartPointer.h"

using namespace std;
using namespace WoodLib;  // 使用我的库

class Test
{
public:
    Test()
    {
        cout << "Test" << endl;
    }

    Test(int i, int m= 1)
    {
        cout << i << endl;
    }

    ~Test()
    {
        cout << "~Test" << endl;
    }
};

int main()
{
    SmartPointer<Test> l_sp1 = new Test();

    cout << l_sp1.isNull() << endl << endl;

    SmartPointer<Test> l_sp2(l_sp1);

    cout << l_sp1.isNull() << endl;
    cout << l_sp2.isNull() << endl << endl;

    SmartPointer<Test> l_sp3;

    l_sp3 = l_sp2;

    cout << l_sp1.isNull() << endl;
    cout << l_sp2.isNull() << endl;
    cout << l_sp3.isNull() << endl;

    return 0;
}
/* 运行结果
Test
SmartPointer()
0

1
0

SmartPointer()
1
1
0
~SmartPointer()
~Test
~SmartPointer()
~SmartPointer()
*/
