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
    key_t key;
    struct msgbuf rcvbuffer;
    key = atoi(argv[1]);
    if ((msqid = msgget(key, 0666)) < 0)
        die("msgget()");
    //Receive an answer of message type 1.
    if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0)
        die("msgrcv");
    printf("Message received: %s\n", rcvbuffer.mtext);
    sleep(1);
    if ((msqid = msgget(key, 0666)) < 0)
        die("msgget()");
    struct msgbuf sbuf;
    size_t buflen;
    sbuf.mtype = 1;
    strcpy(sbuf.mtext,"Loud and Clear");
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
    if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0)
        die("msgrcv");
    printf("Message received: %s\n", rcvbuffer.mtext);
    return 0;
}
