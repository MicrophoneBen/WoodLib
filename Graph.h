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

public:
    virtual V getVertex(int i) = 0;                         // 获取顶点i的值
    virtual bool getVertex(int i, V& value) = 0;            // 获取顶点i的值
    virtual bool setVertex(int i, const V& value) = 0;      // 设置顶点i的值

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
};

}

#endif
