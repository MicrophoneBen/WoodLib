// WoodString.h 字符串类
// 这个文件若取名为String.h与STL库冲突，编译一堆error，但类名可以是String
#ifndef _WOODSTRING_H_
#define _WOODSTRING_H_

#include "Object.h"

namespace WoodLib
{

class String : public Object
{
private:
    char* m_str;    // 指向字符数组
    int m_length;   // 字符串长度

    void init(const char* str);

public:
    String();
    String(const char* s);
    String(const String& s);   // 拷贝构造
    String(char c);

    int length() const;
    const char* str() const;

    /* 比较操作符重载函数 */
    bool operator==(const String& s) const;
    bool operator==(const char* s) const;
    bool operator!=(const String& s) const;
    bool operator!=(const char* s) const;
    bool operator>(const String& s) const;
    bool operator>(const char* s) const;
    bool operator<(const String& s) const;
    bool operator<(const char* s) const;
    bool operator>=(const String& s) const;
    bool operator>=(const char* s) const;
    bool operator<=(const String& s) const;
    bool operator<=(const char* s) const;

    /* 加法操作符重载函数 */
    // 因为const对象返回值只是个数值，而非const对象的返回值是个引用，故这个必须区分开来
    String operator+(const String& s)const;
    String operator+(const char* s) const;
    String& operator+=(const String& s);
    String& operator+=(const char* s);

    /* 赋值操作符重载函数 */
    String& operator=(const String& s);
    String& operator=(const char* s);
    String& operator=(char c);

    ~String();
};

}

#endif
