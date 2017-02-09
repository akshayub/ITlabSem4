#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAXSIZE 256

void die(char *s){
    perror(s);
    exit(-1);
}

struct msgbuf {
    long mtype;
    char mtext[MAXSIZE];
};

int main(int argc, char const *argv[]) {
    int msqid, msgflg = IPC_CREAT|0666;
    key_t key;
    struct msgbuf sbuf;
    struct msgbuf rcv_buffer;
    size_t buflen;
    key = 1234;

    if ((msqid=msgget(key, msgflg)) < 0)
        die("msgget");
    sbuf.mtype = 1;

    while (1) {
        printf("Enter a message: ");
        fgets(sbuf.mtext, MAXSIZE, stdin);
        buflen = strlen(sbuf.mtext) + 1;
        if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0){
            printf("%d, %ld, %s, %lu\n", msqid, sbuf.mtype, sbuf.mtext, buflen);
            die("msgsnd");
        }
        else
            printf("Message sent\n");

        if ((msqid=msgget(key, 0666)) < 0)
            die("msgget");
        if (msgrcv(msqid, &rcv_buffer, MAXSIZE, 1, 0) < 0)
            die("msgrcv");
        printf("%s\n", rcv_buffer.mtext);
    }

    exit(0);
    return 0;
}
