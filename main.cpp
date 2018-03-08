// Linux内核链表的使用示例
#include <stdio.h>
#include <malloc.h>
#include "LinuxList.h"

void Demo1()
{
    // 自定义结点类型（含数据域）
    struct Node
    {
        list_head head;        // 指针域放前面
        int value;             // 数据域
    };

    Node node = {0};

    // 因为 head 位于 Node 结构体中的第一个元素,所以可以这样强制类型转换,这步强
    // 制类型转换的目的是使得这个链表后面便可以直接使用内核链表其他一些函数了
    list_head* list = (list_head*)&node;

    // 初始化链表，形成循环链表 若没有上面强制类型转就不能这样方便初始化了
    INIT_LIST_HEAD(list);

    printf("Insert begin ...\n");

    // 插入 5 个元素
    for(int i=0; i<5; i++)
    {
        Node* n = (Node*)malloc(sizeof(Node));
        n->value = i;

        list_add_tail((list_head*)n, list);
    }

    // list_for_each 遍历中需要用到这个指针
    list_head* slider = NULL;

    // 遍历链表
    list_for_each(slider, list)
    {
        printf("%d ", ((Node*)slider)->value);
    }

    printf("\nInsert end ...\n\n");

    // 删除值为 3 的元素
    printf("Delete begin ...\n");

    list_for_each(slider, list)
    {
        if(((Node*)slider)->value == 3)
        {
            list_del(slider);
            free(slider);

            break;
        }
    }

    list_for_each(slider, list)
    {
        printf("%d ", ((Node*)slider)->value);
    }

    printf("\nDelete end ...\n\n");
}

// 结点类型中指针域放最后
void Demo2()
{
    // 自定义结点类型（含数据域）
    struct Node
    {
        int value;
        list_head head; // 指针域放后面
    };

    Node node = {0};

    // struct list_head head 放到结点后面,就得注意了
    list_head* list = (list_head*)&(node.head);

    // 初始化链表，形成循环链表
    INIT_LIST_HEAD(list);

    printf("Insert begin ...\n");

    // 插入 5 个元素
    for(int i=0; i<5; i++)
    {
        struct Node* n = (Node*)malloc(sizeof(Node));
        n->value = i;

        list_add_tail( &(n->head), list );
    }

    list_head* slider = NULL;

    // 遍历链表（注意，需要用 list_entry 宏来获取节点的地址）
    list_for_each(slider, list)
    {
        printf("%d ", list_entry(slider, Node, head)->value);
    }

    printf("\nInsert end ...\n\n");

    // 删除值为 3 的元素
    printf("Delete begin ...\n");

    list_for_each(slider, list)
    {
        if(list_entry(slider, Node, head)->value == 3)
        {
            list_del(slider);
            free(slider);

            break;
        }
    }

    list_for_each(slider, list)
    {
        printf("%d ", list_entry(slider, Node, head)->value);
    }

    printf("\nDelete end ...\n");
}

int main()
{
    Demo1();

    printf("------------------------\n");

    Demo2();

    return 0;
}
/* 运行结果
Insert begin ...
0 1 2 3 4
Insert end ...

Delete begin ...
0 1 2 4
Delete end ...

------------------------
Insert begin ...
0 1 2 3 4
Insert end ...

Delete begin ...
0 1 2 4
Delete end ...
*/
