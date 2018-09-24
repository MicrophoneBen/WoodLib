// MatrixGraph.h 邻接矩阵结构图的类模板
#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace WoodLib
{
// N为图顶点个数，V 为顶点的数据类型，E 为边的数据类型
template <int N, typename V, typename E>
class MatrixGraph : public Graph<V, E>
{
private:
    V* m_vertexes[N];    // 顶点数组
    E* m_edges[N][N];    // 邻接矩阵，用于表示边的权值，当元素值为 NULL 时表示不存在
    int m_eCount;

public:
    MatrixGraph()
    {
        m_eCount = 0;

        for(int i=0; i<vCount(); i++)
        {
            m_vertexes[i] = NULL;

            for(int j=0; j<vCount(); j++)
            {
                m_edges[i][j] = NULL;
            }
        }
    }

    ~MatrixGraph()
    {
        for(int i=0; i<vCount(); i++)
        {
            delete m_vertexes[i];

            for(int j=0; j<vCount(); j++)
            {
                delete m_edges[i][j];
            }
        }

        m_eCount = 0;
    }

    V getVertex(int i)                              // 获取顶点i的值
    {
        V ret;

        if( !getVertex(i, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "index i is invalid ...");
        }

        return ret;
    }

    bool getVertex(int i, V& value)                 // 获取顶点i的值
    {
        bool ret = ((0 <= i) && (i < vCount()));

        if( ret )
        {
            if(m_vertexes[i] != NULL)
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "No value assigned to this vertex ...");
            }
        }

        return ret;
    }

    bool setVertex(int i, const V& value)           // 设置顶点i的值
    {
        bool ret = ((0 <= i) && (i < vCount()));

        if( ret )
        {
            /*

            // 异常不安全代码
            if(NULL == m_vertexes[i])
            {
                m_vertexes[i] = new V;
            }

            if(m_vertexes[i] != NULL)
            {
                *(m_vertexes[i]) = value;  // 就在这里可能产生异常不安全

                // V类型 赋值是完全 可能产生一个异常的，现假设这里赋值发生异常，就会在这里
                // 抛出一个异常，异常抛出就抛出呗，能有什么？？？ 但是这样产生异常造成的后果
                // 是，图中的这个顶点的数据肯定就发生了变化，变成什么了 -- 不可预期！
                // 这里抛出异常后，这个图对象就因为这个顶点数据不可预期（可能是一些完全非法
                // 数据）而导致整个图对象不能用了！这就是问题，这就是异常不安全！

                // 如何避免，先对一个中间数据操作，后面再进行指针的赋值！
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "No memory to store new vertex value ...");
            }

            */

            /* 异常安全代码 */
            V* data = m_vertexes[i];   // 保证异常安全

            if(NULL == data)
            {
                data = new V;
            }

            if(data != NULL)
            {
                *data = value;
                // 特别注意理解：上面异常不安全导致的此顶点状态改变，只针对原来这个顶点为NULL
                // 的情况（即图中原来没有这样一个顶点），此时这里抛出异常， m_vertexex[i] 依旧
                // 为NULL，图状态不会受到影响!
                // 对原来就有这个顶点存在的图，此处抛出异常，这里这样处理也是无法避免的，
                // *data 与 *(m_vertexex[i])是对同一个内存地址的解引用操作
                // *data 数据非法就是 *(m_vertexex[i]) 数据非法

                m_vertexes[i] = data;  // 上面没问题，这里是内置类型指针间的赋值肯定不会出问题了
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "No memory to store new vertex value ...");
            }
        }
        else
        {
            // 设置顶点数据时常常没有判断返回值，所以这个异常很有必要抛出
            THROW_EXCEPTION(InvalidParameterException, "index i is invalid ...");
        }

        return ret;
    }

    // 判断图中顶点i到顶点j是否邻接
    bool isAdjacent(int i, int j)
    {
        return  ((0 <= i) && (i < vCount())) &&
                ((0 <= j) && (j < vCount())) &&
                (m_edges[i][j] != NULL);
    }

    // 获取顶点 i 的邻接顶点
    SharedPointer< Array<int> > getAdjacent(int i)
    {
        // 动态数组用来保存邻接顶点的
        DynamicArray<int>* ret = NULL;

        if((0 <= i) && (i < vCount()))
        {
            int size = 0;   // 用来申请动态数组的大小

            // 统计顶点i的邻接顶点的个数
            for(int j=0; j<vCount(); j++)
            {
                if(m_edges[i][j] != NULL)
                {
                    ++size;
                }
            }

            ret = new DynamicArray<int>(size);
            if( ret != NULL )
            {
                for(int j=0,k=0; j<vCount(); j++)
                {
                    // 找到i的邻接顶点，即第i行不为NULL的顶点
                    if(m_edges[i][j] != NULL)
                    {
                        ret->set(k++, j);   // 记录邻接顶点标号
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "No memory to create return object ...");
            }
        }
        else
        {
            // 这个函数的使用场景也常常没有判断返回值，所以这个异常很有必要抛出
            THROW_EXCEPTION(InvalidParameterException, "index i is invalid ...");
        }

        return ret;
    }

    // 参数 i 为起点，j为终点，value为边（权值）
    E getEdge(int i, int j)                          // 获取边(i, j)的值
    {
        E ret;

        if( !getEdge(i, j, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "index i or j is invalid ...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E& value)             // 获取边(i, j)的值
    {
        bool ret = ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()));

        if( ret )
        {
            if(m_edges[i][j] != NULL)
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
            }
        }

        // 这个返回为NULL的函数外部一般不直接调用，而是由上面函数调用，故这个异常就交由上面重载函数了
        // 既然这样，这类似的函数是不是放入private充当类内部的功能函数更好 --- 后面优化！！！

        return ret;
    }

    bool setEdge(int i, int j, const E& value)       // 设置边(i, j)的值
    {
        bool ret = ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()));

        if( ret )
        {
            E* data = m_edges[i][j];

            if(NULL == data)
            {
                data = new E;

                if(NULL != data)
                {
                    // 这样处理异常安全的场景同上
                    *data = value;
                    m_edges[i][j] = data;
                    ++m_eCount;
                }
                else
                {
                    THROW_EXCEPTION(NotEnoughMemoryException, "No memory to store new edge value ...");
                }
            }
            else
            {
                *data = value;
            }
        }
        else
        {
            // 这个函数的使用场景也常常没有判断返回值，所以这个异常很有必要抛出
            THROW_EXCEPTION(InvalidParameterException, "index i or j is invalid ...");
        }

        return ret;
    }

    bool removeEdge(int i, int j)                    // 删除边(i, j)
    {
        bool ret = ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()));

        if( ret )
        {
            E* toDel = m_edges[i][j];

            if(toDel != NULL)
            {
                delete toDel;       // 用toDel就是避免这里的异常不安全给图对象带来的影响的
                m_edges[i][j] = NULL;

                --m_eCount;
            }
            else
            {
                // 没有边，抛出操作异常
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
            }
        }
        else
        {
            // 这个函数的使用场景也常常没有判断返回值，所以这个异常很有必要抛出
            THROW_EXCEPTION(InvalidParameterException, "index i or j is invalid ...");
        }

        return ret;
    }

    int vCount()    // 获取顶点的数量
    {
        return N;
    }

    int eCount()    // 获取边的数量
    {
        return m_eCount;
    }

    int OD(int i)   // 获取顶点 i 的出度
    {
        int ret = 0;

        if((0 <= i) && (i < vCount()))
        {
            for(int j=0; j<vCount(); j++)
            {
                // 邻接矩阵中第 i 行不为NULL 的元素的个数
                if(m_edges[i][j] != NULL)
                {
                    ++ret;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "index i is invalid ...");
        }

        return ret;
    }

    int ID(int i)   // 获取顶点 i 的入度
    {
        int ret = 0;

        if((0 <= i) && (i < vCount()))
        {
            for(int j=0; j<vCount(); j++)
            {
                // 邻接矩阵中第 i 列不为NULL 的元素的个数
                if(m_edges[j][i] != NULL)
                {
                    ++ret;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "index i is invalid ...");
        }

        return ret;
    }
};

}

#endif

