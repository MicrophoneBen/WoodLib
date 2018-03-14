#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "Object.h"
#include "Exception.h"
#include "Sort.h"

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

    // 这里调用了会被 StaticArray 类和 DynamicArray 类继承过去
    // 选择排序（O(n*n),不稳定 ） 默认从小到大排序
    void selectSort(bool min2max = true)
    {
        Sort::selectSort(m_array, length(), min2max);
    }

    // 插入排序（O(n*n),稳定 ） 默认从小到大排序
    void insertSort(bool min2max = true)
    {
        Sort::insertSort(m_array, length(), min2max);
    }

    // 冒泡排序（O(n*n),稳定 ） 默认从小到大排序
    void bubbleSort(bool min2max = true)
    {
        Sort::bubbleSort(m_array, length(), min2max);
    }

    // 希尔排序（O(n的3/2次方), 不稳定 ） 默认从小到大排序
    void shellSort(bool min2max = true)
    {
        Sort::shellSort(m_array, length(), min2max);
    }

    // 归并排序（O(nlogn), 稳定 ） 默认从小到大排序
    void mergeSort(bool min2max = true)
    {
        Sort::mergeSort(m_array, length(), min2max);
    }

    // 快速排序（O(nlogn), 不稳定 ） 默认从小到大排序
    void quickSort(bool min2max = true)
    {
        Sort::quickSort(m_array, length(), min2max);
    }

};

}

#endif
