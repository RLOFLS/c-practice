#include<stdbool.h>

#ifndef _LINKED_LIST_
#define _LINKED_LIST_

typedef struct LinkedListItem
{
    int value;
    struct LinkedListItem *next;
} LinkedListItem;

typedef struct LinkedList
{
    int size;
    LinkedListItem *head;
    LinkedListItem *tail;

} LinkedList;

// size() —— 返回链表中数据元素的个数
extern int size(LinkedList *);
// empty() —— 若链表为空则返回一个布尔值 true
extern bool empty(LinkedList *);
// value_at(index) —— 返回第 n 个元素的值（从0开始计算）
extern int value_at(LinkedList *, int index);
// push_front(value) —— 添加元素到链表的首部
extern void push_front(LinkedList *, int value);
// pop_front() —— 删除首部元素并返回其值
extern int pop_front(LinkedList *);
// push_back(value) —— 添加元素到链表的尾部
extern void push_back(LinkedList *, int value);
// pop_back() —— 删除尾部元素并返回其值
extern int pop_back(LinkedList *);
// front() —— 返回首部元素的值
extern int front(LinkedList *);
// back() —— 返回尾部元素的值
extern int back(LinkedList *);
// insert(index, value) —— 插入值到指定的索引，并把当前索引的元素指向到新的元素
extern void insert(LinkedList *, int index, int value);
// erase(index) —— 删除指定索引的节点
extern void erase(LinkedList *, int index);
// value_n_from_end(n) —— 返回倒数第 n 个节点的值
extern int vale_n_from_end(LinkedList *, int n);
// reverse() —— 逆序链表
extern void reverse(LinkedList *);
// remove_value(value) —— 删除链表中指定值的第一个元素
extern void remove_value(LinkedList *, int value);

void check_pointer_address(void *p);

#endif