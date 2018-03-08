// LinuxList.h linux 内核链表头文件
// 这节课只列出实验用到的 和 一些移植所做的改动的部分
// 没有列出 linux 内核链表头文件的所有内容,因为太长不利于阅读
// 在后面移植进WoodLib时我再将其全部列出来的
#ifndef _LINUXLIST_H_
#define _LINUXLIST_H_

// #include <linux/types.h>
// #include <linux/stddef.h>
// #include <linux/poison.h>
// #include <linux/prefetch.h>
// #include <linux/stddef.h> 中的依赖
#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#ifndef container_of
#define container_of(MEMBER_POINTER, TYPE, MEMBER) \
    ((TYPE *)((char *)MEMBER_POINTER - offsetof(TYPE, MEMBER)))
#endif

// #include <linux/poison.h> 中的依赖
#define LIST_POISON1 (NULL)
#define LIST_POISON2 (NULL)

// #include <linux/types.h> 中的依赖
struct list_head
{
    struct list_head* next;
    struct list_head* prev;
};

struct hlist_node
{
    struct hlist_node *next, **pprev;
};

struct hlist_head
{
    struct hlist_node *first;
};

// 清除平台相关代码
// #include <linux/prefetch.h> 中的依赖
#define prefetch(x) ((void)x)
/*
* Simple doubly linked list implementation.
* *
Some of the internal functions ("__xxx") are useful when
* manipulating whole lists rather than single entries, as
* sometimes we already know the next/prev entries and we can
* generate better code by using them directly rather than
* using the generic single-entry routines.
*/
#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

// 初始化头结点 ==>双向循环链表
static void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}
/*
* Insert a new entry between two known consecutive entries.
* *
This is only for internal list manipulation where we know
* the prev/next entries already!*/
#ifndef CONFIG_DEBUG_LIST
static void __list_add(struct list_head *node,
                       struct list_head *prev,
                       struct list_head *next)
{
    next->prev = node;
    node->next = next;
    node->prev = prev;
    prev->next = node;
}
#else
extern void __list_add(struct list_head *node,
                       struct list_head *prev,
                       struct list_head *next);
#endif
/**
* list_add - add a new entry
* @node: new entry to be added
* @head: list head to add it after
* *
Insert a new entry after the specified head.
* This is good for implementing stacks.
*/
// 头插结点
static void list_add(struct list_head *node, struct list_head *head)
{
    __list_add(node, head, head->next);
}
/**
* list_add_tail - add a new entry
* @node: new entry to be added
* @head: list head to add it before
* *
Insert a new entry before the specified head.
* This is useful for implementing queues.
*/
// 尾插结点
static void list_add_tail(struct list_head *node, struct list_head *head)
{
    __list_add(node, head->prev, head);
}

/*
* Delete a list entry by making the prev/next entries
* point to each other.
* *
This is only for internal list manipulation where we know
* the prev/next entries already!
*/
static void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}

#ifndef CONFIG_DEBUG_LIST
// 删除结点
static void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = LIST_POISON1;
    entry->prev = LIST_POISON2;
}
#else
// 这个这课是没有调用的 但还是保留在这里作为对比阅读
extern void __list_del_entry(struct list_head *entry);
extern void list_del(struct list_head *entry);
#endif

/**
* list_entry - get the struct for this entry
* @ptr: the &struct list_head pointer.
* @type: the type of the struct this is embedded in.
* @member: the name of the list_struct within the struct.
*/
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)
/**
* list_for_each - iterate over a list
* @pos: the &struct list_head to use as a loop cursor.
* @head: the head for your list.
*/
// 正向遍历
#define list_for_each(pos, head) \
    for (pos = (head)->next; prefetch(pos->next), pos != (head); \
    pos = pos->next)
/**
* __list_for_each - iterate over a list
* @pos: the &struct list_head to use as a loop cursor.
* @head: the head for your list.
* *
This variant differs from list_for_each() in that it's the
* simplest possible list iteration code, no prefetching is done.
* Use this for code that knows the list to be very short (empty
* or 1 entry) most of the time.
*/
// 这个这课是没有调用的 但还是保留在这里作为对比阅读
#define __list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)
/**
* list_for_each_prev - iterate over a list backwards
* @pos: the &struct list_head to use as a loop cursor.
* @head: the head for your list.
*/
// 逆向遍历
#define list_for_each_prev(pos, head) \
    for (pos = (head)->prev; prefetch(pos->prev), pos != (head); \
    pos = pos->prev)

#endif
