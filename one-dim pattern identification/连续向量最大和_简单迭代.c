/*
	连续子向量最大和_简单迭代.c
*/
#include <stdio.h>
#define MAX(X,Y) ((X)>(Y)?(X):(Y))
#define N 10

int main (void)
{
	int arr[N] = {3,-4,2,5,-5,5,9,-9,-2,8};
	
	int max = 0;
	
	for(int i = 0;i<N;i++)
	{
		int sum = 0;
		for(int j = i;j<N;j++)
		{
			sum += arr[j];
			max = MAX(sum,max);
		}
	}
	printf("%d",max);
	
	return 0;
}
