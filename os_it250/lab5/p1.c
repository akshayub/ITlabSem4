#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXSIZE 128

void die(char *s){
    perror(s);
    exit(1);
}

struct msgbuf{
    long mtype;
    char mtext[MAXSIZE];
};

int main(int argc, char **argv){
    if (argc != 2 ){
	fprintf(stderr, "Usage: %s <Integer value for key. Say 1234? 12345?>\n", argv[0]);
	exit(-1);
    }
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    struct msgbuf sbuf;
    struct msgbuf rcvbuffer;
    size_t buflen;
    key = atoi(argv[1]);
    if ((msqid=msgget(key,msgflg))< 0)
            die("msgget");
    sbuf.mtype = 1;
    //Sending the message
    strcpy(sbuf.mtext,"Are you hearing me?");
    printf("%s\n",sbuf.mtext);
    buflen = strlen(sbuf.mtext) + 1;
    if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
    {
        printf ("%d, %ld, %s, %lu\n", msqid, sbuf.mtype, sbuf.mtext, buflen);
        die("msgsnd");
    }
    else
        printf("Message Sent\n");
    sleep(5);
    //Receiving the message
    if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0)
        die("msgrcv");
    printf("Message received: %s\n", rcvbuffer.mtext);
    //Sending the message again
    strcpy(sbuf.mtext,"I can hear you too.");
    printf("%s\n",sbuf.mtext);
    buflen = strlen(sbuf.mtext) + 1;
    if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
    {
        printf ("%d, %ld, %s, %lu\n", msqid, sbuf.mtype, sbuf.mtext, buflen);
        die("msgsnd");
    }
    else
        printf("Message Sent\n");
    return 0;
}
