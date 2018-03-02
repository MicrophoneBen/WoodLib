// Exception 异常类族使用示例
#include <iostream>
#include "Exception.h"

using namespace std;
using namespace WoodLib;

double Divide(double l, double r)
{
    const double c_delta = 0.000000000000000000000001;
    double ret = 0;

    if( !((-c_delta < r) && (r < c_delta)) )
    {
        ret = l/r;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Divide by zero"); // 产生除0异常,将直接跳出这个函数
    }

    return ret;
}

// 匹配规则（自上而下，严格匹配、不进行类型转换）
void Demo1()
{
    try
    {
        THROW_EXCEPTION(ArithmeticException, "Demo1");
    }
    catch(const ArithmeticException& obj)
    {
        cout << "catch(const ArithmeticException& obj)" << endl;
        cout << obj.getMessage() << endl;
        cout << obj.getLocation() << endl;
    }
    catch(const Exception& obj)
    {
        cout << "catch(const Exception& obj)" << endl;
        cout << obj.getMessage() << endl;
        cout << obj.getLocation() << endl;
    }
}

void Demo2()
{
    THROW_EXCEPTION(NotEnoughMemoryException, "Demo2");
}

int main()
{
    cout << "main() begin ..." << endl;

    try
    {
        double d = Divide(1, 0);
        cout << "d = " << d << endl;
    }
    catch(const InvalidParameterException& obj)
    {
        cout << "catch(const InvalidParameterException& obj)" << endl;
        cout << obj.getMessage() << endl;
        cout << obj.getLocation() << endl;
    }

    cout << endl;

    Demo1();

    cout << endl;

    try
    {
        Demo2();
    }
    catch(const NullPointerException& obj)
    {
        cout << "catch(const NullPointerException& obj)" << endl;
        cout << obj.getMessage() << endl;
        cout << obj.getLocation() << endl;
    }
    catch(const NotEnoughMemoryException& obj)
    {
        cout << "catch(const NotEnoughMemoryException& obj)" << endl;
        cout << obj.getMessage() << endl;
        cout << obj.getLocation() << endl;
    }
    catch(const Exception& obj)
    {
        cout << "catch(const Exception& obj)" << endl;
        cout << obj.getMessage() << endl;
        cout << obj.getLocation() << endl;
    }

    cout << "main() end ..." << endl;

    return 0;
}
/* 运行结果
main() begin ...
catch(const InvalidParameterException& obj)
Divide by zero
..\main.cpp:19

catch(const ArithmeticException& obj)
Demo1
..\main.cpp:30

catch(const NotEnoughMemoryException& obj)
Demo2
..\main.cpp:48
main() end ...
*/
