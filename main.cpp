// main.cpp  图的运用：最长不下降序列
#include <iostream>
#include "ListGraph.h"

using namespace std;
using namespace WoodLib;

// 以图g中的v顶点作为起始顶点，寻找最多顶点路径,将相应的结果保存在辅助数组中
// count 记录顶点的最多顶点数, count[i] 表示顶点i的最多顶点路径树为count[i]
// path 记录最多顶点路径上经过的第一个顶点
// mark 记录最多顶点路径是否已经找到
// 返回值时最多顶点路径的顶点数
int search_max_path(Graph<int, int>& g, int v, Array<int>& count, Array< LinkList<int>* >& path, Array<bool>& mark)
{
    int ret = 0;   // 返回值，返回顶点最多路径的顶点数

    SharedPointer< Array<int> > aj = g.getAdjacent(v);

    for(int i=0; i<aj->length(); i++)
    {
        int num = 0;

        // 邻接顶点 (*aj)[i] 还未找到最多顶点路径
        if( !mark[(*aj)[i]] )
        {
            // 递归查找最多顶点路径
            num = search_max_path(g, (*aj)[i], count, path, mark);
        }
        else   // 已经找到最多顶点路径，直接取顶点数
        {
            num = count[(*aj)[i]];
        }

        // 邻接顶点 (*aj)[i] 的最多顶点数比ret还多
        if( ret < num )
        {
            ret = num;
        }
    }

    // 判断v有没有多个局部顶点最多路径
    for(int i=0; i<aj->length(); i++)
    {
        // 有多个局部顶点最多路径
        if( ret == count[(*aj)[i]] )
        {
            // 将每一个后继结点都加入到path数组的链表中
            path[v]->insert((*aj)[i]);
        }
    }

    ret++;

    count[v] = ret;  // 更新最多顶点数
    mark[v] = true;  // 标记v表示已找到v为顶点的最多顶点路径

    return ret;
}

// 将长度为len的数列a，转换为图返回
SharedPointer< Graph<int, int> > create_graph(int* a, int len)
{
    ListGraph<int, int>* ret = new ListGraph<int, int>(len);

    // 设置顶点与树列一一对应
    for(int i=0; i<len; i++)
    {
        ret->setVertex(i, a[i]);
    }

    // 不下降两个顶点间设置边
    for(int i=0; i<len; i++)
    {
        for(int j=i+1; j<len; j++)
        {
            if(a[i] <= a[j])
            {
                ret->setEdge(i, j, 1);
            }
        }
    }

    return ret;
}

// 初始化原材料
void init_array(Array<int>& count, Array< LinkList<int>* >& path, Array<bool>& mark)
{
    for(int i=0; i<count.length(); i++)
    {
        count[i] = 0;
    }

    for(int i=0; i<path.length(); i++)
    {
        path[i] = new LinkList<int>();
    }

    for(int i=0; i<mark.length(); i++)
    {
        mark[i] = false;
    }
}

// 递归函数：用来打印输出的
void print_path(Graph<int, int>& g, int v, Array< LinkList<int>* >& path, LinkList<int>& cp)
{
    cp.insert(v);   // 将起始顶点编号v插入链表尾部

    // 当前顶点对应的链表中有保存其他顶点编号
    if(path[v]->length() >0)
    {
        // 将保存的顶点取出来找路径，所以需要遍历链表
        for(path[v]->move(0); !path[v]->isEnd(); path[v]->next())
        {
            // 打印这个顶点，递归调用自己来打印
            print_path(g, path[v]->current(), path, cp);
        }
    }
    else   // 递归出口：当前打印的顶点所对应的链表里面没有保存其他顶点号
    {      // 当前打印的顶点就是最后一个顶点了
        // 开始具体的打印，打印cp链表里面所保存的顶点号对应的元素了
        cout << "Element : ";

        // 遍历cp链表，将里面的元素打印出来
        for(cp.move(0); !cp.isEnd(); cp.next())
        {
            cout << g.getVertex(cp.current()) << " ";
        }

        cout << endl;
    }

    // 打印一次必定要删除最近插入的顶点
    cp.remove(cp.length()-1);
}

// 打印输出最长不下降序列
void print_max_path(Graph<int, int>& g, Array<int>& count, Array< LinkList<int>* >& path)
{
    int max = 0;
    LinkList<int> cp;    // 用一个链表保存路径上的顶点编号

    for(int i=0; i<count.length(); i++)
    {
        // 找出最大顶点数
        if(max < count[i])
        {
            max = count[i];
        }
    }

    // 最多顶点路径的 顶点数量
    cout << "Len : " << max << endl;

    for(int i=0; i<count.length(); i++)
    {
        // 找到最多顶点路径的其实 顶点i
        if(max == count[i])
        {
            print_path(g, i, path, cp);
        }
    }
}


void search_max_path(Graph<int, int> &g, Array<int> &count, Array< LinkList<int>* > &path, Array<bool> &mark)
{
    for(int i=0; i<g.vCount(); i++)
    {
        if( !mark[i] )
        {
            search_max_path(g, i, count, path, mark);
        }
    }
}

void solution(int* a, int len)
{
    DynamicArray<int> count(len);
    // 用链表保存是为了对这种数列也有效：{1, 3, 5, 4}
    DynamicArray< LinkList<int>* > path(len);
    DynamicArray<bool> mark(len);
    SharedPointer< Graph<int, int> > g;

    g = create_graph(a, len);

    init_array(count, path, mark);
    search_max_path(*g, count, path, mark);
    print_max_path(*g, count, path);
}

int main()
{
    int  a1[] = {1, 3, 4, 2, 5};
    int  a2[] = {10, 30, 50, 1, 3, 5};
    int  a3[] = {5, 3, 2, 1, 0};
    int  a4[] = {1, 2, 3, 4, 5};
    int  a5[] = {1, 3, 5, 4};
    int  a6[] = {2, 1, 3, 5, 4};

    cout << "============ a1 ================" << endl;
    solution(a1, sizeof(a1)/sizeof(*a1));
    cout << "============ a2 ================" << endl;
    solution(a2, sizeof(a2)/sizeof(*a2));
    cout << "============ a3 ================" << endl;
    solution(a3, sizeof(a3)/sizeof(*a3));
    cout << "============ a4 ================" << endl;
    solution(a4, sizeof(a4)/sizeof(*a4));
    cout << "============ a5 ================" << endl;
    solution(a5, sizeof(a5)/sizeof(*a5));
    cout << "============ a6 ================" << endl;
    solution(a6, sizeof(a6)/sizeof(*a6));

    return 0;
}
/* 运行结果
============ a1 ================
Len : 4
Element : 1 3 4 5
============ a2 ================
Len : 3
Element : 10 30 50
Element : 1 3 5
============ a3 ================
Len : 1
Element : 5
Element : 3
Element : 2
Element : 1
Element : 0
============ a4 ================
Len : 5
Element : 1 2 3 4 5
============ a5 ================
Len : 3
Element : 1 3 5
Element : 1 3 4
============ a6 ================
Len : 3
Element : 2 3 5
Element : 2 3 4
Element : 1 3 5
Element : 1 3 4
*/
