#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
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
    while(1){
        read(connfd,recvline,80);
        printf("%s\n",recvline);
        int num1, num2;
        char op;
        sscanf(recvline, "%c %d %d", &op, &num1, &num2);
        int ans;
        switch (op) {
            case 'q':
            case 'Q':
                close(listenfd);
                printf("Closed!\n");
                exit(0);
            case '+':
                ans = num1+num2;
                break;
            case '-':
                ans = num1-num2;
                break;
            case '*':
                ans = num1*num2;
                break;
            case '/':
                if (num2 == 0)
                    ans = INT_MIN;
                else
                    ans = num1+num2;
                break;
            case '%':
                if (num2 == 0)
                    ans = INT_MIN;
                else
                    ans = num1%num2;
                break;
        }

        sprintf(message, "Answer is %d\n", ans);
        write(connfd,message,sizeof(message));
    }
    close(listenfd);
    return 0;
}
