#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#define SERV_PORT 5000

int main(int argc, char const *argv[]) {
    int i,j;
    ssize_t n;
    char recvData[1000];
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
    printf("Waiting for the client...\n");
    connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);

    printf("User connected!\n");

    read(connfd,recvData,1000);
    printf("Received data is \n%s\n", recvData);


    close(listenfd);
    return 0;
}
