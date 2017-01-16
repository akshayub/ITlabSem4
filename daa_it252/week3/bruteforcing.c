#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    FILE * fp = stdin;
    int n = 0;
    int *ar = calloc(1000,sizeof(int));

    while(scanf("%d", &ar[n++]) == 1){}
    n--;

    int max=ar[0], max_i=0, max_j=0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int temp = 0;
            for (int k=i; k<j; k++)
                temp += ar[k];
            if (temp > max){
                max = temp;
                max_i = i;
                max_j = j;
            }
        }
    }

    printf("Max subarray is \n");
    for (int i = max_i; i <= max_j; i++)
        printf("%d  ", ar[i]);
    printf("\nSum : %d\n", max);

    return 0;
}
