// Exception.cpp 异常类的实现文件
#include "Exception.h"
#include <cstring>
#include <cstdlib>

namespace WoodLib
{

void Exception::init(const char* message, const char* file, int line)
{
    m_message = strdup(message);     // strdup()内部会调用malloc申请堆内存
                                     // 不要直接赋值，直接赋值是不安全的

    if(file != NULL)
    {
        char l_s[16] = {0};

        itoa(line, l_s, 10); // 将整数line转为字符串,其中的10表示转换为十进制格式

        // m_location的格式为：file:line\0;
        m_location = static_cast<char*>(malloc(sizeof(file) + sizeof(l_s) + 2));
        m_location = strcpy(m_location, file);
        m_location = strcat(m_location, ":");
        m_location = strcat(m_location, l_s);
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

