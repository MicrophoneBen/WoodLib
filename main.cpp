// 栈的应用实例：成对符号匹配问题
#include <iostream>
#include "LinkStack.h"

using namespace std;
using namespace WoodLib;

// 是否为左符号
bool isLeft(char c)
{
    return (c == '(') || (c == '{') || (c == '[') || (c == '<');
}

// 是否为右符号
bool isRight(char c)
{
    return (c == ')') || (c == '}') || (c == ']') || (c == '>');
}

// 是否为引号(单引号 双引号) 因为引号左右是一样的所以拿出来单独处理
bool isQuot(char c)
{
    return (c == '\'') || (c == '\"');
}

// 匹配检测
bool isMatch(char l, char r)
{
    return ((l=='(') && (r==')')) ||
           ((l=='{') && (r=='}')) ||
           ((l=='[') && (r==']')) ||
           ((l=='<') && (r=='>')) ||
           ((l=='\'') && (l==r))  ||
           ((l=='\"') && (l==r));
}

// 核心代码：扫描字符，字符串都是以 '\0' 作为标志符结尾
bool scanner(const char* code)
{
    bool ret = true;

    LinkStack<char> stack;  // 链式栈
    int i = 0;

    code = (code == NULL) ? "" : code;  // 对传参进行NULL检测

    // 1、开始按顺序读取字符，遇到结束符'\0' 或匹配失败时结束
    while( ret && code[i] != '\0' )
    {
        if( isLeft(code[i]) )
        {
            stack.push(code[i]);    // 左字符入栈
        }
        else if( isRight(code[i]) ) // 右字符
        {
            // 2.右字符是否与栈顶匹配
            if( stack.size() > 0 && isMatch(stack.top(),code[i]) )
            {
                // 注意 栈空时出现右字符也是匹配失败的
                stack.pop();        // 匹配，则出栈
            }
            else
            {
                ret = false;        // 匹配失败
            }
        }
        else if( isQuot(code[i]) )  // 引号的处理
        {
            // 栈空时扫描到引号，说明此引号是左操作符，则当前字符入栈。
            // 栈顶不是引号，也表示当前字符是左引号，则当前字符入栈。
            if( stack.size() == 0 && !isMatch(stack.top(), code[i]) )
            {
                stack.push(code[i]);
            }
            else if( isMatch(stack.top(), code[i]) )
            {
                // 右引号（栈顶己经是引号了，表示当前字符(code[i])为右引号）
                // 则此时弹出栈顶的引号
                stack.pop();
            }
        }

        i++;
    }

    return ret && (stack.size() == 0);  // 不要忘记匹配成功栈也要完全弹出即为空
}

int main()
{
    const char* s1 = "<a{b<c>(\'x\'\"\")d}e>";
    const char* s2 = "#include <stdio.h>   \
                      int main()          \
                      {                   \
                         int a[5][5];     \
                         int (*p)[4];     \
                         p = a[0];        \
                         printf(\"%d\n\", &p[3][3] - &a[3][3]); \
                         return 0;        \
                      }";

    const char* s3 = "int a[5][5]][6]";

    cout << "expression s1 : " << scanner(s1) << endl;
    cout << "expression s2 : " << scanner(s2) << endl;
    cout << "expression s3 : " << scanner(s3) << endl;

    return 0;
}
/* 运行结果
expression s1 : 1
expression s2 : 1
expression s3 : 0
*/
