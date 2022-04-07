#include<stdio.h>
int add(int, int);
void main(int argc, char *agrv[]) {

    int array1[10], array2[10];

    for (int i = 0; i < 10; i++)
    {
        array1[i] = i;
    }
    

	int *ip1, *ip2 = &array2[0];
	int *ep = &array1[9];
	for(ip1 = &array1[0]; ip1 <= ep; ip1++)
		*ip2++ = *ip1;

    for (int i = 0; i < argc; i++)
    {
        printf("参数 %d : %s\n", i, agrv[i]);
    }

    int (*addfun)();

    addfun = add;

    printf("addfun call 1 + 2 = %d\n", addfun(1, 3));
    
}



int add(int a, int b) {
    return a + b;
}