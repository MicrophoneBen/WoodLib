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

    // 两路合并算法中的合并过程（归并算法）
    // 将两个有序序列array[start...middle]和array[middle+1...end] 合并
    template < typename T >
    static void mergeSort(T array[], T helper[], int start, int middle, int end, bool min2max)
    {
        int left_index = start;
        int right_index = middle + 1;
        int helper_index = 0;

        // 按顺序将两个有序序列中较 小/大 的依次放入helper中
        while( (left_index <= middle) && (right_index <= end) )
        {
#if 0
            if( min2max ? (array[left_index] < array[right_index]) : (array[left_index] > array[right_index]) )
            {
                // 取较 小/大 者放入helper中
                helper[helper_index++] = array[left_index++];
            }
            else
            {
                helper[helper_index++] = array[right_index++];
            }
#else
            // 上面if else 可以优化为下面这句；
            helper[helper_index++] = ( min2max ? (array[left_index] < array[right_index]) : \
                                                 (array[left_index] > array[right_index]) ) ? \
                                                 (array[left_index++]) : (array[right_index++]);
#endif
        }

        // 将左子序列中剩余部分直接拷贝到helper中
        while( left_index <= middle )
        {
            helper[helper_index++] = array[left_index++];
        }

        // 将右子序列中剩余部分直接拷贝到helper中
        while( right_index <= end )
        {
            helper[helper_index++] = array[right_index++];
        }

        // std::cout << "[" << start << "]" << std::endl;   // 用来追踪下面错误的

        // 将数据拷贝回array中
        for(int i=0; i<helper_index; i++)
        {
            // array[i] = helper[i];         // 错误，结果不是预期的
            array[start + i] = helper[i];
        }
    }

    // 两路合并算法中的分解算法
    template <typename T>
    static void mergeSort(T array[], T helper[], int start, int end, bool min2max)
    {
        if( start < end )
        {
            int middle = (start + end) /2;

            // 递归结束条件，只要start < end说明还可以再分解
            // 分解为两路
            mergeSort(array, helper, start, middle, min2max);   // 函数返回后左子序列为有序序列
            mergeSort(array, helper, middle + 1, end, min2max); // 函数返回后右子序列为有序序列

            // 合并
            mergeSort(array, helper, start, middle, end, min2max);
        }
    }

    // 快速排序找到 基准 在序列中应该放入的位置，用返回值返回
    template < typename T >
    static int partition(T array[], int start, int end, bool min2max)
    {
        int ret = start;       // 用传进来的array[] 的最前面这个元素作为基准，下面就是找到这个基准应该处于序列中的位置

        while( start < end )
        {
            // start 指针的移动,从左向右找出大于或者等于 基准 的元素
            // 并且相等的元素只能在这个左边找出，不能在右边找
            while( (start < end) && (min2max ? (array[start] < array[ret]) : (array[start] > array[ret])) )
            {
                start++;
            }

            // end 指针的移动,从右向左找出小于 基准 的元素
            while( (start < end) && (min2max ? (array[end] >= array[ret]) : (array[end] <= array[ret])) )
            {
                end--;
            }

            // 交换上面两个跳出while循环时的 临界点，这样使得一边都是小于的基准的，另一边都是大于基准的
            swap(array[start], array[end]);
        }

        // 将基准元素放入 low 和 high 相遇的地方
        swap(array[ret], array[start]);

        return (ret = start);  // 返回当前基准的位置
    }

    // 快速排序
    template < typename T >
    static void quickSort(T array[], int start, int end, bool min2max = true)
    {
        if( start < end )
        {
            // 递归结束条件
            int pivot_index = partition(array, start, end, min2max);  //依基准分成两个区

            quickSort(array, start, pivot_index - 1, min2max);        // 左区快排（递归）
            quickSort(array, pivot_index +1, end, min2max);           // 右区快排（递归）
        }
    }


    // 堆排序的功能函数: 返回左孩子结点
    static int left(int i)
    {
        return (2 * i + 1);  // 返回的是二叉树中结点的顺序编号，不是结点中存储的值
    }

    // 堆排序的功能函数：返回右孩子结点
    static int right(int i)
    { 
        return (2 * i + 2);  // 返回的是二叉树中结点的顺序编号，不是结点中存储的值
    }

    // 堆排序的功能函数，堆调整：以某一结点（i值）为根的子树做堆调整（保证最大堆性质）
	// 结点编号从根结点0开始，从左至右依次编号
    template <typename T>
    static void HeapAdjust(T array[], int i, int heapSize, bool min2max)
    {
        int lf = left(i);
        int rt = right(i);
		int largest;
		
        T tmp;

        // 比较父结点和左孩子（并将较大者的索引记录下来）
		// lf < heapSize 阻止数组越界的情况发生
        if(lf < heapSize && (min2max ? (array[lf] > array[i]) : (array[lf] < array[i])))
        {
            largest = lf;
        }
        else
        {
            largest = i;
        }

        // 比较父结点和右孩子（并将较大者的索引记录下来）
        if(rt < heapSize && (min2max ? (array[rt] > array[largest]) :(array[rt] < array[largest]) ))
        {
            largest = rt;
        }

        // 找到父结点与左右孩子三个结点中的最大/小值
        if(largest != i)   // 发生了交换就进入if
        {
            // 将最大/小值与父结点交换
            tmp = array[i];
            array[i] = array[largest];
            array[largest] = tmp;
            // 交换后导致左右孩子的数值发生变化，对有变化结点（如左孩子）的子树进一步做堆调整。
            HeapAdjust(array, largest, heapSize, min2max);
        }
    }

    // 堆排序的功能函数：创建最大堆
    template <typename T>
    static void BuildHeap(T array[], int len, bool min2max)
    {
        // 根据给定的数据创建最大堆（不断进行堆调整）
        for(int i=(len-2)/2; i>=0; i--)
        {
            // 注意：从后向前创建堆。
            // 叶子结点无左右孩子，不必调整。所以
            // i=(len-2)/2 开始，跳过所有叶子结点
            HeapAdjust(array, i, len, min2max);     // 对以结点 i 的子树进行堆调整。
        }
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

    // 归并排序
    template < typename T >
    static void mergeSort(T array[], int len, bool min2max = true)
    {
        // 申请一片与待排数据大小一样的空间作为辅助空间使用
        T* helper = new T[len];

        if( helper != NULL )
        {
            mergeSort(array, helper, 0, len-1, min2max);
        }

        delete[] helper;
    }

    // 快速排序
    template < typename T >
    static void quickSort(T array[], int len, bool min2max = true)
    {
        quickSort(array, 0, len - 1, min2max);
    }

    // 堆排序：外面调用的接口，默认升序排序
    template <typename T>
    static void Heap(T array[], int len, bool min2max = true)
    {
        BuildHeap(array, len, min2max);   // 创建最大/最小堆

        T tmp;

        for(int i=len-1; i>=0; i--)       // 将根结点与最末尾的结点进行数值交换，在二叉树末尾逐渐形成有序区
        {
            tmp = array[0];
            array[0] = array[i];
            array[i] = tmp;
            HeapAdjust(array, 0, i, min2max);
        }
    }
};

}

#endif
