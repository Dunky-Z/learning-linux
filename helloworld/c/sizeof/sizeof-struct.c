#include <stdio.h>
typedef struct Test1
{
    int a;
    int b;
} T1;
typedef struct Test2
{
    char a;
    char b;
} T2;
typedef struct Test3
{
    int a;
    char b;
    int c;
} T3;
typedef struct Test4
{
    int a;
    short b;
} T4;
typedef struct Test5
{
    char a;
    int b;
    char c;
} T5;
typedef struct Test6
{
    char a;
    char b;
    int c;
} T6;

typedef struct Test7
{
    short a;
    struct
    {
        char b;
        int c;
    } tt;
    int d;
} T7;

typedef struct Test8
{
    char a;
    struct
    {
        char b;
        int c;
    } tt;
    char d;
    char e;
    char f;
    char g;
    char h;
} T8;

typedef struct Test9
{
    char a;
    float b;
    int c[2];
} T9;

int main()
{
    T1 t1;
    int siz01 = sizeof(t1);
    printf("t1: %d\n", siz01); //t1: 8

    T2 t2;
    int siz02 = sizeof(t2);
    printf("t2: %d\n", siz02); //t2: 2

    T3 t3;
    int siz03 = sizeof(t3);
    printf("t3: %d\n", siz03); //t3: 12

    T4 t4;
    int siz04 = sizeof(t4);
    printf("t4: %d\n", siz04); //t4: 8

    T5 t5;
    int siz05 = sizeof(t5);
    printf("t5: %d\n", siz05); //t5: 12

    T6 t6;
    int siz06 = sizeof(t6);
    printf("t6: %d\n", siz06); //t6: 8

    T7 t7;
    int siz07 = sizeof(t7);
    printf("t7: %d\n", siz07); //t7: 16

    T8 t8;
    int siz08 = sizeof(t8);
    printf("t8: %d\n", siz08); //t8: 20

    T9 t9;
    int siz09 = sizeof(t9);
    printf("t9: %d\n", siz09); //t9: 24
    return 0;
}
