// DualCircleLink.h 双向循环链表类
#ifndef _DUALCIRCLELINKLIST_H_
#define _DUALCIRCLELINKLIST_H_

#include "LinuxList.h"
#include "DualLinkList.h"

namespace WoodLib
{

template < typename T >
class DualCircleLinkList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
        list_head head;  // 指针域
        T value;         // 数据域
    };

    list_head m_header;    // 定义头结点，因为类型与父类不一样，所以重新定义
    list_head* m_current;  // 游标，类型与父类不一样，所以这里重新定义

    list_head* position(int index) const
    {
        // const 函数不能对成员变量取地址，需去掉 const 限定
        // LinkList类中用mutable修饰m_header;更推荐现在这里使用的这种方法
        list_head* ret = const_cast<list_head*>(&m_header);

        for(int pos=0; pos < index; pos++)
        {
            ret = ret->next;
        }

        return ret;
    }

    int mod(int index) const
    {
        return (this->m_length == 0) ? 0 : (index % this->m_length);
    }

public:
    DualCircleLinkList()
    {
        this->m_length = 0;
        this->m_step = 1;

        m_current = NULL;

        // 初始化 Linux 内核链表，形成循环链表
        INIT_LIST_HEAD(&m_header);
    }

    bool insert(int index, const T& element)  // 在任意位置头部插入
    {
        bool ret = true;

        index = index % (this->m_length + 1);

        Node* node = new Node();

        if( node != NULL )
        {
            node->value = element;

            list_add_tail(&(node->head), position(index)->next);

            this->m_length++;
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "No memrey to insert new element ...");
        }

        return ret;
    }

    virtual bool insert(const T& element)   // 尾部插入
    {
        insert(this->m_length, element);
    }

    bool remove(int index)
    {
        bool ret = true;

        index = mod(index);

        ret = (0 <= index) && (index < this->m_length);

        if( ret )
        {
            list_head* toDel = position(index)->next;

            // 当删除的结点恰好是游标m_current指着的结点时,将游标
            // 手动的移到toDel->next,这样游标就始终指着一个有效结点
            if( toDel == m_current )
            {
                m_current = m_current->next;
            }

            list_del(toDel);

            this->m_length--;

            // toDel 只是结点中的指针域部分，通过list_entry获得结点地址
            // list_entry 实际就是 container_of宏，传参head是结点中
            // 的一个成员 这个类中最开始处就定义了的
            delete list_entry(toDel, Node, head);
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }

        return ret;
    }

    int find(const T element) const    // O(n)
    {
        int ret = -1;   // 没找到返回 -1
        int index = 0;  // 用来标记下标的

        list_head* slider = NULL; // 保存遍历的结点中的指针用的

        list_for_each(slider, &m_header)
        {
            if( list_entry(slider, Node, head)->value == element )
            {
                ret = index;
                break;
            }

            index++;
        }

        return ret;
    }

    bool set(int index, const T& element)
    {
        bool ret = true;

        index = mod(index);

        ret = (0 <= index) && (index < this->m_length);

        if( ret )
        {
            list_entry(position(index)->next, Node, head)->value = element;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }

        return ret;

    }

    bool get(int index, T& element) const
    {
        bool ret = true;

        index = mod(index);

        ret = (0 <= index) && (index < this->m_length);

        if( ret )
        {
            element = list_entry(position(index)->next, Node, head)->value;
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
        bool ret = (0 < step) && (step < this->m_length);

        index = mod(index);

        ret = ret && (0 <= index) && (index < this->m_length);

        if( ret )
        {
            m_current = position(index)->next;
            this->m_step = step;
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
        return (m_current == NULL) || (this->m_length == 0);
    }

    // 返回当前结点中数据域的值
    virtual T current()
    {
        if( !isEnd() )
        {
            return list_entry(m_current, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    // 重写父类的 next() 目的：跳过头结点
    bool next()
    {
        int i = 0;

        while( (i < this->m_step) && !isEnd() )
        {
            // 只有非头结点 i 才计数，头结点跳过不计数
            m_current = m_current->next;

            if( m_current != &m_header )
            {
                i++;
            }
        }

        // 再判断一次是不是又指向了头结点
        if( m_current == &m_header )
        {
            m_current = m_current->next;
        }

        return (i == this->m_step);
    }

    // 重写父类的 pre() 目的：跳过头结点
    bool pre()
    {
        int i = 0;

        while( (i < this->m_step) && !isEnd() )
        {
            // 只有非头结点 i 才计数，头结点跳过不计数
            m_current = m_current->prev;

            if( m_current != &m_header )
            {
                i++;
            }
        }

        // 再判断一次是不是又指向了头结点
        if( m_current == &m_header )
        {
            m_current = m_current->prev;
        }

        return (i == this->m_step);
    }

    int length() const
    {
        return this->m_length;
    }

    void clear()
    {
        while( this->m_length > 0 )
        {
            remove(0);
        }
    }

    ~DualCircleLinkList()
    {
        clear();
    }
};

}

#endif
