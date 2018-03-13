// main.cpp  排序基本概念
#include <iostream>
#include "Object.h"

using namespace std;
using namespace WoodLib;

// 多关键字比较
struct Test : public Object
{
public:
    int key1;
    int key2;

    Test(int k1, int k2)
    {
        key1 = k1;
        key2 = k2;
    }

    bool operator ==(const Test& t)
    {
        return (key1 == t.key1) && (key2 == t.key2);
    }

    bool operator !=(const Test& t)
    {
        return !(*this == t);
    }

    bool operator <(const Test& t)
    {
        // 注意两种情况，用“||” 连接
        // key1 的比较优先于 key2 的比较（利用 || 的短路法则）,这就是多关键字的比较
        return (key1 < t.key1) || ((key1 == t.key1) && (key2 < t.key2));
    }

    bool operator >=(const Test& t)
    {
        return !(*this < t);
    }

    bool operator >(const Test& t)
    {
        // 注意两种情况，用“||” 连接
        // key1 的比较优先于 key2 的比较（利用 || 的短路法则）,这就是多关键字的比较
        return (key1 > t.key1) || ((key1 == t.key1) && (key2 > t.key2));
    }

    bool operator <=(const Test& t)
    {
        return !(*this > t);
    }
};

int main()
{
    Test t1(3, 4);
    Test t2(2, 5);
    Test t3(3, 5);

    cout << (t1 > t2) << endl;  // 输出： 1
    cout << (t1 < t3) << endl;  // 输出： 1

    return 0;
}
/* 运行结果
1
1
*/
