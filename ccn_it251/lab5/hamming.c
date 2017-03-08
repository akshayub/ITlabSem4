#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int seq(int x,int h) {
    return (x/h)%2;
}
// Use logarithm.
int power_of_2(int x) {
    if (x == 1) return 1;
    while (x > 0) {
        if (x == 2) return 1;
        if (x%2 == 1) return 0;
        x /= 2;
    }
    return 1;
}

char *hamming(char *input,int len) {
    int in_num[len],i;
    for (i=0; i < len; i++) {
        in_num[len-i-1] = input[i] - '0';
    }
    int red = 0,index=0,j;
    index=0;
    while (pow(2,red) < len+red+1) { red++; }
    int hammed[len+red+1];
    for (i=1; i< len+red+1; i++) {
        if (!power_of_2(i)) {
            hammed[i] = in_num[index++];
        }
        else {
            hammed[i] = 0;
        }
    }
    int k = 1;
    while (k < pow(2,red)+1) {
        int xor = 0;
        for (j=k+1; j < len+red+1; j++) {
            if (seq(j,k)) {
                xor ^= hammed[j];
            }
        }
        hammed[k] = xor;
        k*=2;
    }
    long int res=0;
    char *ans = malloc(sizeof(char) * (len+red+1));
    for (i=len+red;i>0;i--) {
        res = res*10 + hammed[i];
        ans[i] = hammed[i] + '0';
        printf("%c",ans[i]);
    }
    ans[0] = '\0';
    char *answer = malloc(sizeof(char) * (len+red+1));
    for (i=len+red;i>0;i--) {
        answer[i] = ans[len+red-i];
    }
    free(ans);
    return answer;
}

int main(int argc, char const *argv[]) {
    char *input = malloc(sizeof(char) * 100);
    int red = 0;
    printf("Enter the string: ");
    scanf("%s",input);
    int len = strlen(input);
    while (pow(2,red) < len+red+1) { red++; }
    char *answer = hamming(input,len);
    free(input);
    puts(answer);
    free(answer);
    return 0;
}
