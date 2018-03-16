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
            else
            {
                std::cout << node->m_value << std::endl;   // 测试看看的，非堆上的结点就打印出来
            }
        }
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
        return NULL;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        return NULL;
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
