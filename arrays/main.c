#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include "array.h"
#include "array.c"
#include "array_test.c"

void main() {
    // char** strArr;
    // strArr = malloc(sizeof(char*));

    // *strArr = "hello";
    // strArr++;
    // *strArr = "world";

    // printf("%s\n", *strArr);
    // strArr--;
    // printf("%s\n", *strArr);

    // free(strArr);
    // strArr = NULL;

    // char* a1 = "hello";
    // char* a2 = "hello";

    // printf("%d", a1 == a2);

    test_all();
}
