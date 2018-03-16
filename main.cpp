// main.cpp  通用树的 层次遍历
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

    // 按层次遍历整个树
    for(t.begin(); !t.isEnd(); t.next())
    {
        cout << t.current() << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
A B C D E F G H I J K L M
*/
