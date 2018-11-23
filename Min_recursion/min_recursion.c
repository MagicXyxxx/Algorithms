/*
	min_recursion.c 
*/
#include <stdio.h>
#define N 10
#define MIN(X,Y) ((X<Y)?(X):(Y))

int f(int arr[],int len,int n)
{
	if(n == len-1)
		return arr[n];
	
	int min = f(arr,len,n+1);
//	return arr[n]<min?arr[n]:min;
	
	return MIN(min,arr[n]);
	
//	return arr[n]<f(arr,len,n+1)?arr[n]:f(arr,len,n+1);
}

int main (void)
{
	int arr[N] = {2,4,1,3,5,6,7,8,-11};
	
	int min = f(arr,N,0);
	printf("%d ",min);
	
	return 0;
}
