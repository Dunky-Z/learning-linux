#include "main.h"

int mySemget(key_t semkey, int nsems, int semflag)
{
    int retval;
    if ((retval = semget(semkey, nsems, semflag)) == -1)
    {
        printf("semget error: %s.\n", strerror(errno));
        exit(254);
    }
    return retval;
}

int myShmget(key_t shmkey, int size, int shmflag)
{
    int ret;
    ret = shmget(shmkey, size, shmflag);
    if (ret == -1)
    {
        printf("shmget error!\n");
        exit(EXIT_FAILURE);
    }

    return ret;
}
void *myShmat(int shmid, const void *shmaddr, int shmflag)
{
    char *ret;
    ret = (char *)shmat(shmid, shmaddr, shmflag);
    if (ret == (void *)-1)
    {
        printf("shmat error!\n");
        exit(EXIT_FAILURE);
    }
    return ret;
}

int mySemop(int semid, struct sembuf *sops, unsigned nsops)
{
    printf("sp\n");
    int ret;
    if ((ret = semop(semid, sops, nsops)) == -1)
    {
        printf("semop failed!\n");
        exit(EXIT_FAILURE);
    }
    return ret;
}
int safesemctl(int semid, int semnum, int cmd, union semun arg)
{
    int retval;
    if ((retval = semctl(semid, semnum, cmd, arg)) == -1)
    {
        printf("semctl error: %s.\n", strerror(errno));
        exit(254);
    }
    return retval;
}

void operationP(int semid, int semnum)
{
    printf("op\n");
    struct sembuf sb;
    sb.sem_num = semnum;
    sb.sem_op = -1;
    sb.sem_flg = SEM_UNDO;
    mySemop(semid, &sb, 1);
}

void operationV(int semid, int semnum)
{
    struct sembuf sb;
    sb.sem_num = semnum;
    sb.sem_op = 1;
    sb.sem_flg = SEM_UNDO;
    mySemop(semid, &sb, 1);
}

void sigdelete(int signum)
{
    exit(0);
}
void delete (void)
{
    printf("\nMaster exiting; deleting semaphore %d.\n", deleteSemid);
    if (semctl(deleteSemid, 0, IPC_RMID, 0) == -1)
    {
        printf("Error releasing semaphore.\n");
    }
}
void server()
{
    int shmid, semid;
    union semun sunion;
    key_t shmkey, semkey;
    char *shmptr;
    shmkey = ftok("./main.c", 0);
    semkey = ftok("./server.c", 0);

    // 创建或打开内存共享区域
    shmid = myShmget(shmkey, 1024, IPC_CREAT | 0600);

    // 创建信号量
    semid = mySemget(semkey, 2, IPC_CREAT | 0600);

    // 在服务器端程序退出时删除掉信号量集。
    deleteSemid = semid;
    atexit(&delete);

    signal(SIGINT, &sigdelete);
    // 打印共享内存 ID 和 信号量集 ID，客户端程序需要用它们作为参数
    printf("Server is running with SHM id : %d\n", shmid);
    printf("Server is running with SEM id : %d\n", semid);

    sunion.val = 1;
    safesemctl(semid, 0, SETVAL, sunion);
    sunion.val = 0;
    safesemctl(semid, 0, SETVAL, sunion);
    //将共享内存映射到当前进程的地址中，之后直接对进程中的地址addr操作就是对共享内存操作
    shmptr = (char *)myShmat(shmid, 0, 0);

    while (1)
    {
        printf("Waiting until full...");
        fflush(stdout);
        operationP(semid, 1);
        printf("done.\n");
        printf("Message received: %s.\n", shmptr);
        operationV(semid, 0);
    }
    exit(0);
}

void client(int shmid, int semid)
{
    char *shmptr;
    shmptr = myShmat(shmid, 0, 0);
    printf("Client operational: shm id is %d, sem id is %d\n", shmid, semid);
    while (1)
    {
        printf("Waiting until empty...");
        fflush(stdout);
        operationP(semid, 0);
        printf("done.\n");
        printf("Enter Message: ");
        fgets(shmptr, 1024, stdin);
        operationV(semid, 1);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        server();
    }
    else
    {
        client(atoi(argv[1]), atoi(argv[2]));
    }
    return 0;
}