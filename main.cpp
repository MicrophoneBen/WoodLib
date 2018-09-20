// main.cpp  邻接矩阵结构的图类模板
#include <iostream>
#include "MatrixGraph.h"

using namespace std;
using namespace WoodLib;

int main()
{
    // 测试的图为前面“邻接矩阵示例2”的有向图（边的权值被修改了）
    MatrixGraph<3, int, int> g;

    g.setEdge(0, 1, 1);   // 参数分别为起点、终点和边的权值
    g.setEdge(1, 0, 2);
    g.setEdge(1, 2, 3);

    // 图对象 g 的 顶点数、边数
    cout << "vCount: " << g.vCount() << endl;  // 3
    cout << "eCount: " << g.eCount() << endl;  // 3

    // 顶点1的度
    cout <<"ID(1): " << g.ID(1) << endl;       // 1
    cout <<"OD(1): " << g.OD(1) << endl;       // 2
    cout <<"TD(1): " << g.TD(1) << endl;       // 3

    // 边的权值
    cout << "Weight(0, 1): " << g.getEdge(0, 1) << endl;
    cout << "Weight(1, 0): " << g.getEdge(1, 0) << endl;
    cout << "Weight(1, 2): " << g.getEdge(1, 2) << endl;   // 是否可看做无向图

    // 获取顶点 1 的邻接顶点
    SharedPointer< Array<int> > aj = g.getAdjacent(1);
    for(int i=0; i<aj->length(); i++)
    {
        cout << (*aj)[i] << " ";    // 0 2
    }
    cout << endl;

    // 删除边测试
    cout <<"remove Edge test ... " << endl;
    g.removeEdge(1, 2);
    // cout << "Weight(1, 2): " << g.getEdge(1, 2) << endl;  // 抛异常，因为该条边被删除了！
    aj = g.getAdjacent(1);
    for(int i=0; i<aj->length(); i++)
    {
        cout << (*aj)[i] << " ";   // 0  因为删除了1->2的这条边
    }
    cout << endl;

    // 将删除的边又搭建起来
    g.setEdge(1, 2, 100);
    cout << "Weight(1, 2): " << g.getEdge(1, 2) << endl;  // 抛异常，因为该条边被删除了！
    aj = g.getAdjacent(1);
    for(int i=0; i<aj->length(); i++)
    {
        cout << (*aj)[i] << " ";   // 0  因为删除了1->2的这条边
    }
    cout << endl;

    // 设置顶点0的数据为 1000 -- 这个是这个顶点原始就没有数据（原始就为NULL）的情况
    g.setVertex(0, 1000);
    cout << "v(0): " << g.getVertex(0) << endl;

    // 设置顶点0的数据为 1000 -- 这个是这个顶点原始就有数据（原始不为NULL）的情况
    g.setVertex(0, 2000);
    cout << "v(0): " << g.getVertex(0) << endl;

    return 0;
}
/* 运行结果
vCount: 3
eCount: 3
ID(1): 1
OD(1): 2
TD(1): 3
Weight(0, 1): 1
Weight(1, 0): 2
Weight(1, 2): 3
0 2                   // 顶点 1 的邻接顶点: 0<->1  1->2
remove Edge test ...
0                     // 删除了 1->2 的这条边
Weight(1, 2): 100
0 2                   // 又添加 1->2 的这条边
v(0): 1000
v(0): 2000
*/
