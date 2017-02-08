#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#define SERV_PORT 5000

int main(int argc, char const *argv[]) {
    int i,j;
    ssize_t n;
    FILE *fp;
    char s[80], f[80];
    struct sockaddr_in servaddr, cliaddr;
    int listenfd, connfd, clilen;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listenfd, 1);
    clilen = sizeof(cliaddr);

    printf("Waiting for client to connect ...\n");
    connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
    printf("Client connected!\n");

    read(connfd, f, 80);
    fp = fopen(f, "r");
    printf("Name of the file: %s\n", f);
    while (fgets(s, 80, fp) != NULL) {
        printf("%s", s);
        write(connfd, s, sizeof(s));
    }

    close(listenfd);
    fclose(fp);
    return 0;
}
