#ifndef _DYNAMICARRAY_H_
#define _DYNAMICARRAY_H_

#include "Array.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T >
class DynamicArray : public Array<T>
{
private:
    int m_length;

#if 0
    // 对象构造时的初始化操作
    // 产生程序崩溃的代码
    void init(T* array, int len)    
    {

        array = new T[len];        // arry临时变量,并不是真正的this->m_array  

        if( array != NULL )
        {
            m_length = len;
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to init Object ...");
        }
    }
#endif
    // 对象构造时的初始化操作
    void init(T* array, int len)
    {
        if( array != NULL )
        {
            this->m_array = array;
            m_length = len;
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to init Object ...");
        }
    }

    // 分配内存并拷贝数组
    T* copy(T* array, int len, int newLen)
    {
        T* ret = new T[newLen];

        if( array != NULL )
        {
            int size = (len < newLen) ? len : newLen;

            for(int i=0; i<size; i++)
            {
                ret[i] = array[i];
            }
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to copy Object ...");
        }

        return ret;
    }

    // 将指定的堆空间设置为内部存储数组
    void updata(T* array, int len)
    {
        // 先设置变量，再删除 确保异常安全！
        T* tmp = this->m_array;

        this->m_array = array;
        m_length = len;

        delete[] tmp;
    }

public:
    DynamicArray(int length = 0)
    {
        //init(this->m_array, length);   // 产生程序运行崩溃的代码
        init(new T[length], length);
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }

    // 重载拷贝构造
    DynamicArray(const DynamicArray<T>& obj)
    {
        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.length());
    }

    // 重载赋值操作
    DynamicArray<T>& operator =(const DynamicArray<T>& obj)
    {
        if( this != &obj )
        {
            updata(copy(this->m_array, m_length, obj.length()), obj.length());
        }

        return *this;
    }

    void resize(int length)
    {
        if( length != m_length )
        {
            updata(copy(this->m_array, m_length, length), length);
        }
    }

    int length() const
    {
        return m_length;
    }
};

}

#endif
