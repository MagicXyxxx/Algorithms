/*
	连续向量最大和_动态规划.c
*/
#include <stdio.h>
#define MAX(X,Y) ((X)>(Y)?(X):(Y))
#define N 11

int main (void)
{
	int arr[N] = {0,3,-4,2,5,-5,5,9,-9,-2,8};
	int sum[N] = {0};
	sum[1] = 3;
	int max = sum[1];
	
	for(int i = 1;i<N;i++)
		sum[i] = sum[i-1]+arr[i];
//	for(int i = 0;i<N;i++)
//		printf("%d ",sum[i]);
	
	for(int i = N-1;i>=0;i--)
		for(int j = i;j>=0;j--)
		{
			int sum1 = sum[i] - sum[j];
			max = MAX(max,sum1);
		}
	
	printf("\n%d",max);
	
	return 0;	
}
