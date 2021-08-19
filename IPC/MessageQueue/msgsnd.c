#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
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
    char buffer[BUFSIZ];
    key_t msgKey = ftok("./msgsnd.c", 0);
    msgid = msgget(msgKey, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        fprintf(stderr, "masget failed error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        printf("Enter some text: \n");
        fgets(buffer, BUFSIZ, stdin);
        message.msg_type = 1; // 注意2
        strcpy(message.msg, buffer);

        // 向队列里发送数据
        if (msgsnd(msgid, (void *)&message, MAX_TXT, 0) == -1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }

        // 输入end结束输入
        if (strncmp(buffer, "end", 3) == 0)
        {
            break;
        }

        sleep(1);
    }

    exit(EXIT_SUCCESS);
}