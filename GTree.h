// GTree.h 通用树类
#ifndef _GTREE_H_
#define _GTREE_H_

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T >
class GTree : public Tree<T>
{
private:
    // 查找功能函数 以值作为查找 const 表示这个函数不修改变量值
    // 找到了就返回相应的节点地址 没找到就返回 NULL
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(value == node->m_value)  // 递归出口，根结点中保存的值就是要查找的值
            {
                return node;
            }
            else
            {
                // ret == NULL 表示还没有找到，一旦找到 ret != NULL 也就立即退出for循环
                for( node->m_child.move(0); !node->m_child.isEnd() && (ret == NULL); node->m_child.next())
                {
                    // 利用递归在子树中查找
                    ret = find(node->m_child.current(), value);
                }
            }
        }

        return ret;
    }

    // 查找功能函数 以节点作为查找
    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;

        if( node == obj )  // 递归出口，根结点就是要查找的结点
        {
            ret = node;
        }
        else
        {
            if( node != NULL )
            {
                for(node->m_child.move(0); !node->m_child.isEnd() && (ret == NULL); node->m_child.next())
                {
                    ret = find(node->m_child.current(), obj);
                }
            }
        }

        return ret;
    }

    // 功能函数 destory 用来释放堆上面的节点的
    void destory(GTreeNode<T>* node)
    {
        if( NULL != node )
        {
            // 递归出口就是一棵树只有根结点时（即没有子结点 m_child 为空链表时），这个for循环
            // 就不会进去，也就不会再递归了，也就会执行后面清除 根结点 node 了，这就是递归出口
            for(node->m_child.move(0); !node->m_child.isEnd(); node->m_child.next())
            {
                // 递归思想
                destory(node->m_child.current());
            }

            if( node->isHeap() )
            {
                delete node;       // 清除完子树后将根结点干掉
            }
        }
    }

    // 功能函数 remove 用来删除树中的树枝
    void remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
        ret = new GTree<T>;

        if( NULL != ret )
        {
            if( this->m_root == node )
            {
                this->m_root = NULL;
            }
            else
            {
                // 获得要移除结点的父结点的孩子链表，要移除的结点的地址就保存在 这个孩子链表里 某个结点的数据域上
                LinkList< GTreeNode<T>* >& child = dynamic_cast< GTreeNode<T>* >(node->m_parent)->m_child;

                // 找到 要移除结点 在链表中的索引号，再根据这个索引号将其从链表中移除（注意这个不是递归，是单链表的remove函数）
                child.remove(child.find(node));

                // 将移除结点的父结点指针置为NULL，使之成为根结点
                node->m_parent = NULL;
            }

            // 将移除的结点作为根结点的树 赋给返回值 ret
            ret->m_root = node;
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "No memory to creat new tree ...");
        }
    }

    int count(GTreeNode<T>* node) const
    {
        int ret = 0;       // 不能进入 if 表示根结点为NULL则 ret = 0

        if( NULL != node )
        {
            ret = 1;       // 能进入这里表示有根节点 ret = 1

            for(node->m_child.move(0); !node->m_child.isEnd(); node->m_child.next())
            {
                // 能够进入 for循环 表示有孩子结点（for循环不能进入就是递归出口）
                ret += count(node->m_child.current());
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* node) const
    {
        int ret = 0;       // 不能进入 if 表示根结点为NULL则 ret = 0

        if( NULL != node )
        {
            for(node->m_child.move(0); !node->m_child.isEnd(); node->m_child.next())
            {
                // 能够进入 for循环 表示有孩子结点（for循环不能进入就是递归出口）
                int h = height(node->m_child.current());

                // 特别强调：用数学思想理解
                // 根结点几个 子树 高度比较取 最大的那个 就是子树中最大高度值了
                if( ret < h )
                {
                    ret = h;
                }
            }

            // 加上根结点的高度 1 就是整个树的高度了
            ret = ret +1;
        }

        return ret;
    }

    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;       // 不能进入 if 表示根结点为NULL则 ret = 0

        if( NULL != node )
        {
            // 能进入这里表示有根节点,再根据根结点中的 孩子链表中链表结点的个数 就是这个根节点的度
            ret = node->m_child.length();

            for(node->m_child.move(0); !node->m_child.isEnd(); node->m_child.next())
            {
                // 能够进入 for循环 表示有孩子结点（for循环不能进入就是递归出口）
                int d = degree(node->m_child.current());

                if( ret < d )
                {
                    ret = d;
                }
            }
        }

        return ret;
    }


public:
    bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        if( NULL != node )
        {
            if( NULL == this->m_root )
            {
                this->m_root = node;
                node->m_parent = NULL;
            }
            else
            {
                GTreeNode<T>* node_parent = find(node->m_parent);

                if( node_parent != NULL )
                {
                    GTreeNode<T>* GTree_node = dynamic_cast<GTreeNode<T>*>(node);

                    // 防止重复插入同一个节点,所以这里再child链表中查找一遍
                    // 若 m_child 为空链表，则不用查找直接插入，不为空链表就查找是不是已经有这个节点存在,不存在就插入GTree_node
                    if( (node_parent->m_child.length() == 0) || (node_parent->m_child.find(GTree_node) == -1) )
                    {
                        node_parent->m_child.insert(GTree_node);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "Invalid parent tree node ...");
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
        bool ret = true;

        GTreeNode<T>* p_node = GTreeNode<T>::newNode();  // 只能调用static函数来在堆上创建了

        if( NULL != p_node )
        {
            p_node->m_value = value;
            p_node->m_parent = parent;

            ret = insert(p_node);
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memort to insert node ...");
        }

        return ret;
    }

    // <> 间空格隔开，防止出现 >> 被编译器错误解读符合，导致编译错误
    SharedPointer< Tree<T> > remove(const T& value)
    {
        //虽然函数原型返回值是 SharedPointer< Tree<T> >，但却不能这样定义ret
        // 1、这样定义 那么这个只能指针对象还是个栈对象，返回栈空间引发程序崩溃
        // 2、remove(p_node, ret) 时，作为传参的ret的类型时 GTree<T>*
        //   下面SharedPointer< Tree<T> >的类型会编译直接报错
        // 3、ret定义为GTree<T>*类型，是个指针它最后指向的是一片堆空间，再这个
        //   函数结束时编译器会根据函数原型是智能指针，而用这个 ret 帮我创建出
        //   个智能智能类对象来接受ret，然后再返回！
        //SharedPointer< Tree<T> > ret = NULL;

        GTree<T>* ret = NULL;

        GTreeNode<T>* p_node = find(value);

        if( NULL != p_node )
        {
            remove(p_node, ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value ...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;

        node = find(node);

        if( NULL != node )
        {
            // node是TreeNode<T>* 接受 find返回的 GTreeNode<T>*
            // 所以这里需要动态类型转换一下
            remove(dynamic_cast< GTreeNode<T>* >(node), ret);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value ...");
        }

        return ret;
    }

    // 注意返回值由 父类结点指针TreeNode<T>*改为 当前类结点指针GTreeNode<T>*（赋值兼容原则）
    // 这个改也是需要并且合情理的，因为查找的在通用树中找，自然想直接返回的也是通用树的结点地址
    GTreeNode<T>*  find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        // 注意传参为 父类的指针，用动态识别强制转换
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        // 利用动态识别技术，返回子类成员变量 m_root
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
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

    // 清空树
    void clear()
    {
        destory(root());      // 释放树中所有在堆上的结点

        this->m_root = NULL;  // 将根结点置为NULL
    }

    ~GTree()
    {
        clear();
    }

};

}

#endif
