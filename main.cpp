// main.cpp  通用树的 清空树操作 clear()
#include <iostream>
#include "GTree.h"
#include "GTreeNode.h"

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

    cout << endl << "After clear() ... " << endl;

    t.clear();

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

    // 只有 'A' 这个结点不是堆上面的,所以clear()不销毁，让main()结束时自己销毁

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

After clear() ...
A
*/
