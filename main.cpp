// main.cpp 顺序队列使用示例
#include <iostream>
#include "StaticQueue.h"

using namespace std;
using namespace WoodLib;

class Test
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
    StaticQueue<int, 5> queue;

    cout << "queue is Empty ==> " << queue.isEmpty() << endl;

    cout << "queue.enQueue() : ";
    for(int i=0; i < queue.capacity(); i++)
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

    // 测试2： 顺序队列的缺陷
    cout << endl;

    StaticQueue<Test, 5> queue2;   // 与顺序栈一样的缺陷，后面用链式队列解决

    return 0;
}
/* 运行结果
queue is Empty ==> 1
queue.enQueue() : 0 1 2 3 4
queue is Empty ==> 0
queue.deQueue() : 0 1 2 3 4
queue is Empty ==> 1

Test::Test()
Test::Test()
Test::Test()
Test::Test()
Test::Test()
Test::~Test()
Test::~Test()
Test::~Test()
Test::~Test()
Test::~Test()
*/
