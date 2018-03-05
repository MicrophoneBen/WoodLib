#ifndef _STATICLINK_H_
#define _STATICLINK_H_

#include "LinkList.h"

namespace WoodLib
{

// N 静态链表最大容量
template < typename T, int N >
class StaticLink : public LinkList<T>
{
private:
    typedef typename LinkList<T>::Node Node;

    // SNode：为重载 new 操作符
    struct SNode : public Node
    {
        // 重载new第一个参数必须是 int 型表示大小的，否则编译就错误
        // 再后面就是自定义参数了,以本程序为例：locale 就是传进来的ret内存空间了
        void* operator new(unsigned int size, void* locale)
        {
            (void)size;    // 屏蔽没有使用size的编译警告
            return locale; // 直接返回指定的内存空间，申请内存不是目的
                           // 目的是借助编译器遇到new会自动调用相应构造函数的特性
        }
    };

    // unsigned char m_space[sizeof(Node) * N]; ==>error
    // unsigned char m_space[sizeof(LinkList<T>::Node) * N];
    // ==>error 因为编译器不知道 这个 Node 是个类型 还是个静态成员变量
    // unsigned char m_space[sizeof(typename LinkList<T>::Node) * N];
    // ==>这样编译正确了,但这样写太复杂了,所以有了上面的
    // typedef typename LinkList<T>::Node Node;
    // 预留出 N 个 SNode 的内存空间大小 new 时从这里面拿内存空间

    unsigned char m_space[sizeof(SNode) * N];
    bool m_used[N];    // 用于标识空间利用情况

    Node* creatNode()
    {
        SNode* ret = NULL;

        for(int i=0; i < N; i++)
        {
            if( !m_used[i] )
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;  // 分配内存

                // 因为结点中有数据域，而数据域的类型时泛型T，T可能是类类型
                // 这个时候就还需要在这个分配的内存上调用T的构造函数对这个数据域
                // 进行初始化操作，那么就得想方设法利用new来自动调用构造函数

                // 在指定的空间 ret 上（注意，这里不一定是堆！） new 一个对象，
                // 利用 new 的特性来调用 SNode 的构造函数,从而可以调用到 结点上泛型 T 的构造函数
                ret = new(ret) SNode();  // 在指定的ret内存上调用构造函数来初始化

                m_used[i] = true;

                break;
            }
        }

        return ret;
    }

    void destroyNode(Node* pn)
    {
        SNode* space = reinterpret_cast<SNode*>(m_space);
        SNode* psn = dynamic_cast<SNode*>(pn); // 注意强制转换关键字

        for(int i=0; i < N; i++)
        {
            if(pn == (space + i))
            {
                psn->~SNode();     // 手动调用析构函数清理空间
                m_used[i] = false;
            }
        }
    }

public:
    StaticLink()
    {
        for(int i=0; i < N; i++)
        {
            m_used[i] = false;
        }
    }

    int capacity()
    {
        return N;
    }
};

}



#endif
