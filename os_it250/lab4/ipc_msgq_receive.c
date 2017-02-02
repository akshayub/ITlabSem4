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
    int msqid;
    key_t key;
    struct msgbuf rcv_buffer;
    key = 1234;

    if ((msqid=msgget(key, 0666)) < 0)
        die("msgget");
    if (msgrcv(msqid, &rcv_buffer, MAXSIZE, 1, 0) < 0)
        die("msgrcv");
    printf("%s\n", rcv_buffer.mtext);
    exit(0);
    return 0;
}
