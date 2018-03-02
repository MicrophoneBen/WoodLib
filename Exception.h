// Exception.h 异常类族
#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace WoodLib
{

// 利于移植性,不需要抛出异常时只需屏蔽掉后面就OK了
#define THROW_EXCEPTION(type, message)   (throw type(message, __FILE__, __LINE__))

// 异常抽象类
class Exception
{
protected:
    char* m_message;
    char* m_location;

    // 辅助初始化函数
    void init(const char* message, const char* file, int line);

public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line);

    // 注意：
    //（1）析构函数是较为特殊的函数，一旦定义了析构函数，不管这个函数是不是纯虚
    //    函数，就必须提供实现。因为对象在销毁时，最后都会调用父类的析构函数。
    //    如果父类不提供实现，当对象销毁过程中调用到父类析构函数时，就找不到析
    //    构函数，也就不知该如何析构下去。因此，尽管这里将析构函数声明为纯虚函
    //    数，但Exception类仍提供析构函数的实现。以便最后正确释放掉m_message
    //    和m_location所指的堆空间.
    //（2）此外，声明为纯虚函数，可以让该类只能作为接口使用，而且也强迫子类必须
    //    提供析构函数的实现。
    virtual ~Exception() = 0;     // 纯虚函数使得本类成为接口类

    // 因为这个类发生拷贝/赋值行为时是需要进行深拷贝的，所以需要重载这两个函数
    Exception(const Exception& obj);
    Exception& operator = (const Exception& obj);

    virtual const char* getMessage() const;
    virtual const char* getLocation() const;
};

// 计算异常类
class ArithmeticException : public Exception
{
public:
    ArithmeticException() : Exception(0) { }  // NULL需要包含头文件,可以用0替代
    ArithmeticException(const char* message) : Exception(message) { }
    ArithmeticException(const char* file, int line) : Exception(file, line) { }
    ArithmeticException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    ArithmeticException(const ArithmeticException& obj) : Exception(obj) { }

    ArithmeticException& operator = (const ArithmeticException& obj)
    {
        Exception::operator = (obj);  // 直接调用父类的赋值函数

        return *this;
    }
};

// 空指针异常类
class NullPointerException : public Exception
{
public:
    NullPointerException() : Exception(0) { }
    NullPointerException(const char* message) : Exception(message) { }
    NullPointerException(const char* file, int line) : Exception(file, line) { }
    NullPointerException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    NullPointerException(const NullPointerException& obj) : Exception(obj) { }

    NullPointerException& operator = (const NullPointerException& obj)
    {
        Exception::operator = (obj);

        return *this;
    }
};

// 越界异常类
class IndexOutOfBoundsException : public Exception
{
public:
    IndexOutOfBoundsException() : Exception(0) { }
    IndexOutOfBoundsException(const char* message) : Exception(message) { }
    IndexOutOfBoundsException(const char* file, int line) : Exception(file, line) { }
    IndexOutOfBoundsException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    IndexOutOfBoundsException(const IndexOutOfBoundsException& obj) : Exception(obj) { }

    IndexOutOfBoundsException& operator = (const IndexOutOfBoundsException& obj)
    {
        Exception::operator = (obj);

        return *this;
    }
};

// 内存不足异常类
class NotEnoughMemoryException : public Exception
{
public:
    NotEnoughMemoryException() : Exception(0) { }
    NotEnoughMemoryException(const char* message) : Exception(message) { }
    NotEnoughMemoryException(const char* file, int line) : Exception(file, line) { }
    NotEnoughMemoryException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    NotEnoughMemoryException(const NotEnoughMemoryException& obj) : Exception(obj) { }

    NotEnoughMemoryException& operator = (const NotEnoughMemoryException& obj)
    {
        Exception::operator = (obj);

        return *this;
    }
};

// 参数错误异常类
class InvalidParameterException : public Exception
{
public:
    InvalidParameterException() : Exception(0) { }
    InvalidParameterException(const char* message) : Exception(message) { }
    InvalidParameterException(const char* file, int line) : Exception(file, line) { }
    InvalidParameterException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    InvalidParameterException(const InvalidParameterException& obj) : Exception(obj) { }

    InvalidParameterException& operator = (const InvalidParameterException& obj)
    {
        Exception::operator = (obj);

        return *this;
    }
};

}

#endif
