// Sort.h
#ifndef _SORT_H_
#define _SORT_H_

#include "Object.h"

namespace WoodLib
{

class Sort : public Object
{
private:
    // 私有化构造函数、赋值、拷贝构造等函数
    // 也就是这个类是不能被用来创建对象的
    Sort();
    Sort(const Sort&);
    Sort& operator=(const Sort&);

    template < typename T >
    static void swap(T& a, T& b)  // 给其他static成员函数调用，所以也用 static 修饰
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

public:
    // 选择排序（O(n*n),不稳定 ） 默认从小到大排序
    // array 要排序的数据 len 排序数据的长度 min2max 从小到大还是从大到小
    template < typename T >
    static void selectSort(T array[], int len, bool min2max = true)
    {
        for(int i=0; i<len-1; i++)
        {
            // 第 i 趟。有序区为[0,i-1],无序区为[i, len-1]
            // 1.找到无序区的首元素: array[i]
            int swap_index = i;   // 不会重复定义，每轮for循环结束时都会销毁掉

            // 2.从无序区中找到最小值/最大值的下标
            for(int j=i+1; j<len; j++)
            {
                // 根据 min2max 传参 选择顺序还是逆序
                if( min2max ? (array[swap_index] > array[j]) : (array[swap_index] < array[j]) )
                {
                    swap_index = j;
                }
            }

            // 3. 交换无序区中首元素和最小值的位置，将最小值放在无序区的首部
            // 加上一个判断 避免不用交换的也交换的情况以提高效率
            if( swap_index != i )
            {
               swap(array[i], array[swap_index]);
            }

        }
    }

    // 插入排序（O(n*n), 稳定 ）
    template < typename T >
    static void insertSort(T array[], int len, bool min2max = true)
    {
        // 1. 初始状态有序区为[0],无序区为[1..n-1]
        // 注意，从 1 开始，因为第[0]个就一个数据 就是个有序序列
        for(int i=1; i<len; i++)
        {
            // 有序区[0, i-1]，无序区[i, n-1]
            // 2. 取出无序区首元素，从有序区后面往前面依次与其比较
            T element = array[i];   // 无序区首元素
            int insert_index = i;   // 最终应该放置的位置

            for(int j=i-1; (j>=0) && (min2max ? (element < array[j]) : (element > array[j])); j--)
            {
                // 3. 边比较边移动元素， element 最终的位置记录在 insert_index 中
                array[j+1] = array[j];
                insert_index = j;
            }

            // 4. 将 element 放置下来 加判断与上一样目的 避免不必要的操作
            if( insert_index != i )
            {
                array[insert_index] = element;
            }
        }
    }

    // 冒泡排序 O(n*n)
    template < typename T >
    static void bubbleSort(T array[], int len, bool min2max = true)
    {
        // 如果无序区元素己排好序，则 exchange 为 false，
        // 否则当发生元素交换时，说明仍是无序的
        bool is_exchange = true;

        // 1. 初始状态：有序区[]，无序区[0..n-1]
        for(int i=0; (i<len) && (is_exchange); i++)
        {
            is_exchange = false;

            // 2. 从无序的区最后面开始，让小的元素往前面冒
            for(int j=len-1; j>i; j--)
            {
                if( min2max ? (array[j] < array[j - 1]) : (array[j] > array[j - 1]) )
                {
                    // 发生逆序，则交换
                    swap(array[j], array[j - 1]);
                    is_exchange = true;
                }
            }
        }
    }

    // 希尔排序
    template < typename T >
    static void shellSort(T array[], int len, bool min2max = true)
    {
        int d = len;

        do
        {
            d = d / 3 + 1;   // 增量序列，要保证每次 d 增量是递减的，且最终为 1
			                 // 为什么是设计 3 次，有前辈的实践经验得到的数据； 

            // 下面就是插入排序的逻辑了，注意 i、j 的增量！
            for(int i=d; i<len; i+=d)
            {
                T element = array[i];
                int insert_index = i;

                for(int j=i-d; (j>=0) && (min2max ? (element < array[j]) : (element > array[j])); j-=d)
                {
                    array[j+d] = array[j];
                    insert_index = j;
                }

                if( insert_index != i )
                {
                    array[insert_index] = element;
                }
            }

        }while( d > 1 );

    }

};


}

#endif
