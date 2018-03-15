// GTree.h 通用树类
#ifndef _GTREE_H_
#define _GTREE_H_

#include "Tree.h"
#include "GTreeNode.h"

namespace WoodLib
{

template < typename T >
class GTree : public Tree<T>
{
public:
    bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;

        return ret;
    }

    SharedPointer<Tree<T>> remove(const T& value)
    {
        return NULL;
    }

    SharedPointer<Tree<T>> remove(TreeNode<T>* node)
    {
        return NULL;
    }

    // 注意返回值由 父类结点指针TreeNode<T>*改为 当前类结点指针GTreeNode<T>*（赋值兼容原则）
    // 这个改也是需要并且合情理的，因为查找的在通用树中找，自然想直接返回的也是通用树的结点地址
    GTreeNode<T>* find(const T& value) const
    {
        return NULL;

    }

    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return NULL;
    }

    GTreeNode<T>* root() const
    {
        // 利用动态识别技术，返回子类成员变量 m_root
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return 0;
    }

    int count() const
    {
        return 0;
    }

    int height() const
    {
        return 0;
    }

    void clear()
    {
        this->m_root = NULL;
    }

    ~GTree()
    {
        clear();
    }

};

}

#endif
