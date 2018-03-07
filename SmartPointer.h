// SmartPointer.h 智能指针类
#ifndef _SMARTPOINTER_H_
#define _SMARTPOINTER_H_

#include "Pointer.h"

namespace WoodLib
{

template < typename T >
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* pointer = NULL) : Pointer<T>(pointer)
    {

    }

    SmartPointer(const SmartPointer<T>& obj) : Pointer<T>(obj.m_pointer)
    {
        // 所有权转移，使得同一时刻只能由一个指针指向堆空间
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;  // 保证生命周期结束时自动释放
    }

    SmartPointer& operator =(const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            T* pointer = this->m_pointer;  // 保证异常安全

            this->m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

            delete pointer;  // 赋值时,旧对象已经被创建存在故释放它
        }

        return *this;
    }
};

}

#endif
