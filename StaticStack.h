// StaticStack.h 基于顺序存储结构的栈
#ifndef _STATICSTACK_H_
#define _STATICSTACK_H_

#include "Stack.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T, int N >
class StaticStack : public Stack<T>
{
private:
    T m_space[N];  // 栈空间
    int m_top;     // 模拟栈顶指针
    int m_size;    // 栈当前的大小

public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }

    ~StaticStack()
    {

    }

    int capacity() const
    {
        return N;
    }

    void push(const T& element)
    {
        if( m_size < N )
        {
            // 要注意确保异常安全，即如果 T 类的“=” 赋值操作符发生异常时
            // m_top 和 m_size 没被改变。
            m_space[m_top+1] = element;

            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current Stack ...");
        }
    }

    void pop()
    {
        if( m_size > 0 )
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current Stack ...");
        }
    }

    T top() const
    {
        if( m_size > 0 )
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current Stack ...");
        }

    }

    void clear()
    {
        m_top = -1;
        m_size = 0;
    }

    int size() const
    {
        return m_size;
    }

};

}


#endif
