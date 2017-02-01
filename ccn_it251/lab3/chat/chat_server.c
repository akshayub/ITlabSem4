#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#define SERV_PORT 5576

int main(int argc, char const *argv[]) {
    int i,j;
    ssize_t n;
    char message[80],recvline[80];
    struct sockaddr_in servaddr,cliaddr;
    int listenfd,connfd,clilen;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    listen(listenfd,1);
    clilen=sizeof(cliaddr);
    printf("Waiting for the client...\n");
    connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
    printf("User connected!\n");
    do {
        // printf("Waiting for the client...\n");
        read(connfd,recvline,80);
        printf("%s\n",recvline);
        printf("Enter a message: ");
        gets(message);
        write(connfd,message,sizeof(message));
    } while (strcmp(message,"quit") != 0);
    close(listenfd);
    return 0;
}
