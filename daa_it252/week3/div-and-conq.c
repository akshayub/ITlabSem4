#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int MaxSubSum(const int A[], int Left, int Right){
    // the subarray with largest sum on each side corresponding to case 1 and case 2
    int MaxLeftSum, MaxRightSum;
    // the subarray with largest sum across the middle from the left side or to the right side
    // it corresponds to case 3
    int MaxLeftBorderSum, MaxRightBorderSum;
    int LeftBorderSum, RightBorderSum;
    int Center, i;
    if (Left == Right)
        if (A[Left] > 0)
            return A[Left];
        else
            return 0;
    Center = (Left + Right) / 2;
    MaxLeftSum = MaxSubSum(A, Left, Center);
    MaxRightSum = MaxSubSum(A, Center + 1, Right);
    MaxLeftBorderSum = 0;
    LeftBorderSum = 0;
    for (i = Center; i >= Left; i--){
        LeftBorderSum += A[i];
        if (LeftBorderSum > MaxLeftBorderSum)
            MaxLeftBorderSum = LeftBorderSum;
    }
    MaxRightBorderSum = 0;
    RightBorderSum = 0;
    for (i = Center + 1; i <= Right; i++){
        RightBorderSum += A[i];
        if (RightBorderSum > MaxRightBorderSum)
            MaxRightBorderSum = RightBorderSum;
    }
    int max1 = MaxLeftSum > MaxRightSum ? MaxLeftSum : MaxRightSum;
    int max2 = MaxLeftBorderSum + MaxRightBorderSum;
    return max1 > max2 ? max1 : max2;
}

int main(void) {

    FILE * fp = stdin;
    int n = 0;
    int *ar = calloc(1000,sizeof(int));

    while(scanf("%d", &ar[n++]) == 1){}
    n--;

    printf("Max subarray sum is %d\n", MaxSubSum(ar, 0, n));

    return 0;
}
