// SequenceList.h 顺序存储线性表抽象类
#ifndef _SEQUENCELIST_H_
#define _SEQUENCELIST_H_

#include "List.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T >
class SequenceList : public List<T>
{
protected:
    T* m_array;     // 顺序存储空间
    int m_length;   // 当前线性表的长度

public:
    bool insert(int index, const T& element)
    {
        bool ret = (0 <= index) && (index <= m_length);

        ret = ret && (m_length < capacity());  // 还没有达到线性表可存储的最大容量

        if( ret )
        {
            for(int pos=m_length-1; pos >= index; pos--)
            {
                m_array[pos+1] = m_array[pos];
            }

            m_array[index] = element;

            ++m_length;
        }

        return ret;
    }

    bool insert(const T& element)  // 重载insert() 实现尾部插入
    {
        insert(m_length, element);
    }

    bool remove(int index)
    {
        bool ret = (0 <= index) && (index < m_length);

        if( ret )
        {
            for(int pos=index; pos < m_length-1; pos++)
            {
                m_array[pos] = m_array[pos + 1];
            }

            --m_length;
        }

        return ret;
    }

    bool set(int index, const T& element)
    {
        bool ret = (0 <= index) && (index < m_length);

        if( ret )
        {
            m_array[index] = element;
        }

        return ret;
    }

    bool get(int index, T& element) const
    {
        bool ret = (0 <= index) && (index < m_length);

        if( ret )
        {
            element = m_array[index];
        }

        return ret;
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        m_length = 0;
    }

    // 因为是顺序存储线性表，所以从使用体验上很有必要重载[]，方便快速访问
    T& operator [](int index)
    {
        if( (0 <= index) && (index < capacity()) )
        {
            return m_array[index];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }
    }

    T operator [](int index) const
    {
        // 调用这个成员函数的是个 const 对象，可以剔除其const熟悉便可复用非const版本 [] 了
        return (const_cast<SequenceList<T>&>(*this))[index];
    }

    // 线性表存储空间的可存储的最大容量
    // 因为顺序存储的位置和大小在子类中去定义，所以当前类中自然就没法获取其
    // 容量大小同时这个类是设计为抽象类需要一个纯虚函数，纯虚函数正好就可以
    // 不提供实现，结合上面，所以将这个函数设为纯虚函数就恰到好处了
    virtual int capacity() const = 0;
};

}

#endif
