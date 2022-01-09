#include <stdio.h>

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
#include <stdlib.h>
#include <string.h>

void test_cleanup(char **str) {
  printf("after cleanup: %s\n", *str);
  free(*str);
}

int main(int argc, char **argv) {

  char *str __attribute__((__cleanup__(test_cleanup))) = NULL;
  str = (char *)malloc((sizeof(char)) * 100);
  strcpy(str, "test");
  printf("before cleanup : %s\n", str);
  return 0;
}