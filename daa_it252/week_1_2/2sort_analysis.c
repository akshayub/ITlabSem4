/*
 * Reasons for worst case = best case in quicksort
 * http://www.geeksforgeeks.org/when-does-the-worst-case-of-quicksort-occur/
 * https://en.wikipedia.org/wiki/Quicksort
 * Choice of pivot
    In the very early versions of quicksort, the leftmost element of the partition would often be chosen as the pivot element. Unfortunately, this causes worst-case behavior on already sorted arrays, which is a rather common use-case. The problem was easily solved by choosing either a random index for the pivot, choosing the middle index of the partition or (especially for longer partitions) choosing the median of the first, middle and last element of the partition for the pivot (as recommended by Sedgewick).[17] This "median-of-three" rule counters the case of sorted (or reverse-sorted) input, and gives a better estimate of the optimal pivot (the true median) than selecting any single element, when no information about the ordering of the input is known.
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long iters=0;

void swap (int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}

void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
    int i,j,k;
    i = j = k = 0;

    while(i<leftCount && j< rightCount) {
        iters++;
        if(L[i]  < R[j]) A[k++] = L[i++];
        else A[k++] = R[j++];
    }
    while(i < leftCount){
        A[k++] = L[i++];
        iters++;
    }
    while(j < rightCount){
        A[k++] = R[j++];
        iters++;
    }
}

void MergeSort(int *A,int n) {
    int mid,i, *L, *R;
    if(n < 2) return;

    mid = n/2;

    L = (int*)malloc(mid*sizeof(int));
    R = (int*)malloc((n- mid)*sizeof(int));

    for(i = 0;i<mid;i++,iters++) L[i] = A[i]; // creating left subarray
    for(i = mid;i<n;i++,iters++) R[i-mid] = A[i]; // creating right subarray

    MergeSort(L,mid);
    MergeSort(R,n-mid);
    Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
    free(L);
    free(R);
}

int partition(int x[], int low, int high){
    int pivot = x[high];
    int temp,i,j;
    i = low-1;
    for ( j=low; j < high; j++,iters++){
        if (x[j] <= pivot){
            i++;
            swap(&x[i],&x[j]);
        }
    }
    swap(&x[i+1], &x[high]);
    return i+1;
}

void quick_sort(int x[], int low, int high){
    iters++;
    if (low < high){
        int pivot = partition(x,low,high);
        quick_sort(x, low, pivot - 1);
        quick_sort(x, pivot + 1, high);
    }
}

void reverse(int *ar, int n){
    for ( int i=0; i < n/2; i++)
        swap(&ar[i], &ar[n-i-1]);
}

int main(void){

    FILE *f = fopen("numbers_list","r");
    int n = 0;
    int *ar = calloc(10001, sizeof(int));
    long quick_sorted, quick_unsorted, quick_random, merge_sorted, merge_unsorted, merge_random;
    char x[100];

    // Sorting for random numbers
    while (fgets(x,100,f)) {
        ar[n++] = strtol(x, NULL, 10);
        if ( n == 10000 )
            ar = realloc(ar, n + 10000);
    }
    quick_sort(ar, 0, n-1);
    quick_random = iters;
    iters = 0;

    memset(ar, 0, n);
    fseek(f,0,SEEK_SET);
    n=0;
    while (fgets(x,100,f)) {
        ar[n++] = strtol(x, NULL, 10);
        if ( n == 10000 - 1 )
            ar = realloc(ar, n + 10000);
    }
    MergeSort( ar, n);
    merge_random = iters;
    iters = 0;

    // Sorting for sorted numbers
    quick_sort(ar, 0, n-1);
    quick_sorted = iters;
    iters = 0;
    MergeSort(ar, n);
    merge_sorted = iters;
    iters = 0;

    // Reversing the array for worst case
    reverse(ar,n);
    quick_sort(ar, 0, n-1);
    quick_unsorted = iters;
    iters = 0;
    reverse(ar,n);
    MergeSort( ar, n);
    merge_unsorted = iters;
    iters = 0;

    printf ("The value of n : %d\n",n);

    printf ("\tQuick Sort:\n");
    printf ("\t\tRandom : %ld\n", quick_random);
    printf ("\t\tBest : %ld\n", quick_sorted);
    printf ("\t\tWorst : %ld\n", quick_unsorted);
    printf ("\tMerge Sort:\n");
    printf ("\t\tRandom : %ld\n", merge_random);
    printf ("\t\tBest : %ld\n", merge_sorted);
    printf ("\t\tWorst : %ld\n", merge_unsorted);

    fclose(f);

}
