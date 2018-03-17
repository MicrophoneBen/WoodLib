// BTree.h  二叉树类模板
#ifndef _BTREE_H_
#define _BTREE_H_

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace WoodLib
{

enum BTreeTraversal
{
    PreOrder,    // 先序遍历
    InOrder,     // 中序遍历
    PostOrder    // 后序遍历
};

template < typename T >
class BTree : public Tree<T>
{
private:
    LinkQueue< BTreeNode<T>* > m_queue;  // 层次遍历队列用的队列

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

    // 先序遍历
    void preOrderTraversal(BTreeNode<T>* node, LinkQueue< BTreeNode<T>* >& queue)
    {
        if( NULL != node )    // 叶结点（即node == NULL）就是递归出口
        {
            queue.enQueue(node);                       // 将根节点入列
            preOrderTraversal(node->m_left, queue);    // 递归 左孩子入列
            preOrderTraversal(node->m_right, queue);   // 递归 右孩子入列
        }
    }

    // 中序遍历
    void inOrderTraversal(BTreeNode<T>* node, LinkQueue< BTreeNode<T>* >& queue)
    {
        if( NULL != node )
        {
            inOrderTraversal(node->m_left, queue);
            queue.enQueue(node);
            inOrderTraversal(node->m_right, queue);
        }
    }

    // 后序遍历
    void postOrderTraversal(BTreeNode<T>* node, LinkQueue< BTreeNode<T>* >& queue)
    {
        if( NULL != node )
        {
            postOrderTraversal(node->m_left, queue);
            postOrderTraversal(node->m_right, queue);
            queue.enQueue(node);
        }
    }

    // 递归实现：将root为根结点的树 的每个结点的值 克隆到堆内存中的另一个树 对应的结点中
    // 最后返回克隆后的树的 根结点
    BTreeNode<T>* clone(BTreeNode<T>* root) const
    {
        BTreeNode<T>* ret = NULL;

        if( NULL != root )    // 叶结点即root == NULL时是递归出口
        {
            ret = BTreeNode<T>::newNode();

            if( NULL != ret )
            {
                ret->m_value = root->m_value;          // 克隆根结点的数据域

                ret->m_left = clone(root->m_left);     // 克隆根结点左孩子的数据域 （递归到每一个左孩子）
                ret->m_right = clone(root->m_right);   // 克隆根结点右孩子的数据域 （递归到每一个右孩子）

                if( NULL != ret->m_left )
                {
                    ret->m_left->m_parent = ret;
                }

                if( NULL != ret->m_right )
                {
                    ret->m_right->m_parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "No memory to creat clone tree ...");
            }
        }

        return ret;      // 最后返回克隆之后树的 根结点地址
    }

    bool equal(BTreeNode<T>* root, BTreeNode<T>* other_root) const
    {
        bool ret = true;

        if( root == other_root )                 // 同一个树时
        {
            ret = true;
        }
        else if( (!!root + !!other_root) == 1 )  // 一棵树为空树另外一棵不为空树
        {
            ret = false;
        }
        else                                     // 两棵树都不为空树
        {
            // 递归比较结点中的值
            ret = root->m_value == other_root->m_value         \
                && equal(root->m_left, other_root->m_left)     \
                && equal(root->m_right, other_root->m_right);
        }

        return ret;
    }

    // 传参： 相加的两棵树的 根结点
    // 返回值：相加后的树的 根结点地址
    BTreeNode<T>* add(BTreeNode<T>* root, BTreeNode<T>* other_root) const
    {
        BTreeNode<T>* ret = NULL;

        if( (!!root + !!other_root) < 1 )        // 两棵树都为空树
        {
            ret = NULL;
        }
        else if( (!!root + !!other_root) == 1 )  // 一棵树为空树另外一棵不为空树
        {
            ret = !!root ? clone(root) : clone(other_root);
        }
        else                                     // 两棵树都不为空树
        {
            ret = BTreeNode<T>::newNode();

            if( ret )
            {
                ret->m_value = root->m_value + other_root->m_value;
                ret->m_left = add(root->m_left, other_root->m_left);
                ret->m_right = add(root->m_right, other_root->m_right);

                // 设置相加后左右孩子结点的父结点，根结点不用设置直接为NULL
                if( NULL != ret->m_left )
                {
                    ret->m_left->m_parent = ret;
                }

                if( NULL != ret->m_right )
                {
                    ret->m_right->m_parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "No memory to creat new node ...");
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
            m_queue.clear();
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
            remove(dynamic_cast< BTreeNode<T>* >(remove_node), ret);  // ret 在这个里面指向了一个堆空间
            m_queue.clear();
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

        m_queue.clear();
    }

    ~BTree()
    {
        clear();
    }

    bool begin()
    {
        bool ret = (root() != NULL);  // 确保不是空树

        if( ret )
        {
            m_queue.clear();          // 清空队列
            m_queue.enQueue(root());  // 将根结点入队列
        }

        return ret;
    }

    bool isEnd()
    {
        return (m_queue.length() == 0);
    }

    // 返回当前光标指向的结点中的 m_value
    T current()
    {
        if( !isEnd() )
        {
            return m_queue.front()->m_value;  // 返回队首元素指向的值
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "No value at current position ...");
        }
    }

    // 移动光标,实质是队首元素不断的在出队列,后面的元素就成为
    // 队首元素 同时也将每一个出队列的队首元素的子结点全部插入队列
    bool next()
    {
        bool ret = !!m_queue.length();               // 确保队列不为空

        if( ret )
        {
            BTreeNode<T>* p_node = m_queue.front();  // 指向队首元素

            if( p_node->m_left != NULL )
            {
                m_queue.enQueue(p_node->m_left);
            }

            if( p_node->m_right != NULL )
            {
                m_queue.enQueue(p_node->m_right);
            }

            m_queue.deQueue();  // 队首元素出列
        }

        return ret;
    }

    // 典型遍历方法  根据参数选择 先序/中序/后序
    SharedPointer< Array<T> > traversal(BTreeTraversal order)
    {
        DynamicArray<T>* ret = NULL;
        LinkQueue< BTreeNode<T>* > queue;

        switch (order)
        {
        case PreOrder:
            preOrderTraversal(root(), queue);
            break;

        case InOrder:
            inOrderTraversal(root(), queue);
            break;

        case PostOrder:
            postOrderTraversal(root(), queue);
            break;

        default:
            THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
            break;
        }

        ret = new DynamicArray<T>(queue.length());  // 这一步一定不能忘记了

        if( ret )
        {
            for(int i=0; i<(ret->length()); i++)
            {
                //ret[i] = queue.front()->m_value;     // 这个导致异常错误, (*ret) 才是数组
                //(*ret)[i] = queue.front()->m_value;  // 这个是正确的
                ret->set(i, queue.front()->m_value);   // 上面的可以，这个也可以，任选其一
                queue.deQueue();
            }
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "No memory to creat return array ...");
        }

        return ret;
    }

    SharedPointer< BTree<T> > clone() const
    {
        BTree<T>* ret = new BTree();

        if( ret )
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "No memory to creat tree ...");
        }

        return ret;
    }

    bool operator ==(const BTree<T>& btree)
    {
        return equal(root(), btree.root());
    }

    bool operator !=(const BTree<T>& btree)
    {
        return !(*this == btree);
    }

    SharedPointer< BTree<T> > add(const BTree<T>& btree) const
    {
        BTree<T>* ret = new BTree();

        if( NULL != ret )
        {
            ret->m_root = add(root(), btree.root());
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "No memory to cerat the new tree ...");
        }

        return ret;
    }

};

}

#endif
