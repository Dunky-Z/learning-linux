#include "shmem.h"

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

void server(CyCBuf *cycbuff)
{
    int shmid;
    key_t shmkey;
    uint8_t *shmptr;
    shmkey = ftok("./shmem.c", 0);
    shmid = myShmget(shmkey, 1024, IPC_CREAT | 0600);

    printf("Server is running with SHM id : %d\n", shmid);
    shmptr = myShmat(shmid, 0, 0);
    printf("Enter");
    cycbuff_init(cycbuff, 1024, shmptr);

    while (1)
    {
        uint8_t str[20];
        fflush(stdin);
        printf("Enter Message: ");
        fgets(str, 19, stdin);
        for (int i = 0; i < 20; ++i)
        {
            cycbuff_write(cycbuff, str[i]);
        }
    }
    exit(0);
}

void client(CyCBuf *cycbuff, int shmid)
{

    uint8_t *shmptr;
    shmptr = (uint8_t *)myShmat(shmid, 0, 0);

    printf("Server operational: shm id is %d\n", shmid);
    cycbuff_init(cycbuff, 1024, shmptr);

    while (1)
    {
        cycbuff_read(cycbuff);
        printf("Message received: %c", cycbuff_read(cycbuff));
    }
}

int main(int argc, char *argv[])
{
    CyCBuf *cycbuff = malloc(sizeof(CyCBuf));
    if (argc < 2)
    {
        server(cycbuff);
    }
    else
    {
        client(cycbuff, atoi(argv[1]));
    }
    return 0;
}