// C++异常处理示例
#include <iostream>

using namespace std;

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
        throw 0;  // 产生除0异常,将直接跳出这个函数
    }

    return ret;
}

// 匹配规则（自上而下，严格匹配、不进行类型转换）
void Demo1()
{
    try
    {
        throw 'a';
    }
    catch(int i)
    {
        cout << "catch(int i)" << endl;
    }
    catch(double d)
    {
        cout << "catch(double d)" << endl;
    }
    catch(char c)
    {
        cout << "catch(char c)" << endl;
    }
}

void Demo2()
{
    throw "Demo2";
}

int main()
{
    cout << "main() begin ..." << endl;

    try
    {
        double d = Divide(1, 0);
        cout << "d = " << d << endl;
    }
    catch(...)
    {
        cout << "Divide by zero ..." << endl;
    }

    cout << endl;

    Demo1();

    cout << endl;

    try
    {
        Demo2();
    }
    catch(char* c)
    {
        cout << "catch(cahr* c)" << endl;
    }
    catch(const char* c)
    {
        cout << "catch(const char* c)" << endl;
    }
    catch(...)
    {
        cout << "catch(...)" << endl;
    }

    cout << "main() end ..." << endl;

    return 0;
}
/* 运行结果
main() begin ...
Divide by zero ...

catch(char c)

catch(const char* c)
main() end ...
*/
