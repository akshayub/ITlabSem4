#include <stdio.h>
#include <stdlib.h>

long recursions = 0;

long fib(long n){
    recursions++;
    if ( n == 1 || n == 0 ){
        return n;
    }
    else
        return fib(n-1) + fib(n-2);
}

int main(int argc, char const *argv[]) {
    if (argc != 2){
        printf("Pass n as commandline argument\n");
        exit(0);
    }
    long n = strtol(argv[1], NULL, 10);
    printf("Fibonacci(%ld) = %ld\n", n, fib(n));
    printf("Total recursions is %ld\n", recursions);
    return 0;
}
