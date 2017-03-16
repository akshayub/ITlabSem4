#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]) {
    if (argc != 2){
        puts("Usage: ./server PORT_NUMBER");
        exit(-1);
    }
    char msg[100] = "";
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int clilen, client;
    struct sockaddr_in serv, cli;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(atoi(argv[1]));

    bind(sock, (struct sockaddr*) &serv, sizeof(serv));
    listen(sock,5);
    puts("Server started. Waiting for connections ...");
    clilen = sizeof(cli);
    client = accept(sock, (struct sockaddr*) &cli, &clilen);
    puts("User connected");

    while (read(client, msg, 100)) {
        if (strcasecmp(msg, "quit\n") == 0){
            puts("Closed");
            break;
        }
        double num1, num2, ans = 0;
        char op;
        puts("GOT from client");
        puts(msg);
        sscanf(msg, "%c %lf %lf", &op, &num1, &num2);
        // printf("%d %d %c\n", num1, num2, op); //for debug
        switch (op) {
            case '+':   ans = num1 + num2;  break;
            case '-':   ans = num1 - num2;  break;
            case '*':
            case '^':   ans = num1 * num2;  break;
            case '/':
                if(num2 == 0)   break;
                ans = num1 / num2;  break;
        }
        sprintf(msg, "%s %.2lf\n", "The result is ", ans);
        // puts(msg); //for debug
        write(client, msg, sizeof(msg));
    }

    close(sock);

    return 0;
}
