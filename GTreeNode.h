// GTreeNode.h 通用树结点类
#ifndef _GTREENODE_H_
#define _GTREENODE_H_

#include "TreeNode.h"
#include "LinkList.h"

namespace WoodLib
{

template < typename T >
class GTreeNode : public TreeNode<T>
{
private:
    LinkList<GTreeNode<T>*> child;   // 树每个结点中都需要有指针能够指向子结点，自然单链表最合适
};

}

#endif
