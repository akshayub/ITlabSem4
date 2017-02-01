#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define SERV_PORT 5000

int main(int argc, char const *argv[]) {
    int i,j;
    ssize_t n;
    char filename[80], recvline[80];
    struct sockaddr_in servaddr;
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    printf("Enter filename : ");
    scanf("%s", filename);

    write(sockfd, filename, sizeof(filename));

    printf("\nData from server: \n");

    while (read(sockfd, recvline, 80) != 0) {
        fputs(recvline, stdout);
    }

    close(sockfd);

    return 0;
}
