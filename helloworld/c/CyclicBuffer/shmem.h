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

void server(CyCBuf *cycbuff);
void client(CyCBuf *cycbuff, int shmid);
int myShmget(key_t shmkey, int size, int shmflag);
void *myShmat(int shmid, const void *shmaddr, int shmflg);
void sigdelete(int signum);
void delete (void);
