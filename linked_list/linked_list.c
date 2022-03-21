
#include "linked_list.h"
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

//新建当向链表
LinkedList *list_new() {
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
    LinkedListItem *item = new_item(value);
    if (l->size == 0) {
        l->head = l->tail = item;
    } else {
        item->next = l->head;
        l->head = item;
    }

    l->size ++;
}

// pop_front() —— 删除首部元素并返回其值
int pop_front(LinkedList *l) {
    check_empty_del(l);

    LinkedListItem *item = l->head;
    l->head = item->next;
    int returnValue = item->value;
    free_item(item);
    l->size--;

    if (l->size == 0) {
        l->tail = NULL;
    }

    return returnValue;
}

// push_back(value) —— 添加元素到链表的尾部
void push_back(LinkedList *l, int value) {
    LinkedListItem *item = new_item(value);

    if (l->size == 0) {
        l->head = l->tail = item;
    } else {
        l->tail->next = item;
        l->tail = item;
    }
    l->size ++;
}

// pop_back() —— 删除尾部元素并返回其值
int pop_back(LinkedList *l) {
    check_empty_del(l);

    int returnValue = l->tail->value;

    if (l->size == 1) {
        free_item(l->head);
        l->head = l->tail = NULL;
    } else {

        LinkedListItem *current = l->head;
        while (current != NULL)
        {
            if (current->next == l->tail) {
                current->next = NULL;
                free_item(l->tail);
                l->tail = current;
                break;
            }
            current = current->next;
        }
    }

    l->size--;

    return returnValue;
}

// front() —— 返回首部元素的值
int front(LinkedList *l) {
    check_index_range(l, 0);

    return l->head->value;
}

// back() —— 返回尾部元素的值
int back(LinkedList *l) {
    check_index_range(l, l->size - 1);

    return l->tail->value;
}

// insert(index, value) —— 插入值到指定的索引，并把当前索引的元素指向到新的元素
void insert(LinkedList *l, int index, int value) {

    if (l->size == 0) {
        push_front(l, value);
        return;
    } 

    check_index_range(l, index);

    int i = 0;
    LinkedListItem *current = l->head;
    while (current != NULL)
    {
       if (i == index) {
           current->value = value;
           break;
       }

       current = current->next;
       i ++;
    }
}

// erase(index) —— 删除指定索引的节点
void erase(LinkedList *l, int index) {
    check_index_range(l, index);

    if (index == 0) {
        pop_front(l);
        return;
    }

    if (index == (l->size - 1)) {
        pop_back(l);
        return;
    }

    //排除首尾节点
    int i = 1;
    LinkedListItem *pre = l->head;
    LinkedListItem *current = l->head->next;
    while (current != NULL)
    {
        if (i == index) {
            pre->next = current->next;
            free_item(current);
            break;
        }

        i ++;
        pre = current;
        current = pre->next;
    }

    l->size --;
    
}

// value_n_from_end(n) —— 返回倒数第 n 个节点的值
int vale_n_from_end(LinkedList *l, int n) {
    return value_at(l, l->size - n);
}

// reverse() —— 逆序链表
void reverse(LinkedList *l) {
    LinkedListItem *current = l->head;
    LinkedListItem *pre = NULL;

    l->head = l->tail;
    l->tail = current;

    while (current != NULL)
    {
        LinkedListItem *next = current->next;
        current->next = pre;

        if (current == l->head) {
            break;
        }
        pre = current;
        current = next;
    }
    
}

// remove_value(value) —— 删除链表中指定值的第一个元素
void remove_value(LinkedList *l, int value) {
    LinkedListItem *current = l->head;

    int i = 0;
    while (current != NULL)
    {
        if (current->value == value) {
            erase(l, i);
            break;
        }
        i ++;
        current = current->next;
    }
    
}

void print_debug(LinkedList *l) {

    LinkedListItem *current = l->head;
    printf("list:");
    while (current != NULL)
    {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("\n");
    
}

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

void check_empty_del(LinkedList *l) {
    if (empty(l)) {
        printf("已是空链表， 不能删除\n");
        exit(1);
    }
}

void check_pointer_address(void *p) {
    if (p == NULL) {
        printf("分配内存出错：%s \n", strerror(errno));
        exit(1);
    }
}

void check_index_range(LinkedList *l, int index) {
    if (index < 0 || index >= l->size) {
        printf("超出范围\n");
        exit(1);
    }
}