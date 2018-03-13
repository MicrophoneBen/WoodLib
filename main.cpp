// main.cpp  利用递归思想 进行 回溯算法的设计
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "QueenSolution.h"

using namespace std;
using namespace WoodLib;

// 递归实现单向链表反转
struct Node
{
    int value;
    Node* next;
};

// 创建无表头结点的单链表（己填充数据）： v 结点的值， len 链表长度
Node* creatList(int v, int len)
{
    Node* ret = NULL;
    Node* slider = NULL;

    for(int i=0; i<len; i++)
    {
        Node* node = new Node();

        node->value = v++;
        node->next = NULL;

        if( NULL == slider )   // 首结点
        {
            slider = node;
            ret = node;
        }
        else
        {
            slider->next = node;
            slider = node;
        }
    }

    return ret;
}

void destroyList(Node* list)
{
    while( list )
    {
        Node* del = list;
        list = list->next;

        delete del;
    }
}

void printList(Node* list)
{
    while( list )
    {
        cout << "[" << list->value << "]" << "->";
        list = list->next;
    }

    cout << "NULL" << endl;
}

Node* reverse(Node* list)
{
    Node* ret = NULL;

    if( (NULL == list ) || (NULL == list->next) )  // 注意是 || 逻辑
    {
        ret = list;
    }
    else
    {
        Node* guard = list->next;
        ret = reverse(list->next);  // 注意不要忘了返回值
        guard->next = list;
        list->next = NULL;
    }

    return ret;
}

// 单向排序链表的合并(前提两个list1和list2已经排好序)
Node* merge(Node* list1, Node* list2)
{
    Node* ret = NULL;

    if( NULL == list1 )
    {
        ret = list2;
    }
    else if( NULL == list2 )
    {
        ret = list1;
    }
    else if( list1->value < list2->value )          // 取出子链表的第 1 个结点并比较
    {
        //Node* list1_new = list1->next;            // 去掉list1首结点的新的list1
        //Node* list_new = merge(list1_new, list2); // 将上面新的list1 和 原来的 list2 合并
        //list1->next = list_new;                   // 单独拿出来的list1的首结点指向新合并生成的链表
        //ret = list1;                              // 返回最后的链表首结点

        // 上面四句可以改写为下面一句 利用了逗号表达式
        // 由于当前 list1 结点的值较小，取出当前结点，其 next
        // 指向由该结点后继的子链表和 list2 合并的新链表
        ret = (list1->next = merge(list1->next, list2), list1);
    }
    else if( list1->value >= list2->value)
    {
        //Node* list2_new = list2->next;
        //Node* list_new = merge(list2_new, list1);
        //list2->next = list_new;
        //ret = list2;

        // 上面四句可以改写为下面一句 利用了逗号表达式
        // list2 当前结点的值较小
        ret = (list2->next = merge(list1, list2->next), list2);
    }

    return ret;
}

// 逆序打印单链表中的偶数结点
void printRevese(Node* list)
{
    if(list != NULL)
    {
        // 深度搜索，直到最后一个节点
        printRevese(list->next);

        // 回溯算法设计：上一行递归结束，开始回溯并判断节点的值是否为偶数
        if(list->value % 2 == 0)
        {
            cout << list->value << " ";
        }
    }
}

// 汉诺塔 将 n 个木块 由 a 借助 b 移动到 c
void HanoiTower(int n, char a, char b, char c)
{
    if( 1 == n )
    {
        cout << a << "-->" << c << endl;
    }
    else
    {
        HanoiTower(n-1, a, c, b); // 将 n-1 块，从 a 柱借 c 柱移动到 b 柱
        HanoiTower(1, a, b, c);   // 将 a 柱剩下的最后一块移到 c 柱上
        HanoiTower(n-1, b, a, c); // 将 b 柱中的 n-1 块借助 a 柱移到 c 柱。
    }
}

// 全排列 对 s 全排列 将全排列好的由 e 输出，e始终指向s
void permutation(char* s, char* e)
{
    if(*s == '\0')
    {
        cout << e << endl; // 打印出全排列好的字符串
    }
    else
    {
        int len = strlen(s);

        // 如将 abc
        // 1.第 1 轮：将 abc 变成以 a 开头，然后全排列 bc
        // 2.第 2 轮：将 abc 变成以 b 开头，然后全排列 ac
        // 3.第 3 轮：将 abc 变成以 c 开头，然后全排列 ba
        for(int i=0; i<len; i++)
        {
            if((i == 0) || (s[0] != s[i])) // 去重复，如 aba 就不交换两个 a
            {
                // swap() 调用的 C++库函数
                swap(s[0], s[i]);    // 以 s[0]开头(每轮会变化） ,全排列其后的子串
                permutation(s+1, e); // 递归 s+1 指针指向下一个字符 全排列子串
                swap(s[0], s[i]);    // 恢复为原来的串,如 abc,以便下一轮全排列
            }
        }
    }
}

int main()
{
    // 测试1：逆序打印单链表中的偶数结点
    Node* list = creatList(1, 10);

    printList(list);
    printRevese(list);

    cout << endl << endl;

    // 测试2：八皇后解决方案
    QueenSolution<8> qs;
    qs.solve();

    return 0;
}
/* 运行结果
[1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->[10]->NULL
10 8 6 4 2

(0, 0) (4, 1) (7, 2) (5, 3) (2, 4) (6, 5) (1, 6) (3, 7)
...#....
.#......
......#.
..#.....
.....#..
.......#
....#...
#.......

(0, 0) (5, 1) (7, 2) (2, 3) (6, 4) (3, 5) (1, 6) (4, 7)
....#...
.#......
...#....
......#.
..#.....
.......#
.....#..
#.......

(0, 0) (6, 1) (3, 2) (5, 3) (7, 4) (1, 5) (4, 6) (2, 7)
..#.....
....#...
.#......
.......#
.....#..
...#....
......#.
#.......

中间还有88种方案的棋盘省略不列出来了...

(7, 0) (3, 1) (0, 2) (2, 3) (5, 4) (1, 5) (6, 6) (4, 7)
....#...
......#.
.#......
.....#..
..#.....
#.......
...#....
.......#

total : 92
*/
