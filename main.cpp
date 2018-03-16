// main.cpp  通用树的 移除子树的操作 remove()
#include <iostream>
#include "GTree.h"
#include "GTreeNode.h"
#include "SharedPointer.h"

using namespace std;
using namespace WoodLib;

int main()
{
    GTree<char> t;
    GTreeNode<char> root;       // 栈上创建根结点

    root.m_value = 'A';
    root.m_parent = NULL;

    t.insert(&root);             // 根结点
    t.insert('B', t.find('A'));
    t.insert('C', t.find('A'));
    t.insert('D', t.find('A'));

    t.insert('E', t.find('B'));
    t.insert('F', t.find('B'));

    t.insert('K', t.find('E'));
    t.insert('L', t.find('E'));

    t.insert('G', t.find('C'));

    t.insert('H', t.find('D'));
    t.insert('I', t.find('D'));
    t.insert('J', t.find('D'));

    t.insert('M', t.find('H'));

    const char* s = "KLFGMIJ";

    cout << "Before clear() ... " << endl;

    for(int i=0; i<7; i++)
    {
        TreeNode<char>* node = t.find(s[i]);  // 找到各个分支的叶结点

        while( NULL != node )
        {
            cout << node->m_value << " ";
            node = node->m_parent;
        }

        cout << endl;
    }

    cout << endl << "After remove() ... " << endl;

    SharedPointer< Tree<char> > remove_tree = t.remove('D');

    for(int i=0; i<7; i++)
    {
        TreeNode<char>* node = t.find(s[i]);  // 找到各个分支的叶结点

        while( NULL != node )
        {
            cout << node->m_value << " ";
            node = node->m_parent;
        }

        cout << endl;
    }

    cout << endl << "removed tree ... " << endl;

    for(int i=0; i<7; i++)
    {
        // 使用智能智能
        TreeNode<char>* node = (*remove_tree).find(s[i]);  // 找到各个分支的叶结点

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
Before clear() ...
K E B A
L E B A
F B A
G C A
M H D A
I D A
J D A

After remove() ...
K E B A
L E B A
F B A
G C A




removed tree ...




M H D
I D
J D
*/
