// Object类 顶层父类的实现文件
#include "Object.h"
#include <cstdlib>

using namespace std;

namespace WoodLib
{

void* Object::operator new(unsigned int size) throw()
{
    // 编译器会调用这里分配堆内存空间后自动调用相应类的构造函数
    return malloc(size);
}

void Object::operator delete(void* p)
{
    free(p);
}

void* Object::operator new[](unsigned int size) throw()
{
    // 当用new Test[5]时，只须传入数组元素的个数
    // 编译器会向operator new[](...)函数的参数
    // 传入5*sizeof(Test) + sizeof(unsigned int)
    // 其中的sizeof(unsigned int)为额外空间，用于保存元素的个数。
    return malloc(size);
}

void Object::operator delete[](void* p)
{
    free(p);
}

bool Object::operator ==(const Object& obj)
{
    return (this == &obj);
}

bool Object::operator !=(const Object& obj)
{
    return (this != &obj);
}

Object::~Object()
{
}

}

