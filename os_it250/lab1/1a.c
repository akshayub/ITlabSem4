#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// Remove wait for both demo

// For zombie process demo
// add sleep in parent process and exit in child
// do ps -e and you can see a defunct process

// For orphan process demo
// add sleep in child process

int fibo(int n){
    if ( n <= 2 )
        return 1;
    else
        return fibo(n-1) + fibo(n-2);
}

int main(int argc, char const *argv[]) {

    int n;
    printf("Enter n   ");
    scanf("%d",&n);

    pid_t pid = fork();

    if (pid == 0){
        printf("Child process begins\n");
        // sleep(5);

        for (int i=1; i<=n; i++)
            printf("%d   ", fibo(i));

        printf("\nChild process ends\n");
        // exit(0);
    }
    else if (pid > 0){
        printf("Parent begins\n");
        // sleep(10);
        printf("Parent waiting for child to end\n"); wait(0);
        printf("Parent ends\n");
    }
    else if (pid < 0){
        printf("Failed\n");
    }

    return 0;
}
