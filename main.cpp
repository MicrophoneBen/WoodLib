// main.cpp  二叉树 删除树中单度结点 使用示例
#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"

using namespace std;
using namespace WoodLib;

/* 删除单度结点,结点删除后其唯一子结点替代它的位置
             0                        0
           /   \                    /   \
          1     2                  6     2
         /     / \       ==》           /  \
        3     4   5                    7   8
         \   /    /
          6  7   8
*/

// 创建一个二叉树(创建的就是上面的初始二叉树，左边的)
template < typename T >
BTreeNode<T>* createTree()
{
    static BTreeNode<int> bn[9];

    for(int i=0; i<9; i++)
    {
        bn[i].m_value = i;
        bn[i].m_parent = NULL;
        bn[i].m_left = NULL;
        bn[i].m_right = NULL;
    }

    bn[0].m_left   = &bn[1];
    bn[0].m_right  = &bn[2];
    bn[1].m_parent = &bn[0];
    bn[2].m_parent = &bn[0];

    bn[1].m_left   = &bn[3];
    bn[1].m_right  = NULL;
    bn[3].m_parent = &bn[1];
    bn[2].m_left   = &bn[4];
    bn[2].m_right  = &bn[5];
    bn[4].m_parent = &bn[2];
    bn[5].m_parent = &bn[2];

    bn[3].m_left   = NULL;
    bn[3].m_right  = &bn[6];
    bn[6].m_parent = &bn[3];
    bn[4].m_left   = &bn[7];
    bn[4].m_right  = NULL;
    bn[7].m_parent = &bn[4];

    bn[5].m_left   = &bn[8];
    bn[5].m_right  = NULL;
    bn[8].m_parent = &bn[5];

    return bn;
}

// 对二叉树进行中序遍历
template < typename T >
void printInOrder(BTreeNode<T>* node)
{
    if( node != NULL )
    {
        printInOrder(node->m_left);
        cout << node->m_value <<" ";
        printInOrder(node->m_right);
    }
}

// 删除单度结点的功能函数(二叉树有父指针的版本)
template < typename T >
BTreeNode<T>* delNodeDegree1_1(BTreeNode<T>* root)
{
    BTreeNode<T>* ret = NULL;

    if( root != NULL ) // 二叉树不为空树
    {
        // 单度结点的情况
        if( !!root->m_left + !!root->m_right == 1 )
        {
            BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(root->m_parent);
            BTreeNode<T>* root_child = (root->m_left != NULL) ? root->m_left : root->m_right;

            if( parent != NULL )  // 根结点不为单度结点
            {
                // 指针的引用 表示 单度结点的父结点的孩子结点指针
                BTreeNode<T>*& parent_child = (parent->m_left == root) ? parent->m_left : parent->m_right;

                parent_child = root_child;

                root_child->m_parent = parent;
            }
            else
            {
                root_child->m_parent = NULL;

                ret = root_child;
            }

            if( root->isHeap() )
            {
                delete root;
            }

            ret = delNodeDegree1_1(root_child); // 递归删除单度结点
        }
        else
        {
            delNodeDegree1_1(root->m_left);
            delNodeDegree1_1(root->m_right);

            ret = root;  // 这种情况根结点没变,所以根结点就依旧还是 node
        }
    }

    return ret;
}

// 删除单度结点的功能函数(二叉树无父指针的版本)
// 注意与上面不同,这个参数是个引用,返回也是有它带出的
template < typename T >
void delNodeDegree1_2(BTreeNode<T>*& root)
{
    if( root != NULL ) // 二叉树不为空树
    {
        // 单度结点的情况
        if( !!root->m_left + !!root->m_right == 1 )
        {
            // 指针引用
            BTreeNode<T>*& root_child = (root->m_left != NULL) ? root->m_left : root->m_right;

            if( root->isHeap() )
            {
                delete root;
            }

            root = root_child;

            delNodeDegree1_2(root); // 递归删除单度结点，不能是delNodeDegree1_2(root_child);
        }
        else
        {
            delNodeDegree1_2(root->m_left);
            delNodeDegree1_2(root->m_right);
        }
    }
}

int main()
{
    BTreeNode<int>* bt = createTree<int>();

    printInOrder(bt);

    cout << endl;

    bt = delNodeDegree1_1(bt);

    printInOrder(bt);

    cout << endl << endl;

    cout << "No parent ..." << endl;
    BTreeNode<int>* bt2 = createTree<int>();

    delNodeDegree1_2(bt2);

    printInOrder(bt2);

    cout << endl;

    return 0;
}
/* 运行结果
3 6 1 0 7 4 2 8 5
6 0 7 2 8

No parent ...
6 0 7 2 8
*/
