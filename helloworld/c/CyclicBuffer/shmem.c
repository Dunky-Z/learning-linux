#include "shmem.h"

SHMS *shms;
void shm_init(SHMS *shms)
{
    shms->shmkey = ftok("./shmem.c", 0);
    shms->buff_size = BUFFERSIZE;
    shms->shmflag = IPC_CREAT | 0600;
    shms->shmid = my_shmget(shms);
    shms->shmaddr = NULL;
    shms->shmptr = my_shmat(shms);
}

int my_shmget(SHMS *shms)
{
    int ret;
    ret = shmget(shms->shmkey, shms->buff_size, shms->shmflag);
    if (ret == -1)
    {
        printf("shmget error!\n");
        exit(EXIT_FAILURE);
    }
    return ret;
}

uint8_t *my_shmat(SHMS *shms)
{
    uint8_t *ret;
    ret = (uint8_t *)shmat(shms->shmid, shms->shmaddr, shms->shmflag);
    if (ret == (void *)-1)
    {
        printf("shmat error!\n");
        exit(EXIT_FAILURE);
    }
    return ret;
}

void my_fflush(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void server(CyCBuf *cycbuff, SHMS *shms)
{
    printf("Server is running with SHM id : %d\n", shms->shmid);
    cycbuff_init(cycbuff);
    while (1)
    {
        char ch;
        while (cycbuff->flag == 1)
        {
            printf("Enter Message: ");
            scanf("%c", &ch);
            my_fflush();
            cycbuff_write(cycbuff, ch);
        }
    }
    exit(0);
}

void client(CyCBuf *cycbuff, SHMS *shms)
{
    printf("Server operational: shm id is %d\n", shms->shmid);
    printf("client buf : %p\n", cycbuff->buf);
    while (1)
    {
        while (cycbuff->flag == 0)
        {
            uint8_t ch = cycbuff_read(cycbuff);
            printf("Message received: %c \n", ch);
        }
    }
}

void dele(void)
{
    shmdt(shms->shmaddr);
    shmctl(shms->shmid, IPC_RMID, NULL);
}

int main(int argc, char *argv[])
{
    shms = malloc(sizeof(SHMS));
    shm_init(shms);

    CyCBuf *cycbuff = (CyCBuf *)shms->shmptr;
    printf("shms : %p\n", shms);

    printf("cycbuff : %p\n", cycbuff);

    if (argc < 2)
    {
        server(cycbuff, shms);
    }
    else
    {
        client(cycbuff, shms);
    }
    atexit(dele);

    return 0;
}