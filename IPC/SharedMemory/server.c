#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int shmid;
    key_t shmkey;
    char *shmptr;
    shmkey = ftok("./client.c", 0);
    // 创建或打开内存共享区域
    shmid = shmget(shmkey, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        printf("shmget error!\n");
        exit(1);
    }

    //将共享内存映射到当前进程的地址中，之后直接对进程中的地址addr操作就是对共享内存操作
    shmptr = (char *)shmat(shmid, 0, 0);
    if (shmptr == (void *)-1)
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