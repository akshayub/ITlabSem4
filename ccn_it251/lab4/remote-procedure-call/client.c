#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#define SERV_PORT 5576
int main(int argc,char **argv)
{
    int i,j;
    ssize_t n;
    char cmd[800],recvline[800];
    struct sockaddr_in servaddr;
    int sockfd;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);
    inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    printf("Connected to server!\n");

    printf("Enter a command to execute: $");
    fgets(cmd, 800, stdin);
    write(sockfd,cmd,sizeof(cmd));

    printf("\nData from server: \n");

    while (read(sockfd, recvline, 800) != 0) {
        fputs(recvline, stdout);
    }

    printf("\n\nClosed\n");
    close(sockfd);
    return 0;
}
