// SmartPointer.h 智能指针类
#ifndef _SMARTPOINTER_H_
#define _SMARTPOINTER_H_

#include <iostream>     // 测试用后面去掉，打造库要尽量避免使用标准库

using namespace std;

namespace WoodLib
{

template < typename T >
class SmartPointer
{
private:
    T* m_pointer;

public:
    SmartPointer(T* pointer = NULL) : m_pointer(pointer)
    {
        cout << "SmartPointer()" << endl;
    }

    SmartPointer(const SmartPointer<T>& obj)
    {
        m_pointer = obj.m_pointer;
        // 所有权转移，使得同一时刻只能由一个指针指向堆空间
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    ~SmartPointer()
    {
        cout << "~SmartPointer()" << endl;
        delete m_pointer;  // 保证生命周期结束时自动释放
    }

    SmartPointer& operator = (const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            delete m_pointer;  // 赋值旧对象已经被创建存在故先释放它
            m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
        }

        return *this;
    }

    T* operator -> ()
    {
        return m_pointer;
    }

    T& operator * ()
    {
        return *m_pointer;
    }

    T* get()
    {
        return m_pointer;
    }

    bool isNull()
    {
        return (m_pointer == NULL);  // 不是用this判断
    }
};

}

#endif
