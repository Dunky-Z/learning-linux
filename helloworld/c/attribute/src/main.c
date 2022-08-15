#include <stdio.h>
#include <stdlib.h>
#include "main.h"
// struct stu {
//   char sex;
//   int length;
//   char name[2];
//   char value[15];
// } __attribute__((aligned(8)));
// struct stu my_stu;

// int main() {
//   printf("%ld \n", sizeof(my_stu));
//   printf("%p %p,%p,%p \n", &my_stu, &my_stu.length, &my_stu.name,
//          &my_stu.value);
//   f();

//   return 0;
// }

/*==============================================================*/
// void __f() { printf("__attribute__ test\n"); };
// void f() __attribute__((weak, alias("__f")));
// int main() {
//   f();

//   return 0;
// }

/*==============================================================*/
// void *my_calloc(int a) __attribute__((alloc_size(1)));
// void *my_realloc(int a, int b, int c) __attribute__((alloc_size(2, 3)));
// void *my_calloc(int a) { return NULL; }
// void *my_realloc(int a, int b, int c) { return NULL; }

// int main() {
//   void *const p = my_calloc(100);
//   printf("size : %ld\n", __builtin_object_size(p, 0));

//   void *const a = my_realloc(1, 2, 3);
//   printf("size : %ld\n", __builtin_object_size(a, 1));

//   return 0;
// }

/*==============================================================*/
// #include <stdlib.h>
// #include <string.h>

// void test_cleanup(char **str) {
//   printf("after cleanup: %s\n", *str);
//   free(*str);
// }

// int main(int argc, char **argv) {

//   char *str __attribute__((__cleanup__(test_cleanup))) = NULL;
//   str = (char *)malloc((sizeof(char)) * 100);
//   strcpy(str, "test");
//   printf("before cleanup : %s\n", str);
//   return 0;
// }

/*==============================================================*/
// test typedef

// int main(int argc, char **argv)
// {
//     // test_typedef *a = (test_typedef *)malloc(sizeof(test_typedef));
//     // a->num          = 1;
//     // printf("test typedef a = %d\n", a->num);
//     printf("test typedef a");

//     return 0;
// }

/*==============================================================*/

// int main()
// {
//     int i;
//     // printf("please input your year\n");
//     scanf("%d", &i);
//     printf("you are %d old man %s\n", i, (i==26) ? ("true") :("false"));
//     return 0;
// }

/*==============================================================*/


enum REGION {
    REGION1,
    REGION2,
    REGION3,
    REGION4,
    REGION5,
    REGION6,
} region;

typedef struct ReginEntry
{
    unsigned long long  start;
    unsigned long long size;
} ReginEntry;

ReginEntry region_entry[] = {
    [REGION1]  = {},
    [REGION2]  = {},
    [REGION3]  = {},
    [REGION4]  = {},
    [REGION5]  = {},
    [REGION6] = {},
};
#define MEM_SIZ_32M  0x2000000
#define MEM_SIZ_64M  0x4000000
#define MEM_SIZ_128M 0x8000000

int main()
{
    // unsigned int *start_addr = 0x80000000;

    // region_entry[REGION1].start = start_addr;
    // region_entry[REGION1].size = MEM_SIZ_32M;
    // region_entry[REGION2].start = (start_addr + MEM_SIZ_32M);
    // region_entry[REGION2].size = MEM_SIZ_32M;
    // region_entry[REGION3].start = start_addr;
    // region_entry[REGION3].size = MEM_SIZ_64M;

    // printf("addr = %x\n", start_addr);
    // printf("region1 = %x, size = %x\n", region_entry[REGION1].start,
    //        region_entry[REGION1].size);
    unsigned long long i64_addr_64 = 0x1234567890abcdef;
    int i32_addr_32 = 0x92345789;
    unsigned long long i64_addr_32 = 0x2234567890;

    printf("0x%x\r\n", i32_addr_32);
    printf("0x%llx\r\n", i64_addr_64);
    printf("0x%lx\r\n", i64_addr_32);
    printf("0x%llx, 0x%llx,0x%x\r\n", i64_addr_64, i64_addr_32, i32_addr_32);
    return 0;
}
