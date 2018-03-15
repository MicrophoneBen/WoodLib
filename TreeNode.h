// TreeNode.h 树结点抽象类
#ifndef _TREENODE_H_
#define _TREENODE_H_

#include "Object.h"

namespace WoodLib
{

template < typename T >
class TreeNode : public Object
{
public:                   // 结点中保存的值和指针域在外面需要随时可以访问到，所以这个一定要设置为公开的
    T value;              // 树是用来存储数据的，所以肯定有个数据域
    TreeNode<T>* parent;  // 指向父结点的指针域，树是非线性的数据结构，
                          // 但这个指针的设计使得树的操作可以按线性操作

public:
    TreeNode() : parent(NULL)
    {

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
