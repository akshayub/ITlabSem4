// To generate Ham data
// To verify Hammed data

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int getNum(char x){
    if (x == '0')   return 0;
    else            return 1;
}

char getChar(int x){
    if (x == 0) return '0';
    else        return '1';
}

void swap (char *x, char *y){
    char temp = *x;
    *x = *y;
    *y = temp;
}

void rev (char *s, int len){
    for (int i=0; i<len/2; i++)
        swap(&s[i], &s[len-1-i]);
}

int check(int num){
    // int i=1, j=1;
    // while (1){
    //     if (num == i)   return 1;
    //     else if (i > num)   return 0;
    //     else{
    //         i = pow(2,j);
    //         j++;
    //     }
    // }
    if (num == 1) return 1;
    while (num > 0){
        if (num == 2)   return 1;
        if (num%2 == 1) return 0;
        num /= 2;
    }
    return 1;
}

void setup(char *newData, char *data, int len, int r){
    int k = 0;
    newData[0] = ' ';
    rev(data, len);
    // for (int i=1, j=0; i < len+r+1; i++){
    for (int i=1, j=0; k <= r; i++){
        if (check(i)){
            k++;
            newData[i] = 'a';
        }
        else{
            newData[i] = data[j++];
        }
    }
    // rev(newData, strlen(newData));
}

void finalize(char *data, int dataLen, int r){
    int len = dataLen + r + 1;
    int i,j;
    for(i=0; i<r; i++){
        j = (int)pow(2,i);
        int bit = 0;
        for(int k=1; k < len; k++){
            if (k > j && (k/j)%2){
                bit ^= getNum(data[k]);
            }
        }
        data[j] = getChar(bit);
    }
    rev(data, len);
}

char *ham (char *data, int len){
    int redundantBits = 0;
    for (int i = 0; len+i+1 >= (int)pow(2,i); i++)
        redundantBits = i+1;

    char *result = calloc( len + redundantBits + 1, sizeof(char));
    setup(result, data, len, redundantBits);
    finalize(result, len, redundantBits);
    return result;
}

int verify(char *data, int len){
    rev(data, len);
    int error = 0;
    for(int j=1; j < len; j*=2){
        int bit = 0;
        for(int i=1; i<len; i++){
            if((i/j)%2){
                bit ^= getNum(data[i]);
            }
        }
        if (bit == 1)
            error += j;
    }
    return error;
}

int main (int argc, char const *argv[]) {

    int len = strlen(argv[1]);
    char *data = calloc(len, sizeof(char));
    memmove(data, argv[1], len);

    char *ans = ham(data, len);
    puts("Hammed Code");
    puts(ans);
    // ans[6] = '0';   // To Generate a single error at some place
    int error = verify(ans, strlen(ans));
    if (!error)
        puts("No error. Success.");
    else
        printf("Error detected at position %d\n", error);


    free(ans);
    free(data);
    return 0;
}
