// main.cpp  图的最短路径 floyd 算法设计测试
#include <iostream>
#include "ListGraph.h"
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

    // 用有向图的构造方式构造无向图模型
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
    cout <<"eCount: " << g.eCount()/2 << endl;

    int begin = 0, end = 7;  // 起点和终点

    // 图的最短路径算法 floyd()
    SharedPointer<Array<int> > sa = g.floyd(begin, end, 65536);

    int w = 0;
    cout << begin << "->" << end << " shortest path: ";

    for(int i=0; i<sa->length(); i++)
    {
        int v = (*sa)[i];
        if(i>=1)
        {
            w += g.getEdge((*sa)[i-1],v);
        }
        cout << v << " " ;
    }
    cout <<endl;

    cout <<"Total weight: " << w << endl;

    return 0;
}
/* 运行结果
vCount: 9
eCount: 15
0->7 shortest path: 0 5 4 7   // V0->V7最短路径经过的顶点
Total weight: 44              // V0->V7最短路径权值
*/
