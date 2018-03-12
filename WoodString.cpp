// String.cpp 
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

bool String::equal(const char* l, const char* r, unsigned int len) const
{
    bool ret = (len > 0);

    for(unsigned int i=0; i < len && ret; i++)  // 因为len是unsigned int类型的
    {
        // 逐个比对，一有不相等直接跳出 for 循环
        ret = ret && (l[i] == r[i]);
    }

    return ret;
}

// KMP算法： O(n) = len_dest + len_substr
// 返回值：部分匹配表，在堆上申请的内存空间
int* String::makePMT(const char* substr)
{
    int len = strlen(substr);

    // 不要忘记乘以 sizeof(int)
    int* PMT = static_cast<int*>(malloc(sizeof(int) * len));

    if( PMT != NULL )
    {
        int PMT_element = 0;  // 部分匹配表中的元素值
        PMT[0] = 0;           // 1、下标为 0 的元素 匹配值为 0

        // 2、从 2 个字符开始递推（从下标为 1 的字符开始递推）
        for(int i=1; i<len; i++)
        {
            // 4、当前缀与后缀向后拓展的字符不相等时, 匹配值到退至表中上一个元素值
            // 直至再次 判断相等，或者 匹配值 已经为 0 时；
            while( (PMT_element > 0) && (substr[PMT_element] != substr[i]) )
            {
                PMT_element = PMT[PMT_element - 1];
            }

            // 3、前缀与后缀向后拓展的字符相等时, 匹配值加1
            if( substr[PMT_element] == substr[i] )
            {
                PMT_element++;
            }

            PMT[i] = PMT_element;  // 将部分匹配值填入表中
        }
    }

    return PMT;
}

