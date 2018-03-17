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

    // 注意理解：remove_node 是要移除的结点地址，并且已经确定这个树中一定有这个结点存在
    void remove(BTreeNode<T>* remove_node, BTree<T>*& ret)
    {
        ret = new BTree();

        if( NULL != ret )
        {
            // 判断这个要移除的结点是不是根结点
            if( root() == remove_node )
            {
                this->m_root = NULL;
            }
            else
            {
#if 0
                // 判断这个要移除的结点是左孩子还是右孩子
                BTreeNode<T>* parent = dynamic_cast< BTreeNode<T>* >(remove_node->m_parent);

                if( parent->m_left == remove_node )
                {
                    parent->m_left = NULL;
                }
                else if( parent->m_right == remove_node )
                {
                    parent->m_right = NULL;
                }
#else
                // 上面if else 可以用下面一句代替
                dynamic_cast< BTreeNode<T>* >(remove_node->m_parent)->m_left == remove_node ?   \
                            dynamic_cast< BTreeNode<T>* >(remove_node->m_parent)->m_left = NULL \
                          : dynamic_cast< BTreeNode<T>* >(remove_node->m_parent)->m_right = NULL;
#endif
            }

            remove_node->m_parent = NULL;  // 将要移除的结点变为根结点
            ret->m_root = remove_node;     // 将移除的结点代表的子树返回
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "No enough memory to creat new tree ...");
        }
    }

    void destory(BTreeNode<T>* node)
    {
        if( NULL != node )
        {
            destory(node->m_left);   // 递归清除左孩子
            destory(node->m_right);  // 递归清除右孩子

            if( node->isHeap() )
            {
                delete node;
            }
            else
            {
                std::cout << node->m_value << std::endl;  // 测试用
            }
        }
    }

    int count(BTreeNode<T>* node) const
    {
#if 0
        int ret = 0;       // 不能进入 if 表示根结点为NULL则 ret = 0

        if( NULL != node )
        {
            ret = count(node->m_left) + count(node->m_right) + 1;
        }

        return ret;
#else
        // 将上面代码优化为下面一句
        return (NULL != node) ? (count(node->m_left) + count(node->m_right) + 1) : 0;

#endif
    }

    int height(BTreeNode<T>* node) const
    {
#if 0
        int ret = 0;       // 不能进入 if 表示根结点为NULL则 ret = 0

        if( NULL != node )
        {
            // 用数学思想理解这句
            ret = (height(node->m_left) > height(node->m_right) ? height(node->m_left) : height(node->m_right)) + 1;
        }

        return ret;
#else
        // 将上面代码优化为这一句代码
        return (NULL != node) ? ((height(node->m_left) > height(node->m_right) ? height(node->m_left) : height(node->m_right)) + 1): 0;
#endif
    }

    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;       // 不能进入 if 表示根结点为NULL则 ret = 0

        if( NULL != node )
        {
            ret = !!(node->m_left) + !!(node->m_right);

            // 二叉树度最大就为2，若已经为2了，就不用递归了
            if( ret < 2 )
            {
                degree(node->m_left);
                degree(node->m_right);
            }
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
        BTree<T>* ret = NULL;

        BTreeNode<T>* remove_node = find(value);

        if( NULL != remove_node )
        {
            remove(remove_node, ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value ...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* remove_node)
    {
        BTree<T>* ret = NULL;

        remove_node = find(remove_node);

        if( NULL != remove_node )
        {
            remove(dynamic_cast< BTreeNode<T>* >(remove_node), ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter remove_node ...");
        }

        return ret;
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
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        destory(root());

        this->m_root = NULL;   // 这步不要忽略了，否则出现不可预期的运行结果
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif
