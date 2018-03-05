// LinkList类 线性表链式存储结构之单链表类
#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include "List.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T >
class LinkList : public List<T>
{
protected:
    // 结点类型（内部类，C++中struct也是类）
    // 因为可能需要涉及到T类型对象创建,那么就有可能需要new,故也要继承自Object
    struct Node : public Object
    {
        T value;     // 数据域
        Node* next;  // 指针域
    };

    // 由于m_header在定义时会调用T的构造函数。如果T的设计者在构造
    // 函数中抛出异常，当LinkList<T> list时会产生异常。这时调用
    // 者可能会怀疑是LinkList设计出了问题，而不会认为是T的问题，
    // 因为他根本就没有手工定义T的对象（如：T t），为了防止这种现
    // 象的出现，可“借尸还魂”，防止在定义m_header时调用T的构造函数。

    // mutable Node m_header;  // 头结点

    // “借尸还魂”:定义一个与Node内存模型完全一样的结构体，防止调
    // 用T的构造函数（因为这只是个头结点，关心的是next指针域，而
    // 不是数据域的东西）

    // 为了保证和 Node m_header 一样的内存布局，也继承自Object
    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
    }m_header;        // LinkList<T>在构造时会创建这个成员变量

    int m_length;     // 链表长度

    Node* m_current;  // 保存当前游标所代表的结点地址
    int m_step;       // 游标每步移动的长度

    // 找到指向第 [index] 结点的前一个结点的指针
    // 譬如：index==0 ==> ret==头结点； index==5 ==> ret==第[4]个结点的地址；
    // 必须这样设计，因为插入、删除等操作都是需要 目标位置的 前一个结点配合的
    // 而目标位置的 地址 则可以用 这个函数的返回值->next 确定；
    // 若 return ret->next,这样返回的就是 [index]结点的地址，那么这样就只能得到
    // 目标位置和目标位置的下一个结点的地址了，这样没法进行 插入、删除等操作。
    Node* position(int index) const
    {
        // 由于const对象不能修改成员变量的值,对m_header取地址就
        // 可能会修改m_header的值，可将m_header声明为mutable
        Node* ret = reinterpret_cast<Node*>(&m_header);

        // 最开始思维发生了一个恶心的错误，竟然认为for循环执行流是：
        // pos=0 -> {}中代码 -> pos++ -> 判断pos<index -> {}代码
        // 正确的应该是：
        // pos=0 -> 判断pos<index -> {}中代码 -> pos++ -> 判断pos<index -> {}代码
        for(int pos=0; pos < index; pos++)
        {
            ret = ret->next;
        }

        return ret;
    }

    // vitual 封装节点创建和销毁函数，用多态技术区分父类和子类的new 和 delete
    virtual Node* creatNode()
    {
        new Node();
    }

    virtual void destroyNode(Node* pn)
    {
        delete pn;
    }

public:
    LinkList()
    {
        m_header.next = NULL;
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
                node->next = current->next;
                current->next = node;

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

    bool insert(const T& element)   // 尾部插入
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

            current->next = toDel->next;

            destroyNode(toDel);

            m_length--;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }

        return ret;
    }

    void reverse()   // 链表反转
    {
#if 0
        // 方法一：充分利用现有的 position()
        // 思想：每次取最后一个依次插入
        for(int i=0; i < m_length-1; i++)
        {
            Node* end = position(m_length-1);

            end->next->next = position(i)->next;

            position(i)->next = end->next;

            end->next = NULL;
        }
#else
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

#endif
    }

    int find(const T element) const    // O(n)
    {
#if 0
        int ret = -1;

        for(int i=0; i<m_length; i++)
        {
            if( (position(i)->next)->value == element )
            {
                ret = i;
                break;
            }
        }

        return ret;
#else
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
#endif
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
    T get(int index) const
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
    bool move(int index, int step = 1)
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
    bool isEnd()
    {
        return (m_current == NULL);
    }

    // 返回当前结点中数据域的值
    T current()
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
    bool next()
    {
        int i = 0;

        while( (i < m_step) && !isEnd() )
        {
            m_current = m_current->next;
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
        while(m_header.next)
        {
            Node* toDel = m_header.next;

            m_header.next = toDel->next;

            destroyNode(toDel);
        }

        m_length = 0;
    }

    ~LinkList()
    {
        clear();
    }
};

}

#endif
