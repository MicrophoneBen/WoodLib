// Object.h 顶层父类
#ifndef _OBJECT_H_
#define _OBJECT_H_

namespace WoodLib
{

class Object
{
public:
    // 以下四个重载函数用于统一不同编译器new失败时的结果不同的问题
    // throw()表示不抛出异常，即如果申请内请失败时，统一返回NULL而不抛异常
    void* operator new(unsigned int size) throw();
    void operator delete(void* p);
    void* operator new[](unsigned int size) throw();
    void operator delete[](void* p);

    // 纯虚函数就会有虚函数表,保证继承此类的子类都能使用动态类型识别技术
    virtual ~Object() = 0;
};

}

#endif
