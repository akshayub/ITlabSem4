#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    int tracer = 0;
    // printf("%d\n", pid);
    // printf("process begins %d\n",tracer++);
    pid_t pid = fork();
    printf("%d\n", pid);
    printf("process begins %d\n",tracer++);

    if (pid == 0){
        printf("%d\n", pid);
        printf("Child process begins %d\n",tracer++);
        printf("Child process ends %d\n",tracer++);
    }else if (pid > 0){
        printf("%d\n", pid);
        printf("parent process beginssss %d\n",tracer++);
        printf("parent process endssss %d\n",tracer++);
    }
    wait(0);

    printf("process ends %d\n",tracer++);
    printf("%d\n", pid);
    return 0;
}
