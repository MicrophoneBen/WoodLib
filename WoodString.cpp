#include "WoodString.h"
#include "Exception.h"
#include <cstring>
#include <cstdlib>

namespace WoodLib
{

void String::init(const char* str)
{
    // strdup 内部调用 malloc申请了一段堆内存再将str所指向的内容放入这段对内存，故最后析构时要用 free() 释放
    // strdup()内部没有对参数为NULL的检测，自己手动检测，若为NULL就转换为""字符串，这是个常量字符串有const属性
    // 而m_str是非const的，所以得使用const_case<>去掉常量字符串的const属性！
    m_str = str ? strdup(str) : const_cast<char*>("");   // 字符串复制

    if( m_str != NULL )   // strdup()内部malloc可能申请堆内存失败返回NULL指针
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NotEnoughMemoryException, "Not enoght memory to creat string object ...");
    }
}

String::String()
{
    init("");
}

String::String(const char* s)
{
    init(s);
}

String::String(const String& s)
{
    init(s.m_str);
}

String::String(char c)
{
    char s[] = {c, '\0'};  // 变成字符数组 手动加入了字符串结束符

    init(s);
}

int String::length() const
{
    return m_length;
}

// 获取字符串
const char* String::str() const
{
    return m_str;
}

/* 比较操作符重载函数 */
bool String::operator==(const String& s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}

bool String::operator==(const char* s) const
{
    return (strcmp(m_str, s) == 0);
}

bool String::operator!=(const String& s) const
{
    return !(*this == s);
}

bool String::operator!=(const char* s) const
{
    return !(*this == s);
}

bool String::operator>(const String& s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}

bool String::operator>(const char* s) const
{
    // 传参是char* 时：注意对s进行一个NULL检测
    // 上面传参是String时不用进行检测，因为String对象在构造时已经做出了检测，所以其成员 m_str 不可能为NULL
    return (strcmp(m_str, s ? s : "") > 0);
}

bool String::operator<(const String& s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}

bool String::operator<(const char* s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}

bool String::operator>=(const String& s) const
{
    return !(*this < s);   // 不小于不就是大于或等于了
}

bool String::operator>=(const char* s) const
{
    return !(*this < s);
}

bool String::operator<=(const String& s) const
{
    return !(*this > s);
}

bool String::operator<=(const char* s) const
{
    return !(*this > s);
}

/* 加法操作符重载函数 */
// 因为const对象返回值只是个数值，而非const对象的返回值是个引用，故这个必须区分开来
String String::operator+(const String& s)const
{
    // 调用传参为 const char* s 版本的+号操作符重载函数
    return (*this + s.m_str);
}

String String::operator+(const char* s) const
{
    String ret;

    int len = m_length + strlen(s ? s : "");

    char* str = static_cast<char*>(malloc(len + 1));

    if( str != NULL )
    {
        strcpy(str, m_str);
        strcat(str, s ? s : "");  // 包含在末尾加了结尾标志符 '\0'

        free(ret.m_str);

        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to add string value ...");
    }

    return ret;
}

String& String::operator+=(const String& s)
{
    // 通过定义实现，如 a += b; ==>a = a + b;
    // + 和 = 调用的是 const String* 传参版本的
    return *this = *this + s;
}

String& String::operator+=(const char* s)
{
    // 通过定义实现，如 a += b; ==>a = a + b;
    // + 和 = 调用的是 const char* 传参版本的
    return *this = *this + s;
}

/* 赋值操作符重载函数 */
String& String::operator=(const String& s)
{
    return (*this = s.m_str);
}

String& String::operator=(const char* s)
{
    if( m_str != s )
    {
        char* str = strdup(s ? s : "");

        if( str != NULL )
        {
            char* tmp = m_str;        // 保证异常安全
            m_str = str;
            m_length = strlen(str);

            free(tmp);
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to assign new string ...");
        }
    }

    return *this;
}

String& String::operator=(char c)
{
    char s[] = {c, '\0'};

    return (*this = s);
}

String::~String()
{
    free(m_str);
}

}
