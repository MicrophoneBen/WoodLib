// StackToQueue.h 用栈实现队列
#ifndef _STACKTOQUEUE_H_
#define _STACKTOQUEUE_H_

#include "Queue.h"
#include "LinkQueue.h"
#include "LinkStack.h"

namespace WoodLib
{

template < typename T >
class StackToQueue : public Queue<T>
{
private:
    LinkStack<T> m_stack_in;
    LinkStack<T> m_stack_out;

    // 将 stack_in 中所有的元素移动到 stack_out 栈中
    void move() const
    {
        if( m_stack_out.size() == 0 )  // 在m_stack_out栈为空时，发生数据转移
        {
            while( m_stack_in.size() > 0 )
            {
                // 因为是const函数所以得先去掉成员变量的const属性
                // 或者用mutable修饰成员，但这种方法不推荐；
                const_cast<LinkStack<T>&>(m_stack_out).push(m_stack_in.top());
                const_cast<LinkStack<T>&>(m_stack_in).pop();
            }
        }
    }

public:
    void enQueue(const T& element)
    {
        m_stack_in.push(element);
    }

    void deQueue()
    {
        // 1. 判断并移动元素
        move();

        // 2.出队列（出栈）
        if( m_stack_out.size() > 0 )
        {
            m_stack_out.pop();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T front() const
    {
        // 1. 判断并移动元素
        move();

        // 2.取栈顶元素
        if( m_stack_out.size() > 0 )
        {
            m_stack_out.top();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void clear()
    {
        m_stack_in.clear();
        m_stack_out.clear();
    }

    int length() const
    {
        return (m_stack_in.size() + m_stack_out.size());
    }

    bool isEmpty() const
    {
        return (length() == 0);
    }
};

}

#endif
