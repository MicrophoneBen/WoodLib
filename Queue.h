// Queue.h 队列抽象父类
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Object.h"

namespace WoodLib
{

template < typename T >
class Queue : public Object
{
public:
    virtual void enQueue(const T& element) = 0;
    virtual void deQueue() = 0;
    virtual T front() const = 0;
    virtual void clear() = 0;
    virtual int length() const = 0;
    virtual bool isEmpty() const = 0;
};

}

#endif
