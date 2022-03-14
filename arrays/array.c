#include<stdlib.h>
#include<stdio.h>

SARR *SARR_new() {

    SARR* arr = malloc(sizeof(SARR));
    checkPtr(arr);

    arr->size = 0;
    arr->capacity = MIN_CAPACIRY;

    arr->data = malloc(sizeof(char*) * MIN_CAPACIRY);
    checkPtr(arr->data);

    return arr;
    
}

int SARR_size(SARR* arr) {
    return arr->size;
}

int SARR_capacity(SARR* arr) {
    return arr->capacity;
}

bool SARR_is_empty(SARR* arr) {
    return arr->size == 0;
}

char* SARR_at(SARR* arr, int index) {
    if (index >= arr->size) {
        printf("超出数组大小边界\n");
        exit(1);
    }
    char* atPtr = *(arr->data + index);
    return atPtr;
}

void SARR_push(SARR* arr, char* item) {
    reSize(arr, arr->size + 1);

    *(arr->data + arr->size) = item;

    arr->size++;
}

void SARR_insert(SARR* arr, int index, char* item) {
    if (index > arr->size || index < 0) {
        printf("超出数组大小连续边界： 0 ~ %d\n", arr->size);
        exit(1);
    }

    if (index == arr->size) {
        SARR_push(arr, item);
        return;
    }

    reSize(arr, arr->size + 1);

    for (int i = arr->size; i > index; i--)
    {
        char* temp = *(arr->data + (i - 1));
        *(arr->data + i) = temp;
    }
    *(arr->data + index) = item;  
    arr->size++;
}

char* SARR_pop(SARR* arr) {
    if (arr->size == 0) {
        return NULL;
    }

    char* res;

    res = *(arr->data + (arr->size - 1));

    *(arr->data + (arr->size - 1)) = NULL;

    reSize(arr, arr->size - 1);

    arr->size--;

    return res;

}


void SARR_delete(SARR* arr, int index) {
    if (index > arr->size - 1 || index < 0) {
        printf("超出数组大小连续边界： 0 ~ %d\n", arr->size - 1);
        exit(1);
    } 

    *(arr->data + index) = NULL;

    int next = index + 1;
    while (next < arr->size)
    {
        *(arr->data + (next - 1)) = *(arr->data + next);
        *(arr->data + next) = NULL;
        next++;
    }

    reSize(arr, arr->size - 1);
    arr->size--;
    
}

int SARR_find(SARR* arr, char* item) {

    if (arr->size == 0) {
        return -1;
    }
    int max = arr->size - 1;

    for (int i = max; i >= 0; i--)
    {
        if (*(arr->data + i) == item) {
            return i;
        }
    }
    return -1;
}

int SARR_remove(SARR* arr, char* item) {
    int index = SARR_find(arr, item);
    if (index == -1) {
        return -1;
    }

    SARR_delete(arr, index);

    return index;

}


void SARR_prepend(SARR* arr, char* item) {
    return SARR_insert(arr, 0, item);
}

void SARR_free(SARR* arr) {
    free(arr->data);
    free(arr);
    arr = NULL;
}

void reSize(SARR* arr, int reSize) {
    //增大
    if (reSize >= arr->capacity) {
        arr->capacity *= 2;
    }
    //减少
    if (reSize < arr->capacity / 4 && arr->capacity / 4 >= MIN_CAPACIRY) {
        arr->capacity /= 4;
    }
    arr->data = realloc(arr->data, sizeof(char*) * arr->capacity);
    checkPtr(arr->data);
}

void checkPtr(void* ptr) {
    if (ptr == NULL) {
        printf("分配内存失败\n");
        exit(1);
    }
}