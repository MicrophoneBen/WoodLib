// DualLinkList.h 双向链表类
#ifndef _DUALLINKLIST_H_
#define _DUALLINKLIST_H_

#include "List.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T >
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;     // 数据域
        Node* next;  // 后向指针域
        Node* prev;  // 前向指针域
    };

    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
        Node* prev;
    }m_header;        // DualLinkList<T>在构造时会创建这个成员变量

    int m_length;     // 链表长度

    Node* m_current;  // 保存当前游标所代表的结点地址
    int m_step;       // 游标每步移动的长度

    Node* position(int index) const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for(int pos=0; pos < index; pos++)
        {
            ret = ret->next;
        }

        return ret;
    }

    virtual Node* creatNode()
    {
        return new Node();
    }

    virtual void destroyNode(Node* pn)
    {
        delete pn;
    }

public:
    DualLinkList()
    {
        m_header.next = NULL;
        m_header.prev = NULL;

        m_current = NULL;
        m_step = 1;
        m_length = 0;
    }

    bool insert(int index, const T& element)  // 在任意位置头部插入
    {
        bool ret = ( (0 <= index) && (index <= m_length) );

        if( ret )
        {
            Node* node = creatNode();

            if( node != NULL )
            {
                node->value = element;

                Node* current = position(index);
                Node* next = current->next;

                node->next = next;
                current->next = node;

                if( current != reinterpret_cast<Node*>(&m_header) )
                {
                    node->prev = current;
                }
                else
                {
                    node->prev = NULL;
                }

                if( next != NULL )  // 这个判断必不可少,否则尾插时程序运行死掉
                {
                    next->prev = node;
                }
                // 当 next 指针为空时就是链表尾插的情况,此时就没必要对
                // NULL->prev 操作了吧,操作运行那流死翘翘了哦,故没有 else 分支

                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "No memrey to insert new element ...");
            }

        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }

        return ret;
    }

    virtual bool insert(const T& element)   // 尾部插入
    {
        insert(m_length, element);
    }

    bool remove(int index)
    {
        bool ret = ( (0 <= index) && (index < m_length) );

        if( ret )
        {
            Node* current = position(index);

            Node* toDel = current->next;

            Node* next = toDel->next;

            current->next = next;

            if( NULL != next )
            {
                next->prev = toDel->prev;
            }

            // 当删除的结点恰好是游标m_current指着的结点时,将游标
            // 手动的移到toDel->next,这样游标就始终指着一个有效结点
            if( toDel == m_current )
            {
                m_current = m_current->next;
            }

            m_length--;
            // delete toDel; 如果Node析构中抛异常时会出现异常不安全行
            // 为必须保证其之后的--m_length移动在该句之前,以保证异常安全
            destroyNode(toDel);
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }

        return ret;
    }

    virtual void reverse()   // 链表反转
    {
        // 方法二：不用现有函数，完全独立   // O(n)
        // 思想：从节点0按链表顺序逐个反转，最后与头结点挂接
        Node* curr = m_header.next;
        Node* pre = NULL;
        Node* nex = NULL;

        while(curr != NULL)
        {
            nex = curr->next;  // 保存当前位置的后继结点的指针

            curr->next = pre;  // 反转操作

            pre = curr;        // 更新pre指针

            curr = nex;        // 更新curr指针
        }

        m_header.next = pre;   // 与头结点挂接
    }

    int find(const T element) const    // O(n)
    {
        // 这个比上面效率高一些
        int ret = -1;

        Node* node = m_header.next;
        int i = 0;

        while( node != NULL )
        {
            if( node->value == element )
            {
                ret = i;
                break;
            }

            node = node->next;

            i++;
        }

        return ret;
    }

    bool set(int index, const T& element)
    {
        bool ret = ( (0 <= index) && (index < m_length) );

        if( ret )
        {
            (position(index)->next)->value = element;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }

        return ret;

    }

    bool get(int index, T& element) const
    {
        bool ret = ( (0 <= index) && (index < m_length) );

        if( ret )
        {
            element = (position(index)->next)->value;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }

        return ret;
    }

    // 上面函数操作很不方便，重载一个这样的出来
    virtual T get(int index) const
    {
        T ret;

        if( get(index, ret) )
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }
    }

    // 游标设置到index位置 以后游标每次移动step的长度，默认为游标步长为1
    virtual bool move(int index, int step = 1)
    {
        bool ret = (0 <= index) && (index < m_length);
        ret = ret && (0 < step) && (step < m_length);

        if( ret )
        {
            m_current = position(index)->next;
            m_step = step;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter is invalid ...");
        }

        return ret;
    }

    // 检测是否到链表尾结点
    virtual bool isEnd()
    {
        return (m_current == NULL);
    }

    // 返回当前结点中数据域的值
    virtual T current()
    {
        if( !isEnd() )
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    // 移动游标到下一个结点(执行一次这个函数游标移动 m_step 个结点)
    virtual bool next()
    {
        int i = 0;

        while( (i < m_step) && !isEnd() )
        {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);
    }

    virtual bool pre()
    {
        int i = 0;

        while( (i < m_step) && !isEnd() )
        {
            m_current = m_current->prev;
            i++;
        }

        return (i == m_step);
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        while( m_length > 0 )
        {
            remove(0);
        }
    }

    ~DualLinkList()
    {
        clear();
    }
};

}

#endif
