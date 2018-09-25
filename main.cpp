// main.cpp  图的最小生成树kruskal算法设计
// 与上节代码测试一样，只需将对 prim 函数的调用改为 kruskal
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

    // 有向图的方式构造无向图模型
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
    cout <<"eCount: " << g.eCount() / 2 << endl;


    SharedPointer< Array< Edge<int> > > sa = g.krusal();       //最小生成树
    //SharedPointer< Array< Edge<int> > > sa = g.krusal(false);  //最大生成树


    int w = 0;
    for(int i=0; i<sa->length(); i++)
    {
        Edge<int>& edge = (*sa)[i];
        w += edge.data;
        cout << edge.begin << "->" << edge.end << ": "<< edge.data << endl;
    }

    cout << "Weight: " << w << endl;

    return 0;
}
/* 运行结果
// 最小生成树结果：
vCount: 9
eCount: 15
4->7: 7
2->8: 8
0->1: 10
0->5: 11
1->8: 12
1->6: 16
3->7: 16
6->7: 19
Weight: 99

// 最大生成树结果：
vCount: 9
eCount: 15
4->5: 26
3->6: 24
2->3: 22
3->8: 21
3->4: 20
6->7: 19
1->2: 18
0->5: 11
Weight: 161
*/
