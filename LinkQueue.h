// LinkQueue.h 链式队列类（组合LinkList单链表类实现）
#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

#include "Queue.h"
#include "LinkList.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T >
class LinkQueue : public Queue<T>
{
private:
    LinkList<T> m_list;

public:
    ~LinkQueue()
    {

    }

    void enQueue(const T& element)   // O(n),效率低！
    {
        m_list.insert(element);      // 每次需要遍历到尾部插入
    }

    void deQueue()                   // O(1)
    {
        if( m_list.length() > 0 )
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T front() const
    {
        if( m_list.length() > 0 )
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void clear()
    {
        m_list.clear();
    }

    int length() const
    {
        return m_list.length();
    }

    bool isEmpty() const
    {
        return (m_list.length() == 0);
    }
};

}

#endif
