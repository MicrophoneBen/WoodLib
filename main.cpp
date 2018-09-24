// main.cpp  图的深度优先遍历算法测试
#include <iostream>
#include "ListGraph.h"
#include <exception>
#include "MatrixGraph.h"

using namespace std;
using namespace WoodLib;

// 递归版的深度优先遍历
template<typename V, typename E>
void DFS(Graph<V, E>&g ,int v, Array<bool>& visited)
{
    if((0<=v) && (v<g.vCount()))
    {
        cout << g.getVertex(v) << " ";    // 1. 访问顶点
        visited[v] = true;

        // 2. 获取v的邻接顶点
        SharedPointer<Array<int> > aj = g.getAdjacent(v);

        // 3. 以v的邻接顶点为起点，遍历未被访问过的子图。
        //    visited数组除了用于标志顶点是否被访问，也可以用于将未被访问过的
        //    顶点划分入一个子图。
        // 没有邻接顶点时为递归出口，此时 aj->length() = 0; for循环不执行
        for(int i=0; i<aj->length(); i++)
        {
            if(!visited[(*aj)[i]])
            {
                DFS(g, (*aj)[i], visited);
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Index v is invalid ...");
    }
}

template<typename V, typename E>
void DFS(Graph<V, E>&g ,int v)
{
    DynamicArray<bool> visited(g.vCount());

    for(int i=0; i<visited.length(); i++)
    {
        visited[i] = false;
    }

    DFS(g, v, visited);
}


int main()
{
    //MatrixGraph<9, char, int> g;
    ListGraph<char, int> g(9);

    const char* V = "ABCDEFGHI";

    for(int i=0; i<9; i++)
    {
       g.setVertex(i, V[i]);
    }

    g.setEdge(0, 1, 10);
    g.setEdge(0, 5, 11);
    g.setEdge(1, 2, 18);
    g.setEdge(1, 6, 16);
    g.setEdge(1, 8, 12);
    g.setEdge(2, 3, 22);
    g.setEdge(2, 8, 8);
    g.setEdge(3, 4, 20);
    g.setEdge(3, 6, 24);
    g.setEdge(3, 7, 16);
    g.setEdge(3, 8, 21);
    g.setEdge(4, 5, 26);
    g.setEdge(4, 7, 7);
    g.setEdge(5, 6, 17);
    g.setEdge(6, 7, 19);

    // 构建无向图，所以上面设置了(bigin, end)
    // 下面再用同样的权值设置一遍(end, begin)
    g.setEdge(1, 0, 10);
    g.setEdge(5, 0, 11);
    g.setEdge(2, 1, 18);
    g.setEdge(6, 1, 16);
    g.setEdge(8, 1, 12);
    g.setEdge(3, 2, 22);
    g.setEdge(8, 2, 8);
    g.setEdge(4, 3, 20);
    g.setEdge(6, 3, 24);
    g.setEdge(7, 3, 16);
    g.setEdge(8, 3, 21);
    g.setEdge(5, 4, 26);
    g.setEdge(7, 4, 7);
    g.setEdge(6, 5, 17);
    g.setEdge(7, 6, 19);


    cout <<"vCount: " << g.vCount()<< endl;
    cout <<"eCount: " << g.eCount() << endl;

    // 深度优先图遍历算法
    SharedPointer< Array<int> > sa = g.DFS(0);

    for(int i=0; i<sa->length(); i++)
    {
       cout << g.getVertex((*sa)[i]) << " ";
    }

    cout << endl;

    DFS(g, 0);   // 调用递归版本的深度优先遍历算法

    cout << endl;

    return 0;
}
/* 运行结果
vCount: 9
eCount: 30
A B C D E F G H I  // 图顶点内的数据 -- 非递归版本 链式栈的方式
A B C D E F G H I  // 图顶点内的数据 -- 递归版本
*/
