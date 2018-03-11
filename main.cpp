// main.cpp  String 字符串类使用示例
#include <iostream>
#include "WoodString.h"

using namespace std;
using namespace WoodLib;

int main()
{
    String s = "abc1234";

    cout << "s.length() = " << s.length() << endl;

    cout << "s.startWith(\"abc\") : " <<  s.startWith("abc") << endl;
    cout << "s.startWith(\"adc\") : " <<  s.startWith("adc") << endl;
    cout << "s.endOf(\"234\") : " <<  s.endOf("234") << endl;
    cout << "s.endOf(\"56\") : " <<  s.endOf("56") << endl;

    for(int i=0; i < s.length(); i++)
    {
        cout << s[i];
    }

    cout << endl;

    s.insert(0, "   Hello ");
    s.insert(s.length(), " Liyao     ");

    cout << "s.str() = [" << s.str() << "]" << endl;
    cout << "s.length() = " << s.length() << endl;

    s.trim();

    cout << "s.str() = [" << s.str() << "]" << endl;
    cout << "s.length() = " << s.length() << endl;

    return 0;
}
/* 运行结果
s.length() = 7
s.startWith("abc") : 1
s.startWith("adc") : 0
s.endOf("234") : 1
s.endOf("56") : 0
abc1234
s.str() = [   Hello abc1234 Liyao     ]
s.length() = 27
s.str() = [Hello abc1234 Liyao]
s.length() = 19
*/
