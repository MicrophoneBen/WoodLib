// CircleList.h 循环单链表
#ifndef _CIRCLELIST_H_
#define _CIRCLELIST_H_

#include "LinkList.h"

namespace WoodLib
{

template < typename T >
class CircleList : public LinkList<T>
{
private:
    typedef typename LinkList<T>::Node Node;

    // 取模
    int mod(int index) const
    {
        return (this->m_length == 0) ? 0 : (index % this->m_length);
    }

    // 尾结点
    Node* last() const
    {
        return this->position(this->m_length-1)->next;
    }

    // 尾结点和首结点连接在一起形成环
    void makeCircle() const
    {
        if( this->m_header.next )  // 前提首结点存在时,即存在链表
        {
            last()->next = this->m_header.next;  // 尾结点指针指向首结点
        }
    }

public:
    bool insert(int index, const T& element)
    {
        bool ret = true;

        // 注意这里是对 m_length+1 取模,不是 m_length
        // 仔细理解,理解关键是当这个结点是要插入到链表的尾部时
        index = index % (this->m_length + 1);

        // 调用 LinkList 父类的插入函数
        ret = LinkList<T>::insert(index, element);

        // 插入 0 位置时，加一步首尾相连的特殊处理
        if( ret && (0 == index) )
        {
            makeCircle();
        }

        return ret;
    }

    // 尾插
    bool insert(const T& element)
    {
        return insert(this->m_length, element);
    }

    // 移除下标为 index 的结点
    bool remove(int index)
    {
        bool ret = true;

        index = mod(index);

        // 删除 0 位置时
        if( 0 == index )
        {
            Node* toDel = this->m_header.next;

            if( toDel != NULL )  // 首结点存在
            {
                this->m_header.next = toDel->next;

                this->m_length--;

                if( this->m_length > 0 )
                {
                    makeCircle();

                    if( this->m_current == toDel )
                    {
                        this->m_current = toDel->next;
                    }
                }
                else
                {
                    this->m_header.next = NULL;
                    this->m_length = 0;
                }

                this->destroyNode(toDel);
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = LinkList<T>::remove(index);  // 删除其他位置(非 0 位置)的结点
        }

        return ret;
    }

    int find(const T element) const
    {
        int ret = -1;

        Node* slider = this->m_header.next;

        for(int i=0; i < this->m_length; i++)
        {
            if( slider->value == element )
            {
                ret = i;
                break;
            }

            slider = slider->next;
        }

        return ret;
    }

    bool set(int index, const T& element)
    {
        return LinkList<T>::set(mod(index), element);
    }

    bool get(int index, T& element) const
    {
        return LinkList<T>::get(mod(index), element);
    }

    T get(int index) const
    {
        return LinkList<T>::get(mod(index));
    }

    int length() const
    {
        return this->m_length;
    }

    void clear()
    {
        while( this->m_length > 1 )
        {
            // remove(1)而不 remove(0)是因为避开
            // 删除首结点而导致效率低下的问题
            // 因为用remove(0)则每次都得 调用 makeCircle()
            // 维持环的状态，所以效率低下
            remove(1);
        }

        if( 1 == this->m_length )
        {
            Node* toDel = this->m_header.next;

            this->m_header.next = NULL;

            this->m_length = 0;

            this->destroyNode(toDel);
        }
    }

    // 将父类 LinkList 中遍历相关的全部设置为虚函数
    // 本类中重写 move() end() 另外两个不需要重写
    bool move(int index, int step = 1)
    {
        return LinkList<T>::move(mod(index), step);
    }

    // 这个与 remove()相结合使用，但是这样会将链表中元素都一个个移除了
    // 不就改变链表状态了吗，故觉得这个遍历判断尾结点是不太妥的？ 怎么改进？？？
    bool isEnd()
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    ~CircleList()
    {
        clear();
    }
};

}

#endif
