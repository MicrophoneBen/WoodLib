// BTree.h  二叉树类模板
#ifndef _BTREE_H_
#define _BTREE_H_

#include "Tree.h"
#include "BTreeNode.h"

namespace WoodLib
{

template < typename T >
class BTree : public Tree<T>
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

    SharedPointer< Tree<T> > remove(const T& value)
    {
        return NULL;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        return NULL;
    }

    TreeNode<T>* find(const T& value) const
    {
        return NULL;
    }

    TreeNode<T>* find(TreeNode<T>* node) const
    {
        return NULL;
    }

    TreeNode<T>* root() const
    {
        return dynamic_cast< BTreeNode<T>* >(this->m_root);
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

    ~BTree()
    {
        clear();
    }
};

}

#endif
