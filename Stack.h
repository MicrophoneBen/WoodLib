// Stack.h 栈的抽象父类
#ifndef _STACK_H_
#define _STACK_H_

#include "Object.h"

namespace WoodLib
{

template < typename T >
class Stack : public Object
{
public:
    virtual void push(const T& elem) = 0;  // 压栈
    virtual void pop() = 0;                // 出栈
    virtual T top() const = 0;             // 获取栈顶元素
    virtual void clear() = 0;              // 清空栈
    virtual int size() const = 0;          // 获取栈大小
};

}

#endif

