#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "Object.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T >
class Array : public Object
{
protected:
    T* m_array;

public:
    bool set(int index, const T& element)
    {
        bool ret = ( (0 <= index) && (index < length()) );

        if( ret )
        {
            m_array[index] = element;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }

        return ret;
    }

    bool get(int index, const T& element)
    {
        bool ret = ( (0 <= index) && (index < length()) );

        if( ret )
        {
            element = m_array[index];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }

        return ret;
    }

    // 内置数组中数组长度是无法直接获得的，这个数组类可以获得,在子类中获得
    virtual int length() const = 0;

    // 数组访问操作符  针对非const对象
    T& operator [](int index)
    {
        if( (0 <= index) && (index < length()) )
        {
            return m_array[index];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
        }
    }

    // 数组访问操作符  针对const对象
    T operator [](int index) const
    {
        return (const_cast<Array<T>&>(*this))[index];
    }
};

}

#endif
