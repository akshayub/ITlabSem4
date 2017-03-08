#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<math.h>
#include<stdlib.h>
#define SERV_PORT 5576

int seq(int x,int h) {
    return (x/h)%2;
}

int power_of_2(int x) {
    if (x == 1) return 1;
    while (x > 0) {
        if (x == 2) return 1;
        if (x%2 == 1) return 0;
        x /= 2;
    }
    return 1;
}

char *hamming(char *input,int len) {
    int in_num[len],i;
    for (i=0; i < len; i++) {
        in_num[len-i-1] = input[i] - '0';
    }
    int red = 0,index=0,j;
    index=0;
    while (pow(2,red) < len+red+1) { red++; }
    int hammed[len+red+1];
    for (i=1; i< len+red+1; i++) {
        if (!power_of_2(i)) {
            hammed[i] = in_num[index++];
        }
        else {
            hammed[i] = 0;
        }
    }
    int k = 1;
    while (k < pow(2,red)+1) {
        int xor = 0;
        for (j=k+1; j < len+red+1; j++) {
            if (seq(j,k)) {
                xor ^= hammed[j];
            }
        }
        hammed[k] = xor;
        k*=2;
    }
    long int res=0;
    char *ans = malloc(sizeof(char) * (len+red+1));
    for (i=len+red;i>0;i--) {
        res = res*10 + hammed[i];
        ans[i] = hammed[i] + '0';
    }
    ans[0] = '\0';
    char *answer = malloc(sizeof(char) * (len+red+1));
    for (i=len+red;i>=0;i--) {
        answer[i] = ans[len+red-i];
    }
    return answer;
}


int main(int argc,char **argv)
{
    int i,j;
    ssize_t n;
    char *input = malloc(sizeof(char)*80);
    struct sockaddr_in servaddr;
    int sockfd;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);
    inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    printf("Server connected!\n");
    //Server code ends here and user input starts here
    int red = 0;
    printf("Enter the string: ");
    scanf("%s",input);
    int len = strlen(input);
    while (pow(2,red) < len+red+1) { red++; }
    char *answer = malloc(sizeof(char)*(80));
    answer = hamming(input,len);
    puts(answer);
    //Ends here
    write(sockfd,answer,len+red+1);
    close(sockfd);
    return 0;
}
