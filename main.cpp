// main.cpp  二叉树 移除子树 remove() 使用示例
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

    cout << "Before remove ..." << endl;

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

    cout << endl << "After remove ..." << endl;

    SharedPointer< Tree<char> > remove_tree = t.remove('C');             // 按值移除
    //SharedPointer< Tree<char> > remove_tree = t.remove(t.find('C'));   // 按结点移除

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

    cout << endl << "Tree of removed ..." << endl;

    for(int i=0; i<4; i++)
    {
        // remove_tree 是个智能指针对象, *remove_tree 类型是 Tree 类型
        // 但还是正常使用到了 BTree 中的find，这个地方就用到了多态的技术
        TreeNode<char>* node = remove_tree->find(s[i]);  // 找到各个分支的叶结点

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
Before remove ...
D B A
E B A
F C A
G C A

After remove ...
D B A
E B A



Tree of removed ...


F C
G C
*/
