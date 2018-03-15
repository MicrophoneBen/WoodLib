// main.cpp  通用树的 插入函数 insert()
#include <iostream>
#include "GTree.h"
#include "GTreeNode.h"

using namespace std;
using namespace WoodLib;

int main()
{
    GTree<char> t;

    t.insert('A', NULL);
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
*/
