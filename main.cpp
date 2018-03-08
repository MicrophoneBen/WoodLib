// main.cpp 循环单链表解决约瑟夫环问题
#include <iostream>
#include "CircleList.h"

using namespace std;
using namespace WoodLib;

// 有n(n>0)个人，从s(s>0)开始计数，数到m的自杀
void Josephus(int n, int s, int m)
{
    CircleList<int> c1;

    // 给 n 个人编号,从 1 开始编号的,可随意设置起始号码(结点数据区存放的编号)
    for(int i=0; i < n; i++)
    {
        c1.insert(i+1);  // 从 1 开始编号的
    }

    // 遍历形式上面变得复杂了，因为循环链表没有一个专门的结束标志
    c1.move(0);

    for(int i = 0; i < c1.length(); c1.next())
    {

        cout << c1.current() << " ";
        i++;
    }

    cout << endl << endl;

    c1.move(s-1, m-1);

    int i = 0;
    while(c1.length() > 0)
    {
        c1.next();
        cout << "(" << (++i) << ")" << c1.current() << " ";  // 自杀的人的编号
        c1.remove(c1.find(c1.current()));   // 移除自杀的的人

        if( i % 7 == 0 )           // 控制格式用的
        {
            cout << endl;
        }
    }

    cout << endl << endl;
}

int main()
{
    Josephus(41, 1, 3);

    return 0;
}
/* 运行结果
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41

(1)3 (2)6 (3)9 (4)12 (5)15 (6)18 (7)21
(8)24 (9)27 (10)30 (11)33 (12)36 (13)39 (14)1
(15)5 (16)10 (17)14 (18)19 (19)23 (20)28 (21)32
(22)37 (23)41 (24)7 (25)13 (26)20 (27)26 (28)34
(29)40 (30)8 (31)17 (32)29 (33)38 (34)11 (35)25
(36)2 (37)22 (38)4 (39)35 (40)16 (41)31

*/
