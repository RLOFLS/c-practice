
#include "linked_list.h"
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

//新建当向链表
LinkedList *new() {
    LinkedList *l = malloc(sizeof(LinkedList));
    check_pointer_address(l);

    l->size = 0;
    return l;
}

int size(LinkedList *l) {
    return l->size;
}

// empty() —— 若链表为空则返回一个布尔值 true
bool empty(LinkedList *l) {
    return l->size == 0;
}

// value_at(index) —— 返回第 n 个元素的值（从0开始计算）
int value_at(LinkedList *l, int index) {
    check_index_range(l, index);

    LinkedListItem *item = l->head;
    int idx = 0;
    while (item != NULL)
    {
        if (idx == index) 
            return item->value;
        idx++;
        item = item->next;
    }
}

// push_front(value) —— 添加元素到链表的首部
void push_front(LinkedList *l, int value) {
    LinkedListItem *item = new_item(int);

    item->next = l->head;
    l->head = item;
    l->size ++;
}

// pop_front() —— 删除首部元素并返回其值
int pop_front(LinkedList *l) {
    LinkedListItem *item = l->head;
    l->head = item->next;
    int returnValue = item->value;
    free_item(item);
    l->size--;
    return returnValue;
}

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

LinkedListItem *new_item(int value) {
    LinkedListItem *item = malloc(sizeof(LinkedListItem));
    item->value = value;

    check_pointer_address(item);

    return item;
}

void free_item(LinkedListItem *item) {
    item->next = NULL;
    free(item);
    item = NULL;
}

void free_list(LinkedList *l) {
    if (l->head != NULL) {
        LinkedListItem *item = l->head;
        while (item != NULL)
        {
            LinkedListItem *temp = item;
            item = item->next;
            free_item(temp);
        }
    }
    l->head = NULL;
    l->tail = NULL;
    free(l);
    l = NULL;
}

void check_pointer_address(void *p) {
    if (p == NULL) {
        printf("分配内存出错：%s \n", strerror(errno));
        exit(1);
    }
}

void check_index_range(LinkedList *l, int index) {
    if (index < 0 && index >= l->size) {
        printf("超出范围")
        exit(1);
    }
}

void check_size(LinkedList *l) {
    if (l->size == 0) {
        l->head = l->tail = NULL;
    }
}