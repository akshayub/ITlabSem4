#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#define SERV_PORT 5576

int main(int argc, char const *argv[]) {
    int i,j;
    ssize_t n;
    char message[800],recvline[800];
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

    read(connfd,recvline,800);
    recvline[strlen(recvline) - 1] = '\0';
    printf("$%s\n",recvline);
    strcat(recvline, " > tmpFile");
    puts(recvline);
    system(recvline);

    FILE *fp = fopen("tmpFile","r");
    while (fgets(message, 800, fp) != NULL) {
        printf("%s", message);
        write(connfd, message, sizeof(message));
    }
    fclose(fp);

    system("rm -f tmpFile");

    close(listenfd);
    return 0;
}
