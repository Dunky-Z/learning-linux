#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int shmid;
    char *shmptr;
    key_t shmkey;
    shmkey = ftok("./client.c", 0);
    // 创建或打开内存共享区域
    shmid = shmget(shmkey, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        printf("shmget error!\n");
        exit(1);
    }

    //将共享内存映射到当前进程的地址中，之后直接对进程中的地址addr操作就是对共享内存操作
    shmptr = (char *)shmat(shmid, NULL, 0);
    if (shmptr == (void *)-1)
    {
        fprintf(stderr, "shmat error!\n");
        exit(1);
    }

    while (1)
    {
        // 每隔 3 秒从共享内存中取一次数据并打印到控制台
        printf("string:%s\n", shmptr);
        sleep(3);
    }
    exit(0);
}