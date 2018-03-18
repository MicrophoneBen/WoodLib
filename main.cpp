// main.cpp  二叉树 （不使用其他数据结构）中序遍历线索化 使用示例
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

// 输出双向链表(不是循环的双向链表)
template < typename T >
void printDualList(BTreeNode<T>* node)
{
    BTreeNode<T>* g = node;

    cout << "head -> tail: " << endl;

    while( node != NULL )
    {
        cout << node->m_value << " ";

        g = node;

        node = node->m_right;
    }

    cout << endl;

    cout << "tail -> head: " << endl;

    while( g != NULL )
    {
        cout << g->m_value << " ";

        g = g->m_left;
    }

    cout << endl;
}

// 方法1 :不使用其他数据结构中序遍历线索化二叉树
//        思想：边中序遍历边线索化
// node : 根结点,也是中序访问的结点
// pre  : 为中序遍历时的前驱结点指针
template < typename T >
void inOrderThread(BTreeNode<T>* node, BTreeNode<T>*& pre)
{
    if( node != NULL )    // 不为空树
    {
        // 递归处理左子树
        // 这一步之后左子树就全部线索化了，并且pre指向左子树线索化后的最后一个结点
        inOrderThread(node->m_left, pre);

        // 将右子树中序遍历的第一个结点的m_left指针指向上面左子树线索化后的最后一个指针
        // 如此左右子树便连接起来了
        node->m_left = pre;

        if( pre != NULL )
        {
            pre->m_right = node;
        }

        pre = node;

        inOrderThread(node->m_right, pre); // 递归处理右子树
    }
}

// 方法1
template < typename T >
BTreeNode<T>* inOrderThread1(BTreeNode<T>* node)
{
    BTreeNode<T>* pre = NULL;

    inOrderThread(node, pre);

    // 上面线索化后 node 可能已经不是首结点了，利用下面操作定位到 首结点位置
    while( (node != NULL) && (node->m_left != NULL) )
    {
        node = node->m_left;
    }

    return node;
}

// 方法2 : 不使用中序遍历直接线索化二叉树
// node : 根结点,也是中序访问的结点
// head : 转换成功后指向双向链表的首结点
// tail : 转换成功后指向双向链表的尾结点
template < typename T >
void inOrderThread(BTreeNode<T>* node, BTreeNode<T>*& head, BTreeNode<T>*& tail)
{
    if( node != NULL )
    {
        BTreeNode<T>* h = NULL;
        BTreeNode<T>* t = NULL;

        inOrderThread(node->m_left, h, t);  // 线索化左子树

        node->m_left = t;

        if( t != NULL )
        {
            t->m_right = node;
        }

        head = (h != NULL) ? h : node;       // 双向链表首结点

        h = NULL;   // 这步不要忘记
        t = NULL;

        inOrderThread(node->m_right, h, t);  // 线索化右子树

        node->m_right = h;

        if( h != NULL )
        {
            h->m_left = node;
        }

        tail = (t != NULL) ? t : node;       // 双向链表尾结点
    }
}

// 方法2
template < typename T >
BTreeNode<T>* inOrderThread2(BTreeNode<T>* node)
{
    BTreeNode<T>* head = NULL;
    BTreeNode<T>* tail = NULL;

    inOrderThread(node, head, tail);

    return head;
}

int main()
{
    BTreeNode<int>* tn = createTree<int>();
    printInOrder(tn);

    cout << endl;

    tn = inOrderThread1(tn);
    printDualList(tn);

    cout << endl;

    BTreeNode<int>* tn2 = createTree<int>();

    tn2 = inOrderThread2(tn2);
    printDualList(tn2);

    return 0;
}
/* 运行结果
3 6 1 0 7 4 2 8 5  (直接中序遍历输出的二叉树)
head -> tail:
3 6 1 0 7 4 2 8 5  (线索化后的顺序遍历)
head -> tail:
5 8 2 4 7 0 1 6 3  (线索化后的顺序遍历)

head -> tail:
3 6 1 0 7 4 2 8 5  (线索化后的顺序遍历)
head -> tail:
5 8 2
*/
