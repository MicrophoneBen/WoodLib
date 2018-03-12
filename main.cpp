// main.cpp  KMP 算法编码
#include <iostream>
#include "Exception.h"
#include <cstdlib>
#include <cstring>

using namespace std;
using namespace WoodLib;

// 在目标串dest中查找子串substr的常规算法，返回值为子串在目标串中的下标
// O(n) = (len_dest-len_substr) * len_substr ==> len_dest * len_substr
int findSubstr(const char* dest, const char* substr)
{
    int ret = -1;

    int len_dest = strlen(dest);
    int len_substr = strlen(substr);
    int len = len_dest - len_substr;

    for(int i=0; (ret<0) && (i<=len); i++)
    {
        bool equal = true;

        for(int j=0; equal && (j<len_substr); j++)
        {
            equal = equal && (dest[i + j] == substr[j]);
        }

        ret = (equal ? i : -1);
    }

    return ret;
}

// KMP算法： O(n) = len_dest + len_substr
// 返回值：部分匹配表，在堆上申请的内存空间
int* makePMT(const char* substr)
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

int KMP(const char* dest, const char* substr)
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

    return ret;
}

int main()
{
    cout << findSubstr("0123456789ABCDABCDABD", "ABCDABD") << endl << endl;   // 常规算法

    int* PMT = makePMT("ABCDABD");       // PMT表

    cout << "PMT = [ ";
    for(int i=0; i<strlen("ABCDABD"); i++)
    {
        cout << PMT[i] << " ";
    }
    cout << "]" << endl;

    cout << KMP("0123456789ABCDABCDABD", "ABCDABD") << endl;   // KMP算法

    return 0;
}
/* 运行结果
14

PMT = [ 0 0 0 0 1 2 0 ]
14
*/
