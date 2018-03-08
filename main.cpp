// main.cpp 循环单链表解决约瑟夫环问题
#include <iostream>
#include "DualLinkList.h"

using namespace std;
using namespace WoodLib;

int main()
{
    DualLinkList<int> d1;

    for(int i=0; i<5; i++)
    {
        d1.insert(i);
        d1.insert(5);
    }

    for(d1.move(0); !d1.isEnd(); d1.next())
    {
        cout << d1.current() << " ";
    }

    cout << endl;
    // 逆向访问链表
    // 因为首结点的 prev 指针 和 尾结点的 next 指针都指向 NULL
    // 所以可以都用!dl.end()作为循环退出条件的判断
    for(d1.move(d1.length()-1); !d1.isEnd(); d1.pre())
    {
        cout << d1.current() << " ";
    }

    cout << endl;

    // 删除值为 5 的元素
    d1.move(d1.length() - 1);
    while(!d1.isEnd())
    {
        if( 5 == d1.current() )
        {
            cout << d1.current() << " ";
            d1.remove(d1.find(d1.current()));
        }
        else  // 因为 每进remove()一次就有对m_current指针修正一次
        {
            d1.pre();
        }
    }

    cout << endl;

    for(d1.move(0); !d1.isEnd(); d1.next())
    {
        cout << d1.current() << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
0 5 1 5 2 5 3 5 4 5
5 4 5 3 5 2 5 1 5 0
5 5 5 5 5
0 1 2 3 4
*/
