// Graph.h 图的抽象类
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Object.h"
#include "SharedPointer.h"
#include "Array.h"

namespace WoodLib
{

// V 为顶点的数据类型，E 为边的数据类型
template <typename V, typename E>
class Graph : public Object
{
public:
    virtual V getVertex(int i) = 0;                              // 获取顶点i的值
    virtual bool getVertex(int i, V& value) = 0;                 // 获取顶点i的值
    virtual bool setVertex(int i, const V& value) = 0;           // 设置顶点i的值

    // 获取顶点 i 的邻接顶点
    virtual SharedPointer< Array<int> > getAdjacent(int i) = 0;

    // 参数 i 为起点，j为终点，value为边（权值）
    virtual E getEdge(int i, int j) = 0;                          // 获取边(i, j)的值
    virtual bool getEdge(int i, int j, E& value) = 0;             // 获取边(i, j)的值
    virtual bool setEdge(int i, int j, const E& value) = 0;       // 设置边(i, j)的值
    virtual bool removeEdge(int i, int j) = 0;                    // 删除边(i, j)

    virtual int vCount() = 0;    // 获取顶点的数量
    virtual int eCount() = 0;    // 获取边的数量

    virtual int OD(int i) = 0;   // 获取顶点 i 的出度
    virtual int ID(int i) = 0;   // 获取顶点 i 的入度
    virtual int TD(int i)        // 获取顶点 i 的度
    {
        return ID(i) + OD(i);
    }
};

}

#endif
