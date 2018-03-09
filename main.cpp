// StaticStack 基于顺序存储结构栈的使用示例
#include <iostream>
#include "StaticStack.h"

using namespace std;
using namespace WoodLib;

int main()
{
    StaticStack<int, 10> s1;

    cout << "s1.capacity() = " << s1.capacity() << endl;
    cout << "s1.size() = " << s1.size() << endl;

    try
    {
        s1.pop();  // 此时栈为空 出栈自然会抛出异常
    }
    catch(const Exception& e)
    {
        cout << e.getMessage() << endl;
        cout << e.getLocation() << endl;
    }

    cout << "s1.push: ";
    for(int i=0; i<s1.capacity(); i++)
    {
        cout << i*i << " ";
        s1.push(i*i);
    }

    cout << endl;

    cout << "s1.pop(): ";
    while(s1.size() > 0)
    {
        cout << s1.top() << " ";
        s1.pop();
    }

    cout << endl;

    return 0;
}
/* 运行结果
s1.capacity() = 10
s1.size() = 0
No element in current Stack ...
..\StaticStack.h:62
s1.push: 0 1 4 9 16 25 36 49 64 81
s1.pop(): 81 64 49 36 25 16 9 4 1 0
*/
