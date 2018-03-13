// QueenSolution.h  N皇后问题解决方法类
#ifndef _QUEENSOLUTION_H_
#define _QUEENSOLUTION_H_

#include "Object.h"
#include "LinkList.h"

namespace WoodLib
{

template < int N >
class QueenSolution : public Object
{
private:
    struct Pos : public Object
    {
        Pos(int px = 0, int py = 0) : x(px), y(py) { }

        int x;
        int y;
    };

    int m_chess_board[N][N];  // 棋盘(左下角原点 0， x 轴正方向向右， y 轴正方向向上)
    Pos m_direction[3];       // 三个方向向量 (左下角 向下 右下角)，按从下至上从左至右顺序找位置，所以其他方向不需要
    LinkList<Pos> m_solution; // 用单向链表保存结果
    int m_count;              // 有多少种解决方案

    void init()
    {
        m_count = 0;

        // 初始化棋盘，全部置0
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<N; j++)
            {
                m_chess_board[i][j] = 0;
            }
        }

        // 初始化方向矢量，利用构造函数初始化
        m_direction[0] = Pos(-1, -1);   // 左下角方向
        m_direction[1] = Pos(0, -1);    // 正下方方向
        m_direction[2] = Pos(1, -1);    // 右下方方向
    }

    // 打印出皇后位置坐标点，已及棋盘内容
    void print()
    {
        // 按 (x, y) 的格式输出皇后所放置的坐标
        for(m_solution.move(0); !m_solution.isEnd(); m_solution.next())
        {
            std::cout << "(" << m_solution.current().x << ", " \
                 << m_solution.current().y << ")" << " ";
        }

        std::cout << std::endl;

        // 打印出整个棋盘，空白地方用 "." 表示，放置皇后的地方用 "#" 表示
        for(int i=N-1; i>=0; i--)
        {
            for(int j=0; j<N; j++)
            {
                switch (m_chess_board[j][i])   // 注意这里ij控制输出的棋盘原点，这里左下角为原点
                {
                case 0:
                    std::cout << ".";
                    break;
                case 1:
                    std::cout << "#";
                    break;
                default:
                    break;
                }
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    // 判断(x, y)这个点是不是在棋盘内的（检测是否到棋盘边界了）
    bool isInner(int x, int y)
    {
        return (0 <= x) && (x < N) && (0 <= y) && (y < N);
    }

    // 检测在棋盘的（x， y）位置是否可以放置皇后 d 表示检测方向
    // direction：0 左下角、 1 向下、 2 右下角
    // 返回 true 可以放置皇后 false 不可以放置皇后
    bool check(int x, int y, int direction)
    {
        bool ret = (0 <= direction) && (direction <=2);

        while( ret && isInner(x, y) )
        {
            // 若存在皇后则 m_chessboard[x][y]=1 反之为 0
            // 即存在皇后 与 ret 就为 false 退出 while 循环
            // 若不存在则 与 ret 就为 true 循环继续 直到(x,y)超出棋盘范围
            // 此时说明这个点可以放置皇后
            ret = ret && (0 == m_chess_board[x][y]);

            // (x, y) 不断移动 在 d 方向上检测是否已经有皇后存在
            x += m_direction[direction].x;
            y += m_direction[direction].y;
        }

        return ret;
    }

    // 在第 row 行尝试放置皇后
    void place(int row)
    {
        if( row < N )
        {
            int y = row;

            for(int x=0; x<N; x++)
            {
                // 在"左下角 向下 右下角"三个方向检测判断当前位置是否可以放置皇后
                if( check(x, y, 0) && check(x, y, 1) && check(x, y, 2) )
                {
                    m_chess_board[x][y] = 1;      // 标记为 1 表示可以放置皇后
                    m_solution.insert(Pos(x, y)); // 将该位置坐标点加入链表

                    place(y + 1);                 // 在下一行放置皇后

                    // 若 place(row+1) 函数返回了，只有两种情况：
                    // 1、表示前面放置皇后的位置走下去导致 第 row+1 行无法找到放置
                    // 皇后的地方，这样就回溯去掉上一行放置皇后的点，重新找
                    // 2、找到整个N皇后问题的解决方案了，最后一行正常返回走else分支
                    // 结束整个递归
                    m_chess_board[x][y] = 0;      // 回溯,将当前位置的皇后移除
                    m_solution.remove(m_solution.length() - 1);
                }
            }
        }
        else
        {
            // 由于采用深度优先搜索,所以放置到第 N 行时，表示己经找到解决方案
            m_count++;  // 每找到一个方案， m_count 加 1
            print();    // 打印解决方案
        }
    }

public:
    QueenSolution()
    {
        init();
    }

    void solve()
    {
        place(0);   // 从第 0 行开始放置
        std::cout << "total : " << m_count << std::endl;   // 总的可行方案数
    }
};

}

#endif
