// main.cpp  图的广度优先遍历算法测试
#include <iostream>
#include "ListGraph.h"
#include <exception>
#include "MatrixGraph.h"

using namespace std;
using namespace WoodLib;

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

    // 广度优先图遍历算法
    SharedPointer< Array<int> > sa = g.BFS(0);

    for(int i=0; i<sa->length(); i++)
    {
       cout << (*sa)[i] << " ";
    }
    cout << endl;

    for(int i=0; i<sa->length(); i++)
    {
       cout << g.getVertex((*sa)[i]) << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
vCount: 9
eCount: 30
0 1 5 2 6 8 4 3 7    // 图顶点编号
A B F C G I E D H    // 图顶点内的数据
*/
