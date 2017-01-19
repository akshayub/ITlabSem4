#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
    int pfd[2];
    int test = pipe(pfd);
    if (test == -1){
        printf("Error in creating pipe\n");
        exit(1);
    }
    int pid = fork();
    // if (!fork())  // Equivalent
    if (!pid){
        close(1);   // Closing stdout to redirect output to pipe
        dup(pfd[1]);    //Write end. making stdout as pipe output
        close(pfd[0]);
        execlp("ls", "ls", "-l", NULL);
    }
    else{
        close(0);   // Closing stdoin to redirect input to pipe
        dup(pfd[0]);    //Read end. making stdin as pipe input
        close(pfd[1]);
        execlp("wc", "wc", NULL);
    }
    return 0;
}
