// DualCircleLinkList 循环双向链表类使用示例
#include <iostream>
#include "DualCircleLinkList.h"

using namespace std;
using namespace WoodLib;

int main()
{
    DualCircleLinkList<int> dl;

    for(int i=0; i<5; i++)
    {
        dl.insert(i);
        dl.insert(5);
    }

    cout << "begin ..." << endl;

    dl.move(dl.length()-1);    // 游标移动到链表尾部

    while( dl.find(5) != -1 )  // 直到dl中没有值为 5 的结点
    {
        if( dl.current() == 5 )
        {
            cout << dl.current() << " ";
            dl.remove(dl.find(dl.current()));
        }
        else
        {
            dl.pre(); // 逆序移动游标
        }
    }

    cout << endl << "end ..." << endl;

    // 会循环打印 10 个元素 注意： 10>dl.length()
    for(int i=0; i<10; i++)
    {
        cout << dl.get(i) << " ";
    }

    cout << endl;

    // 以下代码会死循环，因为这是双向循环链表
    // for(dl.move(0); !dl.end(0); dl.next())
    // {
    //    cout << dl.current() << endl;
    // }

    return 0;
}
/* 运行结果
begin ...
5 5 5 5 5
end ...
0 1 2 3 4 0 1 2 3 4
*/
