// main.cpp  二叉树 线索化（将二叉树变为双向链表） 使用示例
#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"

using namespace std;
using namespace WoodLib;

int main()
{
    BTree<int> t;
    BTreeNode<int> root;         // 栈上创建根结点

    root.m_value = 1;
    root.m_parent = NULL;

    t.insert(&root);             // 根结点
    t.insert(2, t.find(1));
    t.insert(3, t.find(1));

    t.insert(4, t.find(2));
    t.insert(5, t.find(2));

    t.insert(6, t.find(3));
    t.insert(7, t.find(3));

    t.insert(8, t.find(4));

    t.insert(9, t.find(8));

    cout << "Old BTree ... " << endl;

    for(t.begin(); !t.isEnd(); t.next())
    {
        cout << t.current() << " ";
    }

    // 新增的层次遍历函数功能
    cout << endl << endl << "LevelOrder BTree ... " << endl;

    SharedPointer< Array<int> > tree = t.traversal(LevelOrder);

    for(int i=0; i<tree->length(); i++)
    {
        cout << (*tree)[i] << " ";
    }

    // 测试二叉树线索化后的双向链表
    cout << endl << endl << "LevelOrderthreading Link ... " << endl;

    BTreeNode<int>* node = t.threading(LevelOrder);
    BTreeNode<int>* end = NULL;

    while( !!node )
    {
        cout << node->m_value << "->";
        end = node;
        node = node->m_right;          // m_right 指针逐个访问
    }

    cout << "NULL" << endl;

    while( !!end )
    {
        cout << end->m_value << "->";
        end = end->m_left;             // m_left 指针逐个访问
    }

    cout << "NULL" << endl;

    return 0;
}
/* 运行结果
Old BTree ...
1 2 3 4 5 6 7 8 9

LevelOrder BTree ...
1 2 3 4 5 6 7 8 9

LevelOrderthreading Link ...
1->2->3->4->5->6->7->8->9->NULL
9->8->7->6->5->4->3->2->1->NULL
*/
