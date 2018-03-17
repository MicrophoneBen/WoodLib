// main.cpp  二叉树 典型遍历方式 使用示例
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

    cout << endl << endl << "Clone BTree ... " << endl;

    // clone() 操作检测
    SharedPointer< BTree<int> > tree = t.clone();

    for(tree->begin(); !tree->isEnd(); tree->next())
    {
        cout << tree->current() << " ";
    }

    // 比较操作检测
    cout << endl << endl << "t == *tree : " << (t == *tree) << endl;
    cout << "t != *tree : " << (t != *tree) << endl;

    t.insert(100, t.find(9));

    cout << endl << "Old BTree insert '100' ... " << endl;

    for(t.begin(); !t.isEnd(); t.next())
    {
        cout << t.current() << " ";
    }

    cout << endl << endl << "t == *tree : " << (t == *tree) << endl;
    cout << "t != *tree : " << (t != *tree) << endl << endl;

    // add() 检测
    cout << "Old + Clone BTree ..." << endl;
    SharedPointer< BTree<int> > sum = t.add(*tree);

    for(sum->begin(); !sum->isEnd(); sum->next())
    {
        cout << sum->current() << " ";
    }

    cout << endl << endl;

    // 对相加后的树父结点指针检测
    const int value[] = {100, 10, 12, 14};

    for(int i=0; i < sizeof(value) / sizeof(value[0]); i++)
    {
        TreeNode<int>* node = sum->find(value[i]);

        while( node != NULL )
        {
            cout << node->m_value << "->";
            node = node->m_parent;
        }

        cout << "NULL" << endl;
    }

    cout << endl;

    // 非空树与一棵空树相加
    cout << "Clone + Empty BTree ..." << endl;
    SharedPointer< BTree<int> > sum1 = (*sum).add(BTree<int>());

    for(sum1->begin(); !sum1->isEnd(); sum1->next())
    {
        cout << sum1->current() << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
Old BTree ...
1 2 3 4 5 6 7 8 9

Clone BTree ...
1 2 3 4 5 6 7 8 9

t == *tree : 1
t != *tree : 0

Old BTree insert '100' ...
1 2 3 4 5 6 7 8 9 100

t == *tree : 0
t != *tree : 1

Old + Clone BTree ...
2 4 6 8 10 12 14 16 18 100

100->18->16->8->4->2->NULL
10->4->2->NULL
12->6->2->NULL
14->6->2->NULL

Clone + Empty BTree ...
2 4 6 8 10 12 14 16 18 100
*/
