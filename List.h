// List.h 线性表抽象类
#ifndef _LIST_H_
#define _LIST_H_

#include "Object.h"

namespace WoodLib
{

template < typename T >
class List : public Object
{
public:
    virtual bool insert(int index, const T& element) = 0;  // 插入
    virtual bool remove(int index) = 0;                    // 删除
    virtual bool set(int index, const T& element) = 0;     // 设置
    virtual bool get(int index, T& element) const = 0;     // 获取
    virtual int length() const = 0;                        // 长度
    virtual void clear() = 0;                              // 清空
};

}

#endif

