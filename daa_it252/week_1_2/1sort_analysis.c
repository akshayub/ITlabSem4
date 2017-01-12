#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap (int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}

long bubble_sort(int *ar, int n){
    long iterations = 0;
    for (int i = 0; i < n-1; i++){
        iterations++;
        for (int j = 0; j < n-i-1; j++){
            iterations++;
            if (ar[j] > ar[j+1])
                swap(&ar[j+1], &ar[j]);
        }
    }
    return iterations;
}

long insertion_sort(int *ar, int n){
    int i, key, j;
    long iterations = 0;
    for (i = 1; i < n; i++){
        iterations++;

        key = ar[i];
        j = i-1;

        while (j >= 0 && ar[j] > key){
            iterations++;

            ar[j+1] = ar[j];
            j = j-1;
        }

        ar[j+1] = key;
    }
    return iterations;
}

void reverse(int *ar, int n){
    for ( int i=0; i < n/2; i++)
        swap(&ar[i], &ar[n-i-1]);
}

int main(void){

    FILE *f = fopen("numbers_list","r");
    int n = 0;
    int *ar = calloc(10001, sizeof(int));

    char x[100];

    long bubble_sorted, bubble_unsorted, bubble_random, insertion_sorted, insertion_unsorted, insertion_random;

    // Sorting for random numbers
    while (fgets(x,100,f)) {
        ar[n++] = strtol(x, NULL, 10);
        if ( n == 10000 - 1 )
            ar = realloc(ar, n + 10000);
    }
    bubble_random = bubble_sort(ar, n);

    memset(ar, 0, n);
    fseek(f,0,SEEK_SET);
    n=0;
    while (fgets(x,100,f)) {
        ar[n++] = strtol(x, NULL, 10);
        if ( n == 10000 - 1 )
            ar = realloc(ar, n + 10000);
    }
    insertion_random = insertion_sort( ar, n);

    // Sorting for sorted numbers
    bubble_sorted = bubble_sort(ar, n);
    insertion_sorted = insertion_sort(ar, n);

    // Reversing the array for worst case
    reverse(ar,n);
    bubble_unsorted = bubble_sort(ar, n);
    reverse(ar,n);
    insertion_unsorted = insertion_sort( ar, n);

    printf ("The value of n : %d\n",n);
    printf ("Number of iterations for : \n");
    printf ("\tBubble Sort:\n");
    printf ("\t\tRandom : %ld\n", bubble_random);
    printf ("\t\tSorted : %ld\n", bubble_sorted);
    printf ("\t\tUnsorted : %ld\n", bubble_unsorted);
    printf ("\tInsertion Sort:\n");
    printf ("\t\tRandom : %ld\n", insertion_random);
    printf ("\t\tSorted : %ld\n", insertion_sorted);
    printf ("\t\tUnsorted : %ld\n", insertion_unsorted);

    fclose(f);

}
