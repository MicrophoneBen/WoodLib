// main.cpp  二叉树 典型遍历方式 使用示例
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

    cout << "level traversal     : ";

    for(t.begin(); !t.isEnd(); t.next())
    {
        cout << t.current() << " ";
    }

    SharedPointer< Array<char> > array = NULL;

    array = t.traversal(PreOrder);

    cout << endl << "preorder traversal  : ";

    for(int i=0; i<array->length(); i++)
    {
        cout << (*array)[i] << " ";
    }

    array = t.traversal(InOrder);

    cout << endl << "inorder traversal   : ";

    for(int i=0; i<array->length(); i++)
    {
        cout << (*array)[i] << " ";
    }

    array = t.traversal(PostOrder);

    cout << endl << "postorder traversal : ";

    for(int i=0; i<array->length(); i++)
    {
        cout << (*array)[i] << " ";
    }

    cout << endl;

    return 0;
}
/* 运行结果
level traversal     : A B C D E F G H I
preorder traversal  : A B D H I E C F G
inorder traversal   : I H D B E A F C G
postorder traversal : I H D E B F G C A
*/
