// main.cpp  邻接链表结构的图类模板
#include <iostream>
#include "ListGraph.h"
#include <exception>

using namespace std;
using namespace WoodLib;

int main()
{
    // 测试的图为前面“ 邻接链表示例 2” 的有向图
    ListGraph<char, int> g;

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.addVertex('F');

    for(int i=0; i<g.vCount(); i++)
    {
        cout << i <<": " << g.getVertex(i) << endl;
    }

    cout << "Delete Vertex F :" << endl;
    g.removeVertex();      // 将最后一个顶点 F 删除

    for(int i=0; i<g.vCount(); i++)
    {
        cout << i <<": " << g.getVertex(i) << endl;
    }

    g.setEdge(0, 1, 5);    // 参数分别为起点、终点和边的权值
    g.setEdge(0, 3, 8);
    g.setEdge(1, 2, 8);
    g.setEdge(2, 3, 2);
    g.setEdge(3, 1, 9);

    cout <<"vCount: " << g.vCount() << endl;
    cout <<"eCount: " << g.eCount() << endl;
    cout <<"ID(1): " << g.ID(1) << endl;
    cout <<"OD(1): " << g.OD(1) << endl;
    cout <<"TD(1): " << g.TD(1) << endl;

    cout << "Weight(0, 1): " << g.getEdge(0, 1) << endl;
    cout << "Weight(0, 3): " << g.getEdge(0, 3) << endl;
    cout << "Weight(1, 2): " << g.getEdge(1, 2) << endl;
    cout << "Weight(2, 3): " << g.getEdge(2, 3) << endl;
    cout << "Weight(3, 1): " << g.getEdge(3, 1) << endl;

    // 获取顶点 0 的邻接顶点
    SharedPointer<Array<int> > aj = g.getAdjacent(0);

    for(int i=0; i<aj->length(); i++)
    {
        cout << (*aj)[i] << " ";
    }
    cout << endl;

    cout <<"Delete Edge 0->1 : " << endl;
    g.removeEdge(0, 1);
    // cout << "Weight(0, 1): " << g.getEdge(0, 1) << endl; //抛异常，因为该条边被删除了！
    cout <<"eCount: " << g.eCount() << endl;
    // 再获取顶点 0 的邻接顶点
    aj = g.getAdjacent(0);

    for(int i=0; i<aj->length(); i++)
    {
        cout << (*aj)[i] << " ";
    }
    cout << endl;

    // 将上面删除的边又设置一个新值
    g.setEdge(0, 1, 100);
    cout << "Weight(0, 1): " << g.getEdge(0, 1) << endl;

    // 重新设置顶点值
    g.setVertex(0, 'F');
    cout << "v(0): " << g.getVertex(0) << endl;

    // 删除最近加入的顶点（编号最大的 3 号顶点，注意会同时删除与该顶点相关的边）
    g.removeVertex();
    cout <<"eCount: " << g.eCount() << endl;

    return 0;
}
/* 运行结果
0: A
1: B
2: C
3: D
4: F
Delete Vertex F :
0: A
1: B
2: C
3: D
vCount: 4
eCount: 5
ID(1): 2
OD(1): 1
TD(1): 3
Weight(0, 1): 5
Weight(0, 3): 8
Weight(1, 2): 8
Weight(2, 3): 2
Weight(3, 1): 9
1 3                // 顶点0的邻接顶点
Delete Edge 0->1 :
eCount: 4
3                  // 删除边0->1后顶点0的邻接顶点
Weight(0, 1): 100
v(0): F
eCount: 2
*/
