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

int deleteSemid = 0;
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
void server();
void client(int shmid, int semid);
int mySemget(key_t semkey, int nsems, int semflag);
int myShmget(key_t shmkey, int size, int shmflag);
void *myShmat(int shmid, const void *shmaddr, int shmflg);
int safesemctl(int semid, int semnum, int cmd, union semun arg);
int mySemop(int semid, struct sembuf *sops, unsigned nsops);
void operationP(int signum, int semnum);
void operationV(int signum, int semnum);
void sigdelete(int signum);
void delete (void);