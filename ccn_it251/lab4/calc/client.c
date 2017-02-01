#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include <limits.h>
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
    int num1, num2;
    char op;
    while(1) {
        printf("operation: ");
        scanf("%c", &op);

        if (op == 'q' | op == 'Q'){
            close(sockfd);
            exit(0);
        }

        printf("Num1: ");
        scanf("%d", &num1);

        printf("Num2: ");
        scanf("%d", &num2);

        sprintf(message, "%c %d %d", op, num1, num2);
        write(sockfd,message,sizeof(message));
    }
    close(sockfd);
    return 0;
}
