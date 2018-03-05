// main.cpp StaticLink类 的使用示例
#include <iostream>
#include "StaticLink.h"
#include "Exception.h"

using namespace std;
using namespace WoodLib;

int main()
{
    StaticLink<int, 5> list;

    for(int i=0; i < list.capacity(); i++)
    {
        list.insert(0,i);
    }

    try
    {
        // 因为上面定义的 list 最大预留空间是5,上面也已经使用 5 个结点了所以
        // 下面这个自然就没有预留空间可以插入这个结点了,程序就会出现异常
        // 异常分析：继承而来的 insert() -> Node* node = createNode();
        // -> 调用 StaticLinkList::createNode()(虚函数多态) ->
        // 查询到 m_used[N]没有空余空间,返回 NULL -> insert()走 else 分支抛出异常
        // 这里就很好的解释了上一节课中最后要封装 createNode 和 destroyNode 函数了
        list.insert(0, 100);
    }
    catch(const Exception& e)
    {
        cout << e.getMessage() << endl;
        cout << e.getLocation() << endl;
    }


    for(list.move(0); !list.isEnd(); list.next())
    {
        cout << list.current() << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
No memrey to insert new element ...
..\LinkList.h:109
4 3 2 1 0
*/



