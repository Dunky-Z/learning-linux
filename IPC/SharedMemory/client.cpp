#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define BUF_SIZE 1024

int main(void)
{
    key_t shmkey;

    shmkey = ftok("./client.cpp", 0);

    char *shmptr;
    // 创建或打开内存共享区域
    if ((shmid = shmget(MYKEY, BUF_SIZE, IPC_CREAT)) == -1)
    {
        printf("shmget error!\n");
        exit(1);
    }
    if ((shmptr = shmat(shmid, 0, 0)) == (void *)-1)
    {
        printf("shmat error!\n");
        exit(1);
    }
    while (1)
    {
        // 把用户的输入存到共享内存区域中
        printf("input:");
        scanf("%s", shmptr);
    }
    exit(0);
}
#