#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

void *create_shm()
{
    int   shmid;
    key_t shmkey;
    shmkey = 112233;
    void *shmptr;
    // 创建或打开内存共享区域
    shmid = shmget(shmkey, 3145888, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        printf("shmget error!\n");
        exit(1);
    }

    //将共享内存映射到当前进程的地址中，之后直接对进程中的地址addr操作就是对共享内存操作
    shmptr = (void *)shmat(shmid, 0, 0);
    if (shmptr == (void *)-1)
    {
        printf("shmat error!\n");
        exit(1);
    }
    return shmptr;
}