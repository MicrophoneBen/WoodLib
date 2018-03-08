#include <iostream>
#include <stdio.h>

using namespace std;

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE*)0)->MEMBER)
#endif

// const typeof(...):编译期类型检查， const 指针兼容 const 和非 const 指针类型
// typeof 根据变量名获取到这个变量的类型，这样第二部预处理阶段替换后就会在编译器有个类型检查
// 又因为tryeof只在编译期有效运行期无效，所以也不会出现断错误；
// 强制转为char*类型是为了做 指针运算
#ifndef container_of
#define container_of(ptr, type, member) ({                 \
    const typeof(((type*)0)->member)* __mptr = (ptr);      \
    (type*)((char*)__mptr - offsetof(type, member));})
#endif

struct ST
{
    int i;  // offset 0
    int j;  // offset 4
    char c; // offset 8
};

// ({})是何方神圣
void test()
{
    int a = 0;
    int b = 0;
    int c = (a=1, b=2, a+b); // 括号表达式

    // ({})表达式，其中的{}表示一个作用域， {}外再加上()表示取
    // 最后一个语句的值功能上类似于逗号表达式，这是 GNU C 扩展语法
    int d = ({int a=1; int b=2; a+b;});

    printf("c = %d\n", c);
    printf("d = %d\n", d);
}

// typeof 关键字：GNU C 的扩展关键字
void type_of()
{
    int i = 100;
    typeof(i) j = i;
    const typeof(j)* p = &j;

    printf("sizeof(j)= %d\n", sizeof(j));
    printf("j = %d\n", j);
    printf("*p = %d\n", *p);
}

void func(ST* pst)
{
    int* pi = &(pst->i);       // (unsigned int)pst + 0;
    int* pj = &(pst->j);       // (unsigned int)pst + 4;
    char* pc = &(pst->c);      // (unsigned int)pst + 8;

    printf("pst = %p\n", pst);
    printf("pi = %p\n", pi);
    printf("pj = %p\n", pj);
    printf("pc = %p\n", pc);
}

int main()
{
    ST s = {0, 0, 0};

    func(&s);
    func(NULL);  // 借用 0 地址计算成员变量的偏移地址，相当于 pst=0
                 // 使用到 0 地址但为什么没有发生段错误了，因为这里
                 // 并没有访问 0 地址的内容；
                 // 编译器知道各个成员相对于结构体的地址偏移量是多少
                 // 这里传个 0 地址就是利用了这点，0地址传递进func函数
                 // 再在func函数中打印出各个结构体成员变量的地址
                 // 而因为结构体地址是0,所以各个成员地址数值上就与
                 // 这个成员的偏移量是一样的数值了
                 // offsetof宏就是利用了这个原理

    cout << "offset i: " << offsetof(ST, i) << endl;   // 0
    cout << "offset j: " << offsetof(ST, j) << endl;   // 4
    cout << "offset c: " << offsetof(ST, c) << endl;   // 8

    cout << "---------------------------" << endl;

    test();      // ({}) 用法测试
    type_of();   // typeof 用法测试

    ST s1 = {0, 0, 0};

    char* pc = &s1.c;

    ST* pst = container_of(pc, ST, c);

    cout << "&s = " << &s1 << endl;
    cout << "pst = " << pst << endl;

    return 0;
}
/* 运行结果
pst = 0061fe88
pi = 0061fe88
pj = 0061fe8c
pc = 0061fe90
pst = 00000000
pi = 00000000
pj = 00000004
pc = 00000008
offset i: 0
offset j: 4
offset c: 8
---------------------------
c = 3
d = 3
sizeof(j)= 4
j = 100
*p = 100
&s = 0x61fe7c
pst = 0x61fe7c
*/
