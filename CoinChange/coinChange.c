/*
	换零钱问题
	硬币面额 arr[5] = {33,24,12,5,1}
	零钱总数 N 36
	方法：动态规划 
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#define N 36

int arr[5] = {33,24,12,5,1};
int arr_val[N+1] = {0,1};

int min(int n1,...)
{
	int min_val = N+1;
	va_list argptr;
	va_start(argptr,n1);
	for (int i = 0; i < 4; ++i )
    {
    	int temp = va_arg(argptr,int);
    	if(temp<0)
    		continue;
		if(temp<min_val)
    		min_val = temp;
	}
	va_end(argptr);
	return min_val;
}

int getVal(int n,int i)
{
	int result = 0;
	if(n<0 || n>=i)
		result = -1;
	else if(n == 0)
		result = 0;
	else
		result = arr_val[n];
	return result;
}

int f(int n)
{
	
	for(int i = 2;i<=n;i++)
	{
		int min_t = min(getVal(i-arr[0],i),getVal(i-arr[1],i),getVal(i-arr[2],i),getVal(i-arr[3],i),getVal(i-arr[4],i));
		arr_val[i] = 1+ min_t;
//		printf("arr_val[%d] = %d\n",i,arr_val[i]);
	}
	return arr_val[n];
}

int main (void)
{
	int n = N;

	printf("%d",f(N));
	
	return 0;
}
