// main.cpp  二叉树 查找、插入 使用示例
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

    const char* s = "DEFG";

    for(int i=0; i<4; i++)
    {
        TreeNode<char>* node = t.find(s[i]);  // 找到各个分支的叶结点

        while( NULL != node )
        {
            cout << node->m_value << " ";
            node = node->m_parent;
        }

        cout << endl;
    }

    return 0;
}
/* 运行结果
D B A
E B A
F C A
G C A
*/
