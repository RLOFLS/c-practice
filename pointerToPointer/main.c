#include<stdio.h>
#include<stdlib.h>


struct List
{
    int item;
    struct List* next; 
};

void main() {

    struct List* l1 = malloc(sizeof(struct List));
    struct List* l2 = malloc(sizeof(struct List));
    struct List* l3 = malloc(sizeof(struct List));
    l1->item = 1;
    l2->item = 2;
    l3->item = 3;

    l1->next = l2;
    l2->next = l3;

    
    struct List** l;

    l = &l1;
    printList(l);
    //1---2---3---
    
    //删除2
    while (*l)
    {
        /* code */
        if ((*l)->item == 2) {
            *l = (*l)->next;
            break;
        }
        l = &(*l)->next;
    }

    l = &l1;
    printList(l);
    //1---3---

    //插入元素 将2插入回去
    while (*l)
    {
        if (l2->item <= (*l)->item) {
            l2->next = *l;
            *l = l2;
            break;
        }
        l = &(*l)->next;
    }
    l = &l1;
    printList(l);//1---2---3---

    
    free(l1);
    free(l2);
    free(l3);
    l1 = NULL;
    l2 = NULL;
    l3 = NULL;

}

void printList(struct List** l) {
    while (*l)
    {
        printf("%d---", (*l)->item);
        l = &(*l)->next;
        /* code */
    }
    printf("\n");
}