// main.cpp  二叉树 层次遍历 使用示例
#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"

using namespace std;
using namespace WoodLib;

int main()
{
    BTree<char> t;
    BTreeNode<char> root;       // 栈上创建根结点

    root.m_value = 'A';
    root.m_parent = NULL;

    t.insert(&root);             // 根结点
    t.insert('B', t.find('A'));
    t.insert('C', t.find('A'));

    t.insert('D', t.find('B'));
    t.insert('E', t.find('B'));

    t.insert('F', t.find('C'));
    t.insert('G', t.find('C'));

    t.insert('H', t.find('D'));

    t.insert('I', t.find('H'));

    for(t.begin(); !t.isEnd(); t.next())
    {
        cout << t.current() << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
A B C D E F G H I
*/
