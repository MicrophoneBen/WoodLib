// Graph.h 图的抽象类
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Object.h"
#include "SharedPointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"

namespace WoodLib
{

// 边相关的数据类型
template <typename E>
struct Edge : public Object
{
    int begin;   // 起点
    int end;     // 终点
    E data;      // 权值

    Edge(int b = -1, int e = -1) : begin(b), end(e) {}
    Edge(int b, int e, const E& value) : begin(b), end(e), data(value) {}

    // 用于查找时比较用，一定不可少
    bool operator == (const Edge<E>& rhs)
    {
        return (begin == rhs.begin) && (end == rhs.end);
    }

    bool operator != (const Edge<E>& rhs)
    {
        return !(*this == rhs);
    }

    // 用于排序时比较用，一定不可少
    bool operator > (const Edge<E>& rhs)
    {
        return (data > rhs.data);
    }

    bool operator < (const Edge<E>& rhs)
    {
        return (data < rhs.data);
    }

    bool operator >= (const Edge<E>& rhs)
    {
        return (data >= rhs.data);
    }

    bool operator <= (const Edge<E>& rhs)
    {
        return (data <= rhs.data);
    }
};

// V 为顶点的数据类型，E 为边的数据类型
template <typename V, typename E>
class Graph : public Object
{
protected:
    // 注意传参一定要用引用，否则报段错误的异常
    template <typename T>
    DynamicArray<T>* queueToArray(LinkQueue<T>& queue)
    {
        DynamicArray<T>* ret = new DynamicArray<T>(queue.length());

        if(ret != NULL)
        {
            for(int i=0; i<ret->length(); i++)
            {
                // 将数组元素设置为队头元素，再队头元素出队
                ret->set(i, queue.front());
                queue.deQueue();
            }
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "No memory to create ret object ...");
        }

        return ret;
    }

    // 获取无向图的边集 -- for kruskal算法
    SharedPointer< Array< Edge<E> > > getUndirectedEdges()
    {
        DynamicArray< Edge<E> >* ret = NULL;

        if(asUndirected())
        {
            LinkQueue< Edge<E> > queue;

            // 双重for循环，对每个顶点进行边的遍历
            for(int i=0; i<vCount(); i++)
            {
                for(int j=0; j<vCount(); j++)
                {
                    if(isAdjacent(i, j))
                    {
                        queue.enQueue(Edge<E>(i, j, getEdge(i, j)));
                    }
                }
            }

            ret = queueToArray(queue);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "This function is for undirected graph only ...");
        }

        return ret;
    }

    // kruskal 回路判断
    // prev 前驱标记数组，v前驱标记数组的下标
    int find(Array<int>& prev, int v)
    {
        // 前驱标记数组不为-1
        while (prev[v] >= 0)
        {
            v = prev[v];
        }

        return v;
    }

