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
private:
    // 查找功能函数 以值作为查找 const 表示这个函数不修改变量值
    // 找到了就返回相应的节点地址 没找到就返回 NULL
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(value == node->value)  // 递归出口，根结点中保存的值就是要查找的值
            {
                return node;
            }
            else
            {
                // ret == NULL 表示还没有找到，一旦找到 ret != NULL 也就立即退出for循环
                for(node->child.move(0); !node->child.isEnd() && (ret == NULL); node->child.next())
                {
                    // 利用递归在子树中查找
                    ret = find(node->child.current(), value);
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
                for(node->child.move(0); !node->child.isEnd() && (ret == NULL); node->child.next())
                {
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }

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
