// StaticList.h 静态顺序存储线性表类
#ifndef _STATICLIST_H_
#define _STATICLIST_H_

#include "SequenceList.h"

namespace WoodLib
{

template < typename T, int N >
class StaticList : public SequenceList<T>
{
private:
    T m_space[N];

public:
    StaticList()
    {
        // 模板类的继承关系中：子类访问父类成员必须得加上 this->
        // 原因：模板基类可能被特化，可能不存在对应的成员。所以编译器
        // 一般默认会在模板派生类中隐藏模板基类的细节。
        // 加上 this-> 延迟这个成员到实例化后再查找，第一次编译模板时不查找
        this->m_array = m_space;
        this->m_length = 0;
    }

    int capacity() const
    {
        return N;
    }
};

}

#endif
