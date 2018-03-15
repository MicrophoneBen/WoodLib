#ifndef _SHAREDPOINTER_H_
#define _SHAREDPOINTER_H_

#include "Pointer.h"
#include "Exception.h"
#include <cstdlib>

namespace WoodLib
{

template < typename T >
class SharedPointer : public Pointer<T>
{
private:
    int* m_refCount;

    void assign(const SharedPointer<T>& obj)
    {
        m_refCount = obj.m_refCount;      // 指向同一内存空间这样任意一个改变其他的都会改变

        this->m_pointer = obj.m_pointer;

        if( m_refCount != NULL )          // 若是指向的是个NULL，计数值就不动
        {
            (*m_refCount)++;
        }
    }

public:
    SharedPointer(T* p = NULL) : m_refCount(NULL)
    {
        if( p != NULL )
        {
            // 申请4个字节的空间存放这个计数指针
            m_refCount = static_cast<int*>(malloc(sizeof(int)));

            if( m_refCount != NULL )
            {
                *m_refCount = 1;      // 计数值初始化为1
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "No memory to crea SharedPointer Object ...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj)
    {
        assign(obj);
    }

    ~SharedPointer()
    {
        clear();
    }

    SharedPointer& operator =(const SharedPointer<T>& obj)
    {
        if( this != &obj )
        {
            clear();     // this可能指向另一堆对象内存，要先置空
            assign(obj);
        }

        return *this;
    }

    void clear()
    {
        int* refCount = m_refCount;
        T* toDel = this->m_pointer;

        // 将当前指针置为空
        this->m_pointer = NULL;
        m_refCount = NULL;

        if( refCount != NULL )       // 如果还有指针指着这个堆内存
        {
            if( 0 == --(*refCount) ) // 计数减1,计数减为0时
            {
                delete toDel;        // 释放当前智能指针指向的堆内存
                free(refCount);      // 释放计数指针
            }
        }
    }
};

// 由于SharedPointer支持多个对象同时指向一片堆空间。因此必须支持比较操作！
// 这里用全局函数实现重载
template < typename T >
bool operator ==(const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (l.get() == r.get());
}

template < typename T >
bool operator !=(const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (l.get() != r.get());
}

}

#endif
