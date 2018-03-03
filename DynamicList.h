// DynamicList类 动态顺序存储线性表类
#ifndef _DYNAMICLIST_H_
#define _DYNAMICLIST_H_

#include "SequenceList.h"
#include "Exception.h"

namespace WoodLib
{

template < typename T >
class DynamicList : public SequenceList<T>
{
private:
    int m_capacity;   // 顺序存储最大容量

public:
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];

        if( this->m_array != NULL )
        {
            this->m_length = 0;
            m_capacity = capacity;
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to create DynamicList Object ...");
        }
    }

    ~DynamicList()
    {
        delete[] this->m_array;   // 注意是个数组
    }

    int capacity() const
    {
        return m_capacity;
    }

    // 重新设置顺序存储最大容量的大小
    void resize(int capacity)
    {
        if( capacity != m_capacity )
        {
            T* array = new T[capacity];

            if( array != NULL )
            {
                int len = (this->m_length < capacity) ? this->m_length : capacity;

                // 复制原来的元素
                for(int i=0; i<len; i++)
                {
                    // T类在赋值时，可能产生异常！但是，即使这里发生了异常，由于
                    // 下列的m_array、m_length、m_capacity还没被改变。所以，仍然可
                    // 以保证DynamicList类是安全可用的，只是会造成array这个空间的
                    // 内存泄漏。这里作为T类的使用者，无须替T类的设计者考虑当赋值
                    // 中出现问题时是要抛异常通知使用者，还是采用其它处理办法。如果
                    // T类的设计者以抛异常处理，则这里可以通过try-catch捕获这个赋
                    // 值异常，然后在catch语句块中将array这个临时空间释放掉。
                    array[i] = (this->m_array)[i];
                }

                // 这里不能先delete[] this->m_array，再给m_array、m_length、
                // m_capacity赋值，因为delete可能会引起泛型T调用析构函数，而如果
                // 在析构函数中抛出异常，后面对成员变量的赋值都将无法进行，从而造成
                // 函数异常时的不安全。因此，正确的顺序应该是先对成员变量赋值，最后
                // 再释放m_array的旧空间。
                T* tmp = this->m_array;

                this->m_array = array;
                this->m_length = len;   // 注意不是capacity
                m_capacity = capacity;

                // 即使这里发生异常，但由于上述赋值已经完成
                // 从而保证了这个DynamicList是安全可用的
                delete tmp;
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to resize DynamicList Object ...");
            }
        }
    }

};

}

#endif
