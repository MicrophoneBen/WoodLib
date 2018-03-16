// Tree.h 树的抽象类
#ifndef _TREE_H_
#define _TREE_H_

#include "Object.h"
#include "TreeNode.h"
#include "SharedPointer.h"

namespace WoodLib
{

template < typename T >
class Tree : public Object
{
protected:
    TreeNode<T>* m_root;  // 指向树的根结点的指针

    // 拷贝构造和赋值运算私有化 不让树进行拷贝构造和赋值
    Tree(const Tree<T>&);
    Tree<T>& operator =(const Tree<T>&);

public:
    Tree() : m_root(NULL)
    {

    }

    // 根据前面经验，树肯定也需要 增、删、查、以及树的属性相关个功能函数

    virtual bool insert(TreeNode<T>* node) = 0;                     // 增（插入结点）
    virtual bool insert(const T& value, TreeNode<T>* parent) = 0;   // 按位置插入结点

    // 删除结点我的定义：将删除的这个结点及这个结点与其子结点组成的子树从 树 中移除，但用智能指针指向这颗移除的 子树
    // 这样就不是简单粗暴的直接销毁掉子树，而是需要操作的话还能通过智能指针操作到，不需要操作最后也会自动销毁，不需要我管它
    virtual SharedPointer< Tree<T> > remove(const T& value) = 0;    // 删除结点
    virtual SharedPointer< Tree<T> > remove(TreeNode<T>* node) = 0;

    virtual TreeNode<T>* find(const T& value) const = 0;            // 查找结点，返回找到的结点的结点指针
    virtual TreeNode<T>* find(TreeNode<T>* node) const = 0;

    virtual TreeNode<T>* root() const = 0;   // 获取根结点

    virtual int degree() const = 0;          // 树的度
    virtual int count() const = 0;           // 树的结点数目
    virtual int height() const = 0;          // 树的高度
    virtual void clear() = 0;                // 清空树
};

}

#endif
