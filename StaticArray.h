#ifndef _STATICARRAY_H_
#define _STATICARRAY_H_

#include "Array.h"

namespace WoodLib
{

template < typename T, int N >
class StaticArray : public Array<T>
{
private:
    T m_space[N];

public:
    StaticArray()
    {
        this->m_array = m_space;
    }

    // 重载拷贝构造
    StaticArray(const StaticArray<T, N>& obj)
    {
        this->m_array = m_space;

        for(int i=0; i<obj.length(); i++)
        {
            m_space[i] = obj.m_space[i];
        }
    }

    // 重载赋值操作
    StaticArray<T, N>& operator =(const StaticArray<T, N>& obj)
    {
        if( &obj != this )
        {
            for(int i=0; i<obj.length(); i++)
            {
                m_space[i] = obj.m_space[i];
            }
        }

        return *this;
    }

    int length() const
    {
        return N;
    }
};

}

#endif
