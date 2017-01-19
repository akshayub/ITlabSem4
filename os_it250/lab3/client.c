#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {
    char fname[100], buffer[1025];
    int request, response;

    request = open("req.fifo", O_WRONLY);
    response = open("res.fifo", O_RDONLY);

    if (request < 0 || response < 0){
        printf("Server not started\n");
        exit(1);
    }

    printf("Enter filename to request:\n");
    scanf("%s", fname);
    write(request, fname, sizeof(fname));
    printf("Response received\n");
    int n;
    while((n = read(response, buffer, sizeof(buffer))) > 0)
        write(1, buffer, n);
    close(request);
    close(response);
    return 0;
}
