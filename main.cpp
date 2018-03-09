// main.cpp 链式队列（组合linux内核双向链表类）使用示例
#include <iostream>
#include "LinKQueue.h"

using namespace std;
using namespace WoodLib;

class Test : public Object
{
public:
    Test()
    {
        cout << "Test::Test()" << endl;
    }

    ~Test()
    {
        cout << "Test::~Test()" << endl;
    }
};

int main()
{
    LinkQueue<int> queue;

    cout << "queue is Empty ==> " << queue.isEmpty() << endl;

    cout << "queue.enQueue() : ";
    for(int i=0; i < 5; i++)
    {
        cout << i << " ";
        queue.enQueue(i);
    }

    cout << endl << "queue is Empty ==> " << queue.isEmpty() << endl;

    cout << "queue.deQueue() : ";
    while( queue.length() > 0 )
    {
        cout << queue.front() << " ";
        queue.deQueue();
    }

    cout << endl << "queue is Empty ==> " << queue.isEmpty() << endl;

    // 测试2
    cout << endl;

    LinkQueue<Test> queue2;   // 链式队列就没有构造函数的调用了

    return 0;
}
/* 运行结果
queue is Empty ==> 1
queue.enQueue() : 0 1 2 3 4
queue is Empty ==> 0
queue.deQueue() : 0 1 2 3 4
queue is Empty ==> 1

*/
