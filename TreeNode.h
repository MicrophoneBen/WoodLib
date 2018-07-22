// TreeNode.h 树结点抽象类
#ifndef _TREENODE_H_
#define _TREENODE_H_

#include "Object.h"

namespace WoodLib
{

template < typename T >
class TreeNode : public Object
{
protected:
    bool m_is_heap;

    // 拷贝构造和赋值运算私有化 不让树结点间进行拷贝构造和赋值
    TreeNode(const TreeNode<T>&);
    TreeNode<T>& operator =(const TreeNode<T>&);

    // 重载 new 为私有的，外部不能直接 new 不要忘记加上throw() 失败不让抛出系统异常
    void* operator new(size_t size) throw()
    {
        // 调用顶层父类的 new()
        return Object::operator new(size);
    }

public:                     // 结点中保存的值和指针域在外面需要随时可以访问到，所以这个一定要设置为公开的
    T m_value;              // 树是用来存储数据的，所以肯定有个数据域
    TreeNode<T>* m_parent;  // 指向父结点的指针域，树是非线性的数据结构，
                            // 但这个指针的设计使得树的操作可以按线性操作

public:
    TreeNode() : m_is_heap(false), m_parent(NULL)
    {

    }

    bool isHeap()
    {
        return m_is_heap;
    }

    virtual ~TreeNode() = 0;  // 纯虚函数，使得这个类成为抽象类，不写也行的
                              // 父类Object顶层父类的析构函数就是纯虚函数

                              // 实际main()测试发现，去掉之后竟然可以创建出对象？？？

};

template < typename T >
TreeNode<T>::~TreeNode()      // 纯虚的析构函数也需要提供定义的
{

}

}

#endif
