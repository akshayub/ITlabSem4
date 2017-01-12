#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// Remove wait for both demo

// For zombie process demo
// add sleep in parent process and exit in child
// do ps -e and you can see a defunct process

// For orphan process demo
// add sleep in child process

void merge(int a[],int l,int u,int m){
	int i,j;
	//int left[100],right[100];
	int n1,n2;
	n1=m-l+1;
	n2=u-m;
	int left[n1],right[n2];
	for(i=0;i<n1;i++)
		left[i]=a[l+i];
	for(i=0;i<n2;i++)
		right[i]=a[m+1+i];

	int k=l;
	i=0;
	j=0;
	while(i<n1 && j<n2)
	{
		if(left[i]<=right[j])
			a[k++]=left[i++];
		else
			a[k++]=right[j++];
	}
	if(i<n1)
	{	while(i<n1)
			a[k++]=left[i++];
	}
	else if(j<n2)
	{	while(j<n2)
			a[k++]=right[j++];
	}

}

void m_sort(int a[],int l,int u){
	if(l<u)
	{
		int m=(l+u)/2;
		m_sort(a,l,m);
		m_sort(a,m+1,u);
		merge(a,l,u,m);
	}

}

void swap(int *a,int *b){
	int t=*a;
		*a=*b;
		*b=t;
}

int partition(int a[],int l,int u){
	int p=a[l];
	int i=l,j=u+1;
	do
	{
		do
		{
			i++;
		}while(a[i]<p);

		do
		{
			j--;
		}while(a[j]>p);

		swap(&a[i],&a[j]);

	}while(i<j);
	swap(&a[i],&a[j]);
	swap(&a[l],&a[j]);
	return j;
}

void quick(int a[],int l,int u){
	if(l<u)
	{
		int m=partition(a,l,u);
		quick(a,l,m-1);
		quick(a,m+1,u);

	}

}

void main(){
	int n,a[1000],i;

	printf("Enter n:\n");
	scanf("%d",&n);

    printf("Enter numbers to be sorted:\n");
    for(i=0;i<n;i++)
    	scanf("%d",&a[i]);

    pid_t pid = fork();

	if (pid==0){
		printf("Child process created\n");
        // sleep(5);
        printf("Original array:\n");
		for(i=0;i<n;i++)
			printf("%d ",a[i]);

		quick(a,0,n-1);
		printf("Sorted array (child process):\n");
		for(i=0;i<n;i++)
            printf("%d ",a[i]);
		printf("\n");
        // printf("exiting child\n");exit(0);

	}

	else if (pid > 0){
		printf("Parent process created\n");
		wait(0);
        // sleep(10);

        printf("Original array:\n");
		for(i=0;i<n;i++)
            printf("%d ",a[i]);

		m_sort(a,0,n-1);
		printf("Sorted array (parent process):\n");
		for(i=0;i<n;i++)
            printf("%d ",a[i]);
		printf("\n");

	}
}
