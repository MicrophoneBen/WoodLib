// Pointer.h 指针抽象类
#ifndef _POINTER_H_
#define _POINTER_H_

#include "Object.h"

namespace  WoodLib
{

template < typename T >
class Pointer : public Object
{
protected:
    T* m_pointer;

public:
    Pointer(T* pointer = NULL) : m_pointer(pointer)
    {
    }

    const T*  operator ->() const   // cosnt版本，注意这个返回值也设为const的
    {
        return m_pointer;
    }

    T* operator ->()
    {
        return m_pointer;
    }

    const T& operator *() const
    {
        return *m_pointer;
    }

    T& operator *()
    {
        return *m_pointer;
    }

    T* get() const
    {
        return m_pointer;
    }

    bool isNull() const
    {
        return (m_pointer == NULL);  // 不是用this判断
    }

    // 父类Object的析构函数本身是纯虚函数！
    // 所以这里不实现析构函数,这个类就是个抽象类
};

}

#endif
