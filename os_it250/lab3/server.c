#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {
    char fname[100], buffer[1025];
    int request, response, fileIO;
    mkfifo("req.fifo", 0777);
    mkfifo("res.fifo", 0777);
    printf("Waiting for request ...\n");

    request = open("req.fifo", O_RDONLY);
    response = open("res.fifo", O_WRONLY);

    read(request, fname, sizeof(fname));

    printf("Received request for %s\n", fname);
    fileIO = open(fname, O_RDONLY);
    if (fileIO < 0)
        write(response, "File not found\n", 15);
    else{
        int n = 0;
        while ((n = read(fileIO, buffer, sizeof(buffer))) > 0) {
            write(response, buffer, n);
        }
    }
    close(request);
    close(response);
    unlink("req.fifo");
    unlink("res.fifo");
    return 0;
}
