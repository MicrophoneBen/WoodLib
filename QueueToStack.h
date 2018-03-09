// QueueToStack.h 用队列实现栈
#ifndef _QUEUETOSTACK_H_
#define _QUEUETOSTACK_H_

#include "Stack.h"
#include "LinkQueue.h"
#include "LinkStack.h"

namespace WoodLib
{

template < typename T >
class QueueToStack : public Stack<T>
{
private:
    LinkQueue<T> m_queue1;
    LinkQueue<T> m_queue2;

    LinkQueue<T>* m_pIn;   // 不能够用引用，因为这两个指向是不定的，而引用是指针常量，一旦初始化后就不能改变；
    LinkQueue<T>* m_pOut;  // 故这里只能够用指针，这个地方也就体现了指针和引用在使用上的一个区别；

    // 将in队列中的前n-1个元素转移到out队列中
    void move() const
    {
        /*
        // 这样写犯了严重错误，因为循环体中 m_pIn->deQueue() 会改变m_pIn->length()的值
        // 导致出现不是预期的循环次数，这样的情况，必须拿出来单独设置一个变量
        for(int i=0; i < m_pIn->length() - 1; i++)
        {
            m_pOut->enQueue(m_pIn->front());
            m_pIn->deQueue();
        }
        */
        int n = m_pIn->length() - 1;

        for(int i=0; i < n; i++)
        {
            m_pOut->enQueue(m_pIn->front());
            m_pIn->deQueue();
        }
    }

    // 交换进出队列
    void swap()
    {
        LinkQueue<T>* tmp = m_pIn;
        m_pIn = m_pOut;
        m_pOut = tmp;
    }

public:
    QueueToStack()
    {
        m_pIn = &m_queue1;
        m_pOut = &m_queue2;
    }

    void push(const T& element)
    {
        m_pIn->enQueue(element);
    }

    void pop()
    {
        if( m_pIn->length() > 0 )
        {
            //1. 转移元素
            move();

            //2.出栈
            m_pIn->deQueue();

            //3. 交换进出队列角色
            swap();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top() const
    {
        if( m_pIn->length() > 0 )
        {
            //1. 转移元素
            move();

            //2. 返回in队列的栈顶元素
            return m_pIn->front();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    void clear()
    {
        m_queue1.clear();
        m_queue2.clear();
    }

    int size() const
    {
        return (m_queue1.length() + m_queue2.length());
    }
};

}

#endif
