#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
    }
    else if (pid > 0) {
        // Parent process
    }
    else {
        printf("Failed\n");
        exit(-1);
    }

    return 0;
}
