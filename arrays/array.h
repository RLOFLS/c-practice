//  size() —— 数组元素的个数
//  capacity() —— 可容纳元素的个数
//  is_empty()
//  at(index) —— 返回对应索引的元素，且若索引越界则愤然报错
//  push(item)
//  insert(index, item) —— 在指定索引中插入元素，并把后面的元素依次后移
//  prepend(item) —— 可以使用上面的 insert 函数，传参 index 为 0
//  pop() —— 删除在数组末端的元素，并返回其值
//  delete(index) —— 删除指定索引的元素，并把后面的元素依次前移
//  remove(item) —— 删除指定值的元素，并返回其索引
//  find(item) —— 寻找指定值的元素并返回其中第一个出现的元素其索引，若未找到则返回 -1
//  resize(new_capacity) // 私有函数
#ifndef _STR_ARRAY

#include<stdbool.h>

#define _STR_ARRAY 1
#define MIN_CAPACIRY 16

typedef struct SARR
{
    int size;
    int capacity;
    char** data;
} SARR;

struct SARR* SARR_new();
int SARR_size(SARR*);
int SARR_capacity(SARR*);
bool SARR_is_empty(SARR*);
char* SARR_at(SARR*, int index);
void SARR_push(SARR*, char* item);
void SARR_insert(SARR*, int index, char* item);
void SARR_prepend(SARR*, char* item);
char* SARR_pop(SARR*);
void SARR_delete(SARR*, int index);
int SARR_remove(SARR*, char* item);
int SARR_find(SARR*, char* item);
void SARR_free(SARR*);

void reSize(SARR* arr, int reSize);
void checkPtr(void* ptr);

//====test===
void test_all();
void test_new();
void test_push();
void test_at();
void test_grow_szie();
void test_insert();
void test_prepend();
void test_pop();
void test_delete();
void test_reduce_capacity();
void test_find();
void test_remove();

#endif