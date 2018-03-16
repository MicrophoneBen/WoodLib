// main.cpp  通用树的 属性操作 获取树的结点数、高度、度
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

    cout << "t.count() = " << t.count() << endl;
    cout << "t.height() = " << t.height() << endl;
    cout << "t.degree() = " << t.degree() << endl;

    return 0;
}
/* 运行结果
K E B A
L E B A
F B A
G C A
M H D A
I D A
J D A
t.count() = 13
t.height() = 4
t.degree() = 3
*/
