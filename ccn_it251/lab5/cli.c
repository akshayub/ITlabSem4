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

int main(int argc,char **argv){
    int i,j;
    ssize_t n;
    char data[100];
    struct sockaddr_in servaddr;
    int sockfd;
    sockfd=socket( AF_INET, SOCK_STREAM, 0);
    setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
    bzero( &servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("Connected to server!\n");

    printf("Enter data to send\n");
    fgets(data, 100, stdin);

    // Hamming editing.
    int len = strlen(data);
    int r;
    for (r = 0; ; r++)
        if (pow(2,r) >= len + r+ 1) break;
    // R bits to be inserted.
    int newLen = len+r+2;
    char hamData[newLen];

    for (int i=0,j=1; i<len; i++){
        hamData[j] = data[i];
        j++;
    }

    write(sockfd, hamData, sizeof(hamData));

    printf("\n\nClosed\n");
    close(sockfd);
    return 0;
}
