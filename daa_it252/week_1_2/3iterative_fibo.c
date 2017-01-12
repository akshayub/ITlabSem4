#include <stdio.h>
#include <stdlib.h>

long iterations = 0;

long fib(long n){
    if (n<2)
        return n;
    int a = 1, b = 1, c;
    for (int i=0; i<n-2; i++) {
        iterations++;
        c = a+b;
        b = a;
        a = c;
    }
    return a;
}

int main(int argc, char const *argv[]) {
    if (argc != 2){
        printf("Pass n as commandline argument\n");
        exit(0);
    }
    long n = strtol(argv[1], NULL, 10);
    printf("Fibonacci(%ld) = %ld\n", n, fib(n));
    printf("Total iterations is %ld\n", iterations);
    return 0;
}
