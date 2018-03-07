// Exception.cpp 异常类的实现文件
#include "Exception.h"
#include <cstring>
#include <cstdlib>    // 虽然是使用了标准库，但这个很容易就可以用c库替换就OK了
#include <cstdio>

namespace WoodLib
{

void Exception::init(const char* message, const char* file, int line)
{
    // strdup()内部会调用malloc申请堆内存,不要直接赋值，直接赋值是不安全的
    // 传递给strdup()函数的参数若是NULL将会引发段错误；
    // strdup()函数内部没有对传参是NULL的检查，所以这里自己检查NULL；
    m_message = message ? strdup(message) : NULL;

    if(file != NULL)
    {
        char l_s[16] = {0};

        //itoa(line, l_s, 10); // 将整数line转为字符串,其中的10表示转换为十进制格式
        //itoa()函数不具有可移植性，到linux的g++下面就编译报错了
        snprintf(l_s, sizeof(l_s), "%d", line);

        // 注意:申请内存失败时无须再抛NotEnoughMemoryException异常,从宏观上
        // 看，父类是无法抛出子类型的异常的。
        // 从逻辑上看也不能抛出这个异常，因为当父类构造时出现异常时，如果去抛出
        // 子类异常，则必然需要构造子类，但这又得先调用父类构造函数（会再一次产生
        // 异常，从而造成Exception构造函数的递归调用，从而造成死循环！）
        m_location = static_cast<char*>(malloc(sizeof(file) + sizeof(l_s) + 2));
        if(m_location != NULL)
        {
            // m_location的格式为：file:line\0;
            m_location = strcpy(m_location, file);
            m_location = strcat(m_location, ":");
            m_location = strcat(m_location, l_s);
        }
    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception(const char* message)
{
    init(message, NULL, 0);
}

Exception::Exception(const char* file, int line)
{
    init(NULL, file, line);
}

Exception::Exception(const char* message, const char* file, int line)
{
    init(message, file, line);
}

Exception::Exception(const Exception& obj)
{
    // 深拷贝
    m_message = strdup(obj.m_message);
    m_location = strdup(obj.m_location);
}

Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

Exception& Exception::operator =(const Exception& obj)
{
    if(this != &obj)
    {
        free(m_message);
        free(m_location);

        m_message = strdup(obj.m_message);
        m_location = strdup(obj.m_location);
    }

    return *this;
}

const char* Exception::getMessage() const
{
    return m_message;
}

const char* Exception::getLocation() const
{
    return m_location;
}

}

