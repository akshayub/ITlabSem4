#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#define SERV_PORT 5576

int options = 0;

int seq(int x,int h) {
    return (x/h)%2;
}

int power_of_2(int x) {
    if (x == 1) return 1;
    while (x > 0) {
        if (x == 2) return 1;
        if (x%2 == 1) return 0;
        x /= 2;
    }
    return 1;
}

void hamcheck(char *input) {
    int len = strlen(input);
    int red = 0,index = 0,i,j;
    while (pow(2,red) <= len) { red++; }
    int check[red];
    int k = 1;
    while (k < pow(2,red)+1) {
        int xor = 0;
        for (j=k; j <= len; j++) {
            if (seq(j,k)) {
                xor ^= (input[j]-48);
                printf("xor %d\n", xor);
            }
        }
        puts("");
        check[index++] = xor;
        k*=2;
    }
    for (i = 0; i < red; i++) {
        // check[i] -= 48;
        printf("%d ",check[i]);
    }
}

int main(int argc, char const *argv[]) {
    int i=0,j;
    ssize_t n;
    char *recvline = malloc(sizeof(char)*800);
    struct sockaddr_in servaddr,cliaddr;
    int listenfd,connfd,clilen;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    listen(listenfd,1);
    clilen=sizeof(cliaddr);
    connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
    printf("User connected!\n");
    read(connfd,recvline,800);
    printf("Data received: %s\n",recvline);
    hamcheck(recvline);
    close(listenfd);
    return 0;
}
