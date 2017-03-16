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
    if (argc != 3){
        puts("Usage: ./client SERVER_IP SERVER_PORT");
        exit(-1);
    }
    char msg[100] = "";
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(atoi(argv[2]));
    inet_pton( AF_INET, argv[1], &serv.sin_addr);

    bind(sock, (struct sockaddr*) &serv, sizeof(serv));
    connect(sock, (struct sockaddr*) &serv, sizeof(serv));
    puts("Connected to server");
    printf("Enter\n\
                1 for Addition\n\
                2 for Subtraction\n\
                3 for Multiplication\n\
                4 for Division\n\
                5 for Square\n\
                0 to Quit\n");
    while (1) {
        int op;
        double num1, num2;
        char c;
        printf("Choice? ");
        scanf("%d", &op);
        switch (op) {
            case 1: c = '+'; break;
            case 2: c = '-'; break;
            case 3: c = '*'; break;
            case 4: c = '/'; break;
            case 5: c = '^'; break;
            case 0: c = 'q'; break;
            default:    continue;
        }
        if (c == 'q'){
            strcpy(msg, "quit\n");
            puts("Closing");
            write(sock, msg, sizeof(msg));
            break;
        }
        else if (op == 5){
            printf("Enter number: ");
            scanf("%lf", &num1);
            num2 = num1;
        }
        else{
            printf("Enter the numbers\n");
            scanf("%lf%lf", &num1, &num2);
        }
        sprintf(msg, "%c %lf %lf", c, num1, num2);
        // puts(msg); // for debugging
        write(sock, msg, sizeof(msg));
        read(sock, msg, 100);
        puts(msg);
    }

    close(sock);
    return 0;
}
