// BTreeNode.h 二叉树结点类
#ifndef _BTREENODE_H_
#define _BTREENODE_H_

#include "Tree.h"

namespace WoodLib
{

template < typename T >
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;

    BTreeNode() : left(NULL), right(NULL)
    {

    }

    // 工厂方法 静态成员函数外部用这个访问内部成员函数 new
    static BTreeNode<T>* newNode()
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

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

