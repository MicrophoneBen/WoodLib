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
    bool equal(const char* l, const char* r, unsigned int len) const;

public:
    String();
    String(const char* s);
    String(const String& s);   // 拷贝构造
    String(char c);

    int length() const;
    const char* str() const;   // 获取字符串

    char& operator[](int index);
    char operator[](int index) const;
    bool startWith(const char* s) const;    // 判断是否以s开头
    bool startWith(const String& s) const;
    bool endOf(const char* s) const;        // 判断是否以s结尾
    bool endOf(const String& s) const;
    String& insert(int index, const char* s);   // const对象不能改变肯定也不能够插入
    String& insert(int index, const String& s);
    String& trim();    // 去掉两端空格字符

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
