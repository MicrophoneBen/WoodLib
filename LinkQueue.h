// LinkQueue.h 链式队列类（组合Linux内核双向链表类实现）
#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

#include "Queue.h"
#include "LinuxList.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T >
class LinkQueue : public Queue<T>
{
private:
    struct Node : public Object
    {
        list_head head;  // 指针域
        T value;         // 存储的队列数据
    };

    list_head m_header;  // 头结点
    int m_length;

public:
    LinkQueue()
    {
        m_length = 0;
        INIT_LIST_HEAD(&m_header);
    }

    ~LinkQueue()
    {
        clear();
    }

    void enQueue(const T& element)   // O(1) 常量时间内完成，比组合单链表效率高
    {
        Node* node = new Node();

        if( node != NULL )
        {
            node->value = element;

            // 注意第一个放置队列有效数据元素的结点是 m_header.next
            list_add_tail(&(node->head), &m_header);  // 尾部插入
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memort to add element ...");
        }
    }

    void deQueue()                   // O(1)
    {
        if( m_length > 0 )
        {
            // 注意第一个放置队列有效数据元素的结点是 m_header.next
            // 故出队列第一个结点时 m_header.next
            list_head* toDel = m_header.next;

            list_del(toDel);         // 只是将toDel从链表中断开还没有释放
            m_length--;              // 保证异常安全

            delete list_entry(toDel, Node, head);  // 释放toDel所在结点
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T front() const
    {
        if( m_length > 0 )
        {
            // 注意第一个有效队列结点时 m_header.next
            return list_entry(m_header.next, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void clear()
    {
        while( m_length > 0 )
        {
            deQueue();
        }

    }

    int length() const
    {
        return m_length;
    }

    bool isEmpty() const
    {
        return ( 0 == m_length );
    }
};

}

#endif