public:
    virtual V getVertex(int i) = 0;                         // 获取顶点i的值
    virtual bool getVertex(int i, V& value) = 0;            // 获取顶点i的值
    virtual bool setVertex(int i, const V& value) = 0;      // 设置顶点i的值

    // 判断是否可看做无向图
    bool asUndirected()
    {
        bool ret = true;

        for(int i=0; i<vCount() && ret; i++)
        {
            for(int j=0; j<vCount() && ret; j++)
            {
                // 判断i和j互为邻接顶点且<i,j>和<j,i>边的权值相等
                if(isAdjacent(i, j))
                {
                    ret = ret && isAdjacent(j, i) && (getEdge(i, j) == getEdge(j, i));
                }
            }
        }

        return ret;
    }

    // 判断图中顶点i到顶点j是否邻接
    virtual bool isAdjacent(int i, int j) = 0;

    // 获取顶点 i 的邻接顶点
    virtual SharedPointer< Array<int> > getAdjacent(int i) = 0;

    // 参数 i 为起点，j为终点，value为边（权值）
    virtual E getEdge(int i, int j) = 0;                    // 获取边(i, j)的值
    virtual bool getEdge(int i, int j, E& value) = 0;       // 获取边(i, j)的值
    virtual bool setEdge(int i, int j, const E& value) = 0; // 设置边(i, j)的值
    virtual bool removeEdge(int i, int j) = 0;              // 删除边(i, j)

    virtual int vCount() = 0;    // 获取顶点的数量
    virtual int eCount() = 0;    // 获取边的数量

    virtual int OD(int i) = 0;   // 获取顶点 i 的出度
    virtual int ID(int i) = 0;   // 获取顶点 i 的入度
    virtual int TD(int i)        // 获取顶点 i 的度
    {
        return ID(i) + OD(i);
    }

    // 广度优先遍历：参数i为起始顶点，返回值为遍历时访问的顶点的数组
    SharedPointer< Array<int> > BFS(int i)
    {
        DynamicArray<int>* ret = NULL;

        if((0 <= i) && (i < vCount()))
        {
            LinkQueue<int> q;   // 链式队列
            LinkQueue<int> r;   // return 队列

            DynamicArray<bool> visited(vCount()); // 顶点是否被访问过的标记数组

            for(int i=0; i<visited.length(); i++)
            {
                visited[i] = false;
            }

            // 1.将起始顶点加入队列中
            q.enQueue(i);

            while (q.length() > 0)
            {
                int v = q.front();   // 队头元素

                // 2.队头元素出队列，并判断队头元素是否被访问过
                q.deQueue();
                if(!visited[v])
                {
                    // 3. 将顶点v标访为己访问过，并将v的邻接顶点压入q队列中
                    visited[v] = true;

                    SharedPointer< Array<int> > aj = getAdjacent(v);

                    // 遍历这些邻接顶点
                    for(int i=0; i<aj->length(); i++)
                    {
                        int k = (*aj)[i];

                        // 未被访问过的，则加入q队列
                        // 这个地方与唐佐林讲的不一样，唐佐林的是在r队列中过滤
                        // 这里是直接在q队列中过滤掉已经访问的顶点
                        if(!visited[k])
                        {
                            q.enQueue(k);
                        }
                    }
                    // 将v压入返回值的r队列中
                    r.enQueue(v);
                }
            }
            // 将队列转换为数组
            ret = queueToArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    // 深度优先遍历：参数i为起始顶点，返回值为遍历时访问的顶点的数组
    SharedPointer< Array<int> > DFS(int i)
    {
        DynamicArray<int>* ret = NULL;

        if((0 <= i) && (i < vCount()))
        {
            LinkStack<int> s;   // 链式栈
            LinkQueue<int> r;   // return 队列

            DynamicArray<bool> visited(vCount()); // 顶点是否被访问过的标记数组

            for(int i=0; i<visited.length(); i++)
            {
                visited[i] = false;
            }

            // 1.将起始顶点加入栈中
            s.push(i);

            while (s.size() > 0)
            {
                int v = s.top();   // 栈头元素

                // 2.栈头元素弹出，并判断栈头元素是否被访问过
                s.pop();
                if(!visited[v])
                {
                    // 3. 将顶点v标访为己访问过，并将v的邻接顶点压入s栈中
                    visited[v] = true;

                    SharedPointer< Array<int> > aj = getAdjacent(v);

                    // 遍历这些邻接顶点
                    // 这个地方注意，栈是先进后出，为了与人直观感受一致
                    // 让编号小的邻接顶点后入栈这样就先出，符合人的感官感受
                    // 这个访问顺序就类似于二叉树的先序遍历的访问顺序
                    // 其实这个for也OK,只不过就恰好与人感官感受相反(类似后序)
                    // for(int i=0; i<aj->length(); i++)
                    for(int i=aj->length()-1; i>=0; i--)
                    {
                        int k = (*aj)[i];

                        // 未被访问过的，则加入s栈
                        // 这个地方与唐佐林讲的不一样，唐佐林的是在r队列中过滤
                        // 这里是直接在s栈中过滤掉已经访问的顶点
                        if(!visited[k])
                        {
                            s.push(k);
                        }
                    }
                    // 将v压入返回值的r队列中
                    r.enQueue(v);
                }
            }
            // 将队列转换为数组
            ret = queueToArray(r);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    // Prim算法(求最小/大生成树)
    // LIMIT 理想的极限值，最小树则传最大值，最大树则传最小值0
    // MINORMAX 为true时找最小生成树，为false找最大生成树，默认最小生成树
    SharedPointer< Array< Edge<E> > > prim(const E& LIMIT, const bool MINORMAX = true)
    {
        LinkQueue< Edge<E> > ret;

        // prim算法只能用于无向图，这里判断是无向图
        if(asUndirected())
        {
            // 1.准备工作
            DynamicArray<bool> mark(vCount());  // 标记顶点所属的集合（T or F）
            DynamicArray<E> cost(vCount());     // 记录T集合到F集合中顶点的最小权值
            DynamicArray<int> adjVex(vCount()); // 记录cost中权值时的对应顶点

            SharedPointer< Array<int> > aj = NULL; // 标记某个顶点的邻接顶点
            bool end = false;     // 是否中断执行
            int v = 0;            // 从0号顶点开始查找最小生成树

            for(int i=0; i<vCount(); i++)
            {
                mark[i] = false;
                cost[i] = LIMIT;  // LIMIT为最值(最小数则这个数就是个理想的最大值)
                adjVex[i] = -1;
            }

            // 2.对初始化顶点v进行操作
            mark[v] = true;     // v加入最小生成树（T集合），生成T0树
            aj = getAdjacent(v);

            for(int i=0; i<aj->length(); i++)
            {
                // 更新各顶点到T0树的矩离，及记录各顶点通过哪个顶点靠近T0树
                int t = (*aj)[i];
                cost[t] = getEdge(v, t); // 获取边的权值并加入cost数组
                adjVex[t] = v;           // t顶点通过T集合中的v顶点靠近树
            }

            // 3.继续扩展最小/大生成树
            for(int i=0; (i<vCount() && !end); i++)
            {
                E mCost = LIMIT;
                int k = -1;

                // 从F集合中选择权值最小的边，并将所对应的顶点（未标记）加入到T集合
                for(int j=0; j<vCount(); j++)
                {
                    if(!mark[j] && (MINORMAX ? (cost[j] < mCost) : (cost[j] > mCost)))
                    {
                        mCost = cost[j];
                        k = j;
                    }
                }

                end = (-1 == k);  // 如果无法找到最小权值的边，则算法结束

                if(!end)
                {
                    // 找到权值最小的边，将该边加入到ret队列
                    ret.enQueue(Edge<E>(adjVex[k], k, getEdge(adjVex[k], k)));
                    mark[k] = true;
                    aj = getAdjacent(k);

                    // 更新其余未标记顶点到新树的最近矩离（实际上只需更新与k相连的顶点即可）
                    for(int j=0; j<aj->length(); j++)
                    {
                        int t = (*aj)[j];
                        if(!mark[t] && (MINORMAX ? (getEdge(t, k) < cost[t]) : (getEdge(t, k) > cost[t])))
                        {
                            cost[t] = getEdge(t, k);
                            adjVex[t] = k;
                        }
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Prim operation is for undirected graph only ...");
        }

        // n个顶点的图需要n-1条边才能够生成最小生成树
        if(ret.length() != (vCount() -1))
        {
            // 出现这种情况则说明图中有孤立的顶点没有与其他任何顶点邻接
            THROW_EXCEPTION(InvalidOperationException, "No enough edge for Prim operation ...");
        }

        return queueToArray(ret);
    }

    // Krusal 算法(求最小/大生成树)
    // MINORMAX 为true时找最小生成树，为false找最大生成树，默认最小生成树
    SharedPointer< Array< Edge<E> > > krusal(const bool MINORMAX = true)
    {
        LinkQueue< Edge<E> > ret;     // ret 队列
        // 无向图边集
        SharedPointer< Array< Edge<E> > > edges = getUndirectedEdges();
		// 前驱标记数组：用于判断新选择的边是否构成回路
        DynamicArray<int> prev(vCount());  

        for(int i=0; i<prev.length(); i++)
        {
            prev[i] = -1;     // n个顶点的图初始化为n课树
        }

        // 将边权值排序：求最小生成树时，升序；最大生成树时降序
        edges->bubbleSort(MINORMAX);

        // n 个顶点的图 最小生成树最多有 n-1 条边
        for(int i=0; (i<edges->length()) && (ret.length()<vCount()-1); i++)
        {
            Edge<E>& edge = (*edges)[i];

            // 判断该边的两端的顶点是否位于不同的棵中
            int begin = find(prev, edge.begin);
            int end   = find(prev, edge.end);

            // 不存在回路
            if(begin != end)
            {
                prev[end] = begin;
                ret.enQueue(edge);   // 队列数量最多可到 vCount() - 1
            }
        }

        // 边数不够，则无法构成最小生成树
        if(ret.length() != (vCount() -1))
        {
            THROW_EXCEPTION(InvalidOperationException, "No enough edges for Krusal operation ...");
        }

        return queueToArray(ret);
    }
};

}

#endif
