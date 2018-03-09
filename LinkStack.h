// LinkStack.h 基于链式存储结构的栈类（简称链式栈）
#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_

#include "Stack.h"
#include "LinkList.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T >
class LinkStack : public Stack<T>
{
private:
    LinkList<T> m_list;

public:
    ~LinkStack()
    {

    }

    void push(const T& element)
    {
        m_list.insert(0, element);  // 在头部插入
    }

    void pop()
    {
        if( m_list.length() > 0 )   // 不要忘记这个判断，else抛出异常；
        {
            m_list.remove(0);       // 头部操作 移除链表中的首结点
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top() const
    {
        if( m_list.length() > 0 )
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    void clear()
    {
        m_list.clear();
    }

    int size() const
    {
        return m_list.length();
    }
};

}

#endif
