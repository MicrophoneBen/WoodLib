// ListGraph.h 邻接链表存储结构的图类模板
#ifndef _LISTGRAPH_H_
#define _LISTGRAPH_H_

#include "Graph.h"
#include "LinkList.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace WoodLib
{
// V 为顶点类型， E 为边类型
template <typename V, typename E>
class ListGraph : public Graph<V, E>
{
private:
    struct Vertex : public Object
    {
        V* data;                    // 顶点数据元素
        LinkList< Edge<E> > edge;   // 邻接于该顶点的边信息

        Vertex() : data(NULL) {}
    };

    LinkList<Vertex*> m_vertList;   // 邻接链表，存储指向顶点元素的指针

public:
    ListGraph(unsigned int n = 0)
    {
        for(unsigned int i=0; i<n; i++)
        {
            addVertex();
        }
    }

    // 增加新的顶点，返回顶点编号，尾部增加
    int addVertex()
    {
        int ret = -1;

        Vertex* v = new Vertex();
        if(v != NULL)
        {
            m_vertList.insert(v);          // 链表尾部插入节点
            ret = m_vertList.length() -1;  // 返回链表尾部节点的编号
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "No memory to create new vertex object ...");
        }

        return ret;
    }

    // 增加新顶点的同时附加数据，尾部增加
    int addVertex(const V& value)
    {
        int ret = addVertex();

        if(ret >= 0)
        {
            setVertex(ret, value);
        }

        return ret;
    }

    V getVertex(int i)                              // 获取顶点i的值
    {
        V ret;

        if(!getVertex(i, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return ret;
    }

    bool getVertex(int i, V& value)                 // 获取顶点i的值
    {
        bool ret = (0 <= i) && (i < vCount());

        if(ret)
        {
            Vertex* v = m_vertList.get(i);

            if(v->data != NULL)
            {
                value = *(v->data);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return ret;
    }

    bool setVertex(int i, const V& value)           // 设置顶点i的值
    {
        bool ret = (0 <= i) && (i < vCount());

        if(ret)
        {
            Vertex* v = m_vertList.get(i);

            V* data = v->data;   // 保证异常安全
            if(NULL == data)
            {
                data = new V();
            }

            if(data != NULL)
            {
                *data = value;
                v->data = data;
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "No memory to create new vertex value ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid ...");
        }

        return ret;
    }

    // 删除最近增加的顶点(最后一个顶点)
    void removeVertex()
    {
        // 邻接链表长度大于0，即有顶点
        if(m_vertList.length() > 0)
        {
            int index = m_vertList.length() -1;  // 最后顶点的编号
            Vertex* v = m_vertList.get(index);   // 最后顶点的指针

            // 从邻接链表中删除顶点
            if(m_vertList.remove(index))
            {
                // 遍历邻接链表，即遍历顶点，第一个 i 赋值利用了逗号表达式一语双关
                for(int i=(m_vertList.move(0), 0); !m_vertList.isEnd(); i++, m_vertList.next())
                {
                    // 查找各个顶点到这个删除顶点的边
                    int pos = m_vertList.current()->edge.find(Edge<E>(i, index));

                    // 查找顶点m_vertList.current()中，有起点为 i,终点为 index 的边
                    if(pos >= 0)
                    {
                        // 将这个节点从edge中移除，即删除查找到的边
                        m_vertList.current()->edge.remove(pos);
                    }
                }
            }

            delete v->data;    // 释放顶点数据指针所占的空间
            delete v;          // 释放顶点指针所占的空间
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No vertex in current graph ...");
        }

    }

    // 判断图中顶点i到顶点j是否邻接
    bool isAdjacent(int i, int j)
    {
        bool ret = (0 <= i) && (i < vCount()) &&
                   (0 <= j) && (j < vCount());

        if(ret)
        {
            Vertex* v = m_vertList.get(i);
            ret = ret && ( v->edge.find(Edge<E>(i, j)) >= 0);
        }

        return ret;
    }

    // 获取顶点 i 的邻接顶点
    SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* ret = NULL;

        if((0 <= i) && (i < vCount()))
        {
            Vertex* v = m_vertList.get(i);
            ret = new DynamicArray<int>(v->edge.length());

            if(ret != NULL)
            {
                for(int i=(v->edge.move(0), 0); !v->edge.isEnd(); v->edge.next(), i++)
                {
                    ret->set(i, v->edge.current().end);
                }
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "No memory to create ret object ...");
            }

            // 这里按从小到大排个序，因为每个顶点的邻接链表是元素是无序的
            ret->bubbleSort(true);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    // 参数 i 为起点，j为终点，value为边（权值）
    E getEdge(int i, int j)                          // 获取边(i, j)的值
    {
        E ret;

        if(!getEdge(i, j, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i or j is invalid ...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E& value)             // 获取边(i, j)的值
    {
        bool ret = (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount());

        if(ret)
        {
            Vertex* v = m_vertList.get(i);           // 顶点i的指针
            int pos = v->edge.find(Edge<E>(i, j));   // 顶点i中查找到顶点j的边

            // 顶点i中有到顶点j的边
            if(pos >= 0)
            {
                value = v->edge.get(pos).data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned in this edge ...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)       // 设置边(i, j)的值
    {
        bool ret = (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount());

        if(ret)
        {
            Vertex* v = m_vertList.get(i);
            int pos = v->edge.find(Edge<E>(i, j));

            // 有 i->j 这条边
            if(pos >= 0)
            {
                ret = v->edge.set(pos, Edge<E>(i, j, value));
            }
            else   // 没有i->j 这条边，那就尾部新插入一条边
            {
                ret = v->edge.insert(Edge<E>(i, j, value));
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i or j is invalid ...");
        }

        return ret;
    }

    bool removeEdge(int i, int j)                    // 删除边(i, j)
    {
        bool ret = (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount());

        if(ret)
        {
            Vertex* v = m_vertList.get(i);
            int pos = v->edge.find(Edge<E>(i, j));

            if(pos >= 0)
            {
                ret = v->edge.remove(pos);
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "No edge j in Vertex i ...");
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter i or j is invalid ...");
        }

        return ret;
    }

    int vCount()    // 获取顶点的数量
    {
        return m_vertList.length();
    }

    int eCount()    // 获取边的数量
    {
        int ret = 0;

        for(m_vertList.move(0); !m_vertList.isEnd(); m_vertList.next())
        {
            ret += m_vertList.current()->edge.length();
        }

        return ret;
    }

    int OD(int i)   // 获取顶点 i 的出度
    {
        int ret = 0;

        if((0 <= i) && (i <= vCount()))
        {
            ret = m_vertList.get(i)->edge.length();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    int ID(int i)   // 获取顶点 i 的入度
    {
        int ret = 0;

        if((0 <= i) && (i <= vCount()))
        {
            for(m_vertList.move(0); !m_vertList.isEnd(); m_vertList.next())
            {
                // 引用变量方便后面代码好写
                LinkList< Edge<E> >& edge = m_vertList.current()->edge;

                for(edge.move(0); !edge.isEnd(); edge.next())
                {
                    if(edge.current().end == i)
                    {
                        ret++;
                        break;
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    ~ListGraph()
    {
        while (m_vertList.length() > 0)
        {
            Vertex* toDel = m_vertList.get(0);

            m_vertList.remove(0);

            delete toDel->data;
            delete toDel;
        }
    }
};

}

#endif

