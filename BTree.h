// BTree.h  二叉树类模板
#ifndef _BTREE_H_
#define _BTREE_H_

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T >
class BTree : public Tree<T>
{
private:
    // 找到了就返回相应的节点地址 没找到就返回 NULL
    BTreeNode<T>* find(BTreeNode<T>* root, const T& value) const
    {
        BTreeNode<T>* ret = NULL;

        if( NULL != root )
        {
            if( root->m_value == value )   // 递归出口
            {
                ret = root;
            }
            else
            {
                if( NULL == ret )
                {
                    // 递归查找左子树
                    ret = find(root->m_left, value);
                }

                if( NULL == ret )
                {
                    // 递归查找右子树
                    ret = find(root->m_right, value);
                }
            }

        }

        return ret;
    }

    BTreeNode<T>* find(BTreeNode<T>* root, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = NULL;

        if( NULL != root )
        {
            if( root == obj )
            {
                ret = root;
            }
            else
            {
                if( NULL == ret )
                {
                    ret = find(root->m_left, obj);
                }

                if( NULL == ret )
                {
                    ret = find(root->m_right, obj);
                }
            }

        }

        return ret;
    }

    bool insert(BTreeNode<T>* new_node, BTreeNode<T>* parent,BTreeNodePos pos)
    {
        bool ret = true;

        if( ANY == pos )
        {
            if( NULL == parent->m_left )
            {
                parent->m_left = new_node;
            }
            else if( NULL == parent->m_right )
            {
                parent->m_right = new_node;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "The child of node cannot to insert new node ...");
            }
        }
        else if( LEFT == pos )
        {
            if( NULL == parent->m_left )
            {
                parent->m_left = new_node;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "The left of node cannot to insert new node ...");
            }
        }
        else if( RIGHT == pos )
        {
            if( NULL == parent->m_right )
            {
                parent->m_right = new_node;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "The right of node cannot to insert new node ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter pos is invalid ...");
        }

        return ret;
    }

public:
    bool insert(TreeNode<T>* new_node)
    {
        return insert(new_node, ANY);
    }

    bool insert(TreeNode<T>* new_node, BTreeNodePos pos)
    {
        bool ret = (new_node != NULL);

        if( ret )
        {
            if( this->m_root == NULL )
            {
                new_node->m_parent = NULL;
                this->m_root = new_node;
            }
            else
            {
                BTreeNode<T>* parent = find(new_node->m_parent);

                if( NULL != parent )
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(new_node), parent, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
                }

            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot to be NULL ...");

        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        return insert(value, parent, ANY);
    }

    bool insert(const T& value, TreeNode<T>* parent, BTreeNodePos pos)
    {
        bool ret = true;

        BTreeNode<T>* new_node = BTreeNode<T>::newNode();

        if( NULL != new_node )
        {
            new_node->m_value = value;
            new_node->m_parent = parent;

            ret = insert(new_node, pos);

            if( !ret )
            {
                delete new_node;
            }
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to insert the node ...");
        }

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

    BTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast< BTreeNode<T>* >(node));
    }

    BTreeNode<T>* root() const
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
