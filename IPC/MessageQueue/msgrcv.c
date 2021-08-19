#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/msg.h>

#define MAX_TXT 512

struct msg_st
{
    long int msg_type;
    char msg[MAX_TXT];
};

int main()
{
    struct msg_st message;
    int msgid = 1;
    long int msgtype = 0;
    key_t msgKey = ftok("./msgsnd.c", 0);
    msgid = msgget(msgKey, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        fprintf(stderr, "masget failed error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        if (msgrcv(msgid, (void *)&message, BUFSIZ, msgtype, 0) == -1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }

        printf("You wrote: %s\n", message.msg);

        if (strncmp(message.msg, "end", 3) == 0)
        {
            break;
        }
    }

    exit(EXIT_SUCCESS);
}