//file transfer client program:fileclient.cc

#include<stdio.h>
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
    char message[80],recvline[80];
    struct sockaddr_in servaddr;
    int sockfd;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);
    inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    printf("Server connected!\n");
    do {
        printf("Enter a message: ");
        gets(message);
        write(sockfd,message,sizeof(message));
        // printf("Waiting for the server...\n");
        read(sockfd,recvline,80);
        printf("%s\n",recvline);
    } while (strcmp(message,"quit") != 0);
    close(sockfd);
    return 0;
}
