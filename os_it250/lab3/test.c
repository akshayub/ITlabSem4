// Code to test execution of linux commands through a C program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    execlp("ls", "ls", "-l", NULL);
    return 0;
}
