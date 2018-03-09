#ifndef _STATICQUEUE_H_
#define _STATICQUEUE_H_

#include "Queue.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T, int N >
class StaticQueue : public Queue<T>
{
private:
    T m_space[N];   // 队列存储空间

    int m_rear;     // 队尾标识
    int m_front;    // 队头标识
    int m_length;   // 当前队列的长度

public:
    StaticQueue()   // 初始化成员变量
    {
        m_rear = 0;
        m_front = 0;
        m_length = 0;
    }

    ~StaticQueue()  // 队列最大容量
    {

    }

    int capacity() const
    {
        return N;
    }

    void enQueue(const T& element)
    {
        if( m_length < N )
        {
            m_space[m_rear] = element;
            m_rear = (m_rear + 1) % N;   // 当m_rear等于N-1，计算结果m_rear等于0，
                                         // 若此时m_front=0，则此时队列满
                                         // 队列数据是在循环覆盖的过程
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "No space in current queue ...");
        }
    }

    void deQueue()
    {
        if( m_length > 0 )
        {
            m_front = (m_front + 1) % N;
            m_length--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T front() const    // 获取队头元素，注意并没有出队列
    {
        if( m_length > 0 )
        {
            return m_space[m_front];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void clear()         // 清空队列，作为容器类都会设计的一个方法
    {
        m_length = 0;
        m_rear = 0;
        m_front = 0;
    }

    int length() const    // 获取队列的长度
    {
        return m_length;
    }

    bool isEmpty() const  // 判断队列是否为空
    {
        return ( 0 == m_length );
    }
};

};

#endif

