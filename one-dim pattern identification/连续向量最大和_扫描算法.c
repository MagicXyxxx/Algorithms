/*
	连续向量最大和_扫描算法.c 
*/
#include <stdio.h>
#define MAX(X,Y) ((X)>(Y)?(X):(Y))
#define N 10

int main (void)
{
	int arr[N] = {3,-4,2,5,-5,5,9,-9,-2,8};
	
	int maxsofar = 0,maxendinghere = 0;
	
	for(int i = 0;i<N;i++)
	{
		maxendinghere = MAX(maxendinghere+arr[i],0);
	printf("%d %d",i,maxendinghere); 
		maxsofar = MAX(maxsofar,maxendinghere);
	printf(" %d\n",maxsofar);
	}
	printf("%d",maxsofar);
	
	return 0;
}