int String::KMP(const char* dest, const char* substr)
{
    int ret = -1;

    int len_dest = strlen(dest);
    int len_substr = strlen(substr);

    int* PMT = makePMT(substr);

    if( PMT != NULL )
    {
        for(int i=0,j=0; i<len_dest; i++)  // 目标串查找完毕跳出 for 循环
        {
            while( (j > 0) && (substr[j] != dest[i]) )
            {
                // 失配时，移动 j 到当前已经匹配了的子串的部分匹配值的位置
                // 。如果仍然失配， j 继续照上面规则忘前移动， 直到匹配或 j
                // 到达了子串开始的位置
                j = PMT[j-1];
            }

            if(substr[j] == dest[i])
            {
                j++;
            }

            if( j == len_substr )  // 目标串中有子串,已经匹配完找到了时
            {
                ret = i + 1 - len_substr;  // 同一维度计算
                break;
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "Nor exising normally PMT ...");
    }

    free(PMT);   // pmt 指向的是 make_pmt()申请的堆内存,所以得free
                 // free释放其他函数中申请的堆内存,这个设计不好！！！
                 // 能否改进一下？
                 // 不需要改进，类比strdup()也是这样！

    return ret;
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

int String::find(const char* substr) const
{
    return KMP(m_str, substr ? substr : "");
}

int String::find(const String& s) const
{
    return find(s.m_str);
}

String& String::remove(int index, int len)
{
    if( (0 <= index) && (index < m_length) && (len > 0))
    {
        int m = index + len;

        while( m < m_length )
        {
            m_str[index++] = m_str[m++];
        }

        m_str[index] = '\0';
        m_length = index;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter index is invalid ...");
    }

    return *this;
}

String& String::remove(const char* substr)
{
    return remove(find(substr), substr ? strlen(substr) : 0);
}

String& String::remove(const String& s)
{
    return remove(find(s), s.length());
}

String& String::replace(const char* dest, const char* substr)
{
    int index = find(dest);     // 1. 找到字符串 dest 在目标串中的位置

    if( index >= 0 )            // find() 没有找到时返回值 -1
    {
        remove(dest);           // 2. 先删除 dest
        insert(index, substr);  // 3. 在 index 位置插入 substr
    }

    return *this;
}

String& String::replace(const char* dest, const String& subst)
{
    return replace(dest, subst.m_str);
}

String& String::replace(const String& dest, const char* substr)
{
    return replace(dest.m_str, substr);
}

String& String::replace(const String& dest, const String& subst)
{
    return replace(dest.m_str, subst.m_str);
}

// 在目标串中的 index 下标出提取出长度为 len 的子串
String String::creatSubstr(int index, int len) const
{
    String ret;

    if( (0 <= index) && (index < m_length) && (len > 0))
    {
        if( (index + len) > m_length )
        {
            len = m_length - index;   // 归一化 将超过目标串的归一于最大到目标串末尾
        }

        char* str = static_cast<char*>(malloc(sizeof(char) * len + 1));

        if( str != NULL )
        {
            strncpy(str, m_str + index, len);
            str[len] = '\0';

            ret = str;   // 调用String的传参为 const char* 的 =函数,其中有对原来m_str堆内存的释放；
        }
        else
        {
            THROW_EXCEPTION(NotEnoughMemoryException, "Not enough memory to creat string ...");
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter is invalid ...");
    }

    return ret;
}

char& String::operator[](int index)
{
    return m_str[index];
}

char String::operator[](int index) const
{
    return m_str[index];
}

bool String::startWith(const char* s) const
{
    int len = strlen(s);
    bool ret = (s != NULL) && (len < m_length);  // 先对传参s进行检测

    if( ret )
    {
        ret = equal(m_str, s, len);
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter s is invalid ...");
    }

    return ret;
}

bool String::startWith(const String& s) const
{
    return (s.m_str);
}

bool String::endOf(const char* s) const
{
    int len = strlen(s);
    bool ret = (s != NULL) && (len < m_length);

    if( ret )
    {
        char* str = m_str + (m_length - len);  // 获取待比较位置的地址

        ret = equal(str, s, len);
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter s is invalid ...");
    }

    return ret;
}

bool String::endOf(const String& s) const
{
    return (s.m_str);
}

String& String::insert(int index, const char* s)
{
    if( (0 <= index) && (index <= m_length) )
    {
        int len = strlen(s);

        if( (s != NULL) && (len > 0) )
        {
            char* str = static_cast<char*>(malloc(m_length + len + 1));

            if( str != NULL )   // 堆空间申请成功
            {
                // 1. 拷贝 m_str 的前 index 个字符放入新空间开始的位置
                strncpy(str, m_str, index);
                // 2. 将 s 放入第 index+1 的位置
                strncpy(str + index, s, len);
                // 3. 将 m_str 剩余的部分紧接着放入新空间
                strncpy(str + index + len, m_str + index, m_length - index);

                str[m_length + len] = '\0';

                char* tmp = m_str;   // 保证异常安全
                m_str = str;
                m_length += len;
                free(tmp);
            }
            else
            {
                THROW_EXCEPTION(NotEnoughMemoryException, "No memory to insert string value ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter s is invalid ...");
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Paramter index is invalid ...");
    }

    return *this;
}

String& String::insert(int index, const String& s)
{
    return (insert(index, s.m_str));
}

String& String::trim()
{
    int front_count = 0;            // 字符串头最前面非空格字符的位置
    int rear_count = m_length - 1;  // 字符串尾最后一个非空格字符的位置

    while( ' ' == m_str[front_count] )
    {
        front_count++;
    }

    while( ' ' == m_str[rear_count] )
    {
        rear_count--;
    }

    if( 0 == front_count )            // 字符串前端无空格的情况
    {
        m_str[rear_count + 1] = '\0';
        m_length = rear_count + 1;
    }
    else                              // 字符串前端有空格
    {
        for(int i=0,j=front_count; j < rear_count+1; i++,j++)
        {
            m_str[i] = m_str[j];
        }

        m_length = rear_count - front_count + 1;
        m_str[rear_count - front_count + 1] = '\0';
    }

    return *this;
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

/* 减法操作符重载函数 */
String String::operator -(const String& s) const
{
    return String(*this).remove(s.m_str);
}

String String::operator -(const char* s) const
{
    // String(*this) 利用构造器产生一个和当前对象一样的
    // 临时字符串,这样也就不会改变目标串
    // 再调用 remove(s)删除子串 不就实现了减法了吗
    return String(*this).remove(s);
}

String& String::operator -=(const String& s)
{
    // 注意这个与上面不一样,这个是自身是要改变的
    return remove(s.m_str);
}

String& String::operator -=(const char* s)
{
    return remove(s);
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
