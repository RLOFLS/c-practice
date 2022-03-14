#include "ext.h"
#include<math.h>

//输出hello-world
void helloWorld()
{
    printf("Hello World");
}

//根据值输出数据类型
void printVariableType()
{
    int a = 1;
    float f = 22.09;
    char string[] = "hello world";

    printf("%d is int\r\n", a);
    printf("%f is float\r\n", f);
    printf("%s is char\r\n", string);
}

//接收标准输出并输出
void WelcomeUserInput()
{
    printf("请输入姓名：");
    char *name;
    scanf("%ms", &name);
    printf("Welcome %s\r\n", name);

    free(name);
    
}

//计算圆的面积
void caculateAreaOfCircle()
{
    printf("请输入圆的半径：");

    float f;
    scanf("%f", &f);
    
    float area = PI * powf(f, 2);

    printf("圆的面积是： %f", area);
}

void exec5()
{
    int s;
    printf("请输入秒数：");
    scanf("%d", &s);

    int hours = s / 3600;
    int remaind = s % 3600;

    int minutes = remaind / 60;
    remaind %= 60;

    printf("%d 秒是： %d 小时， %d 分钟， %d 秒", s, hours, minutes, remaind);
}

void exec6()
{
    int numberator;
    int denominator;

    printf("请输入整数分子：");
    scanf("%d", &numberator);
    printf("请输入整数分母：");
    scanf("%d", &denominator);

    int remainder = numberator % denominator;
    if (remainder > 0) {
        printf("%d 除以 %d 有余数： %d", numberator, denominator, remainder);
    } else {
        printf("%d 除以 %d 没有余数", numberator, denominator);
    }
}