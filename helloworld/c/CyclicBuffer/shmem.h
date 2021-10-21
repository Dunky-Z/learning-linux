#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "cyclic-buffer.h"

#define BUFFERSIZE 1024

typedef struct ShareMemoryState
{
    int shmid;
    key_t shmkey;
    uint8_t *shmptr;
    void *shmaddr;
    int buff_size;
    int shmflag;
} SHMS;
void server(CyCBuf *cycbuff, SHMS *shms);
void client(CyCBuf *cycbuff, SHMS *shms);
void shm_init(SHMS *shms);
int my_shmget(SHMS *shms);
uint8_t *my_shmat(SHMS *shms);
