#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    int n;
    printf("How many numbers? ");
    scanf("%d",&n);
    FILE * f;
    f = fopen("numbers_list","w+");
    srand(time(NULL));
    for (int i=0; i<n; i++)
        fprintf(f, "%d\n", rand());
    fclose(f);
    return 0;
}
