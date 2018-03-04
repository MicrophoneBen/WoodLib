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

public:
    DynamicArray(int length)
    {
        // 1. 分配新内存
        this->m_array = new T[length];

        // 2. 设置变量
        if( this->m_array != NULL )
        {
            m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to create DynamicArray Object ...");
        }
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }

    // 重载拷贝构造
    DynamicArray(const DynamicArray<T>& obj)
    {
        // 1. 分配新内存
        this->m_array = new T[obj.length()];

        if( this->m_array != NULL )
        {
            // 2. 拷贝数组
            for(int i=0; i<obj.length(); i++)
            {
                this->m_array[i] = obj.m_array[i];
            }

            // 3.设置变量（如长度信息）
            m_length = obj.m_length;
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to DyanmicArray Object ...");
        }
    }

    // 重载赋值操作
    DynamicArray<T>& operator =(const DynamicArray<T>& obj)
    {
        if( this != &obj )
        {
            // 1. 分配新内存
            T* array = new T[obj.length()];

            if( array != NULL )
            {
                // 2. 拷贝数组
                for(int i=0; i<obj.length(); i++)
                {
                    array[i] = obj.m_array[i];
                }

                // 3. 设置变量
                T* tmp = this->m_array;  // 先设置参数，再删除m_array以确保异常安全

                this->m_array = array;
                m_length = obj.length();

                delete tmp[];           // 注意指向的是个数组
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to DyanmicArray Object ...");
            }
        }

        return *this;
    }

    void resize(int length)
    {
        if( length != m_length )
        {
            // 1.分配新内存
            T* array = new T[length];

            if( array != NULL )
            {
                int len = length < m_length ? length : m_length;

                // 2. 拷贝数组
                for(int i=0; i<len; i++)
                {
                    array[i] = this->m_array[i];  
                }

                // 3. 设置变量
                T* tmp = this->m_array;  // 先设置参数，再删除m_array以确保异常安全

                this->m_array = array;
                m_length = length;

                delete tmp[];            // 注意指向的是个数组
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to resize DynamicArray Object ...");
            }
        }
    }

    int length() const
    {
        return m_length;
    }
};

}

#endif
