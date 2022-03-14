#include "array.h"
#include <assert.h>

void test_all() {
    test_new();
    test_push();
    test_at();
    test_grow_szie();
    test_insert();
    test_prepend();
    test_pop();
    test_delete();
    test_reduce_capacity();
    test_find();
    test_remove();
}

void test_new() {
    SARR* arr = SARR_new();
    assert(SARR_size(arr) == 0);
    assert(SARR_capacity(arr) == MIN_CAPACIRY);
    assert(SARR_is_empty(arr));
    SARR_free(arr);
}

void test_push() {
    SARR* arr = SARR_new();
    SARR_push(arr, "hello");
    assert(SARR_size(arr) == 1);
    assert(SARR_capacity(arr) == MIN_CAPACIRY);
    assert(SARR_is_empty(arr) == false);
    SARR_free(arr);
}

void test_at() {
    SARR* arr = SARR_new();
    SARR_push(arr, "hello");
    SARR_push(arr, "hello2");
    assert(SARR_size(arr) == 2);
    assert(SARR_at(arr, 1) == "hello2");
    SARR_free(arr);
}

void test_grow_szie() {
    SARR* arr = SARR_new();

    for (int i = 0; i < 15; i++)
    {
        SARR_push(arr, "hello");
    }
    
    assert(SARR_size(arr) == 15);
    assert(SARR_capacity(arr) == 16);

    SARR_push(arr, "world");
    assert(SARR_size(arr) == 16);
    assert(SARR_capacity(arr) == 32);
    
    SARR_free(arr);
}

void test_insert() {
    SARR* arr = SARR_new();
    
    SARR_push(arr, "1");
    SARR_push(arr, "2");

    SARR_insert(arr, 1, "11");
    SARR_insert(arr, 3, "1212");
    assert(SARR_size(arr) == 4);
    assert(SARR_at(arr, 0) == "1");
    assert(SARR_at(arr, 1) == "11");
    assert(SARR_at(arr, 2) == "2");
    assert(SARR_at(arr, 3) == "1212");

    SARR_free(arr);
}

void test_prepend() {
    SARR* arr = SARR_new();
    
    SARR_push(arr, "1");
    SARR_push(arr, "2");
    SARR_prepend(arr, "-1");
    SARR_prepend(arr, "-2");

    assert(SARR_size(arr) == 4);
    assert(SARR_at(arr, 0) == "-2");
    assert(SARR_at(arr, 1) == "-1");
    assert(SARR_at(arr, 2) == "1");
    assert(SARR_at(arr, 3) == "2");

}

void test_pop() {
    SARR* arr = SARR_new();
    
    SARR_push(arr, "1");
    SARR_push(arr, "2");
    assert(SARR_pop(arr) == "2");
    assert(SARR_pop(arr) == "1");
    assert(SARR_size(arr) == 0);
}


void test_delete() {
    SARR* arr = SARR_new();
    
    SARR_push(arr, "1");
    SARR_push(arr, "2");
    SARR_delete(arr, 0);
    assert(SARR_at(arr, 0) == "2");

    SARR_delete(arr, 0);
    assert(SARR_size(arr) == 0);
}

void test_reduce_capacity() {
    SARR* arr = SARR_new();

    for (int i = 0; i < 32; i++)
    {
        SARR_push(arr, "1");
    }
    assert(SARR_size(arr) == 32);
    assert(SARR_capacity(arr) == 64);

    // 64/4 = 16 && 16 >= 16
    for (int i = 0; i < 30; i++)
    {
        SARR_pop(arr);
    }
    assert(SARR_size(arr) == 2);
    assert(SARR_capacity(arr) == MIN_CAPACIRY);
    
}

void test_find() {

    SARR* arr = SARR_new();
    SARR_push(arr, "1");
    SARR_push(arr, "2");

    assert(SARR_find(arr, "1") == 0);
    assert(SARR_find(arr, "2") == 1);
    assert(SARR_find(arr, "3") == -1);
}

void test_remove() {
    SARR* arr = SARR_new();
    SARR_push(arr, "1");
    SARR_push(arr, "2");

    assert(SARR_remove(arr, "1") == 0);
    assert(SARR_at(arr, 0) == "2");
    assert(SARR_remove(arr, "2") == 0);
    assert(SARR_is_empty(arr));
}