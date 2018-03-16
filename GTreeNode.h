// GTreeNode.h 通用树结点类
#ifndef _GTREENODE_H_
#define _GTREENODE_H_

#include "TreeNode.h"
#include "LinkList.h"

namespace WoodLib
{

template < typename T >
class GTreeNode : public TreeNode<T>
{
private:
    bool m_is_heap;

    // 重载 new 为私有的，外部不能直接 new 不要忘记加上throw() 失败不让抛出系统异常
    void* operator new(unsigned int size) throw()
    {
        // 调用顶层父类的 new()
        return Object::operator new(size);
    }

public:                                  // 通用树结点在外面需要随时可以访问到child指针域，所以这个一定要设置为公开的
    LinkList< GTreeNode<T>* > m_child;   // 树每个结点中都需要有指针能够指向子结点，自然单链表最合适

    GTreeNode() : m_is_heap(false)       // 默认是否是堆空间节点的标记为 false
    {

    }

    bool isHeap()
    {
        return m_is_heap;
    }

    // 工厂方法 静态成员函数外部用这个访问内部成员函数 new
    static GTreeNode<T>* newNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if( ret != NULL )
        {
            // 堆上面创建的结点 将 m_is_heap 标记为 true
            ret->m_is_heap = true;   // 不要忘记是 ret->m_is_heap
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to creat node ...");
        }

        return ret;
    }
};

}

#endif
