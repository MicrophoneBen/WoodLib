// main.cpp  数学思想来理解递归
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

// 递归求和
unsigned int sum(unsigned int n)
{
    unsigned int ret = 0;

    if( n > 1 )
    {
        ret = n + sum(n - 1);
    }

    if( 1 == n )   // 递归出口
    {
        ret = 1;
    }

    return ret;
}

// 斐波拉契数列： 1,1,2,3,5,8,13,21,34,...
// 注意小标设置为从1开始
unsigned int fac(unsigned int index)
{
    unsigned int ret = 0;

    if( index >= 3 )
    {
        ret = fac(index - 1) + fac(index - 2);
    }

    if( (index == 2) || (index == 1) )   // 递归出口
    {
        ret = 1;
    }

    return ret;
}

// 用递归求字符串长度
unsigned int mySrylen(const char* str)
{
    unsigned int ret = 0;

    // 注意是*str
    if(*str != '\0')
    {
        // 1 + 跳过第0个 计算str下标1开始的字符串长度
        ret = 1 + mySrylen(str + 1);
    }
    else
    {
        ret = 0;
    }

    return ret;
}

// 用一行代码改写上面递归求字符串长度的函数
// 这个是想说明,在阅读他人代码时当看到他人很精妙的写法时不要惊讶
// 这可能就是别人反复优化最后的代码而已,就如这里,实质原理与上面
// 完全一样,但看上去却比上面优雅太多了
// 同时这里也是想说明,基础理论很重要,对于下面这个如果不知道用数学
// 思想来看待递归,那下面这个改写了一句程序绝对是看不懂的,上面普
// 通写法还是可能看懂的,说明了基础理论的重要性
unsigned int mySrylen_beautiful(const char* str)
{
    return str ? (*str ? 1 + mySrylen_beautiful(str + 1) : 0) : 0;
}

int main()
{
    cout << sum(100) << endl;

    cout << "[ ";
    for(int i=1; i<=10; i++)    // 注意小标设置为从1开始
    {
        cout << fac(i) << " ";
    }
    cout << "]" << endl;

    cout << mySrylen("Liyao") << endl;

    cout << mySrylen_beautiful("Liyao") << endl;

    return 0;
}
/* 运行结果
5050
[ 1 1 2 3 5 8 13 21 34 55 ]
5
5
*/
