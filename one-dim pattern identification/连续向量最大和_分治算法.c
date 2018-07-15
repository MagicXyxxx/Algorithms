/*
	连续向量最大和_分治算法.c 
*/
#include <stdio.h>
#define MAX(X,Y) ((X)>(Y)?(X):(Y))
#define N 10

int arr[N] = {3,-4,2,5,-5,5,9,-9,-2,8};

float maxsum3(int l,int u);
float max(float f1,float f2,float f3);

int main (void)
{
	float ans = maxsum3(0,N-1);
	printf("%f",ans);
	
	return 0;
}

float maxsum3(int l,int u)
{
	if(l>u)
		return 0;
	if(l == u)
		return MAX(0,arr[l]);
	int m = (l+u)/2;
	
	int lmax = 0,sum = 0;
	for(int i = m;i>=l;i--)
	{
		sum += arr[i];
		lmax = MAX(lmax,sum);
	}
	int rmax = 0;
	sum = 0;
	for(int i = m+1;i<=u;i++)
	{
		sum += arr[i];
		rmax = MAX(rmax,sum);
	}
	
	return max((float)lmax+rmax,maxsum3(l,m),maxsum3(m+1,u));
}

float max(float f1,float f2,float f3)
{
	if(f1 >= f2 && f1 >= f3)
		return f1;
	if(f2 >= f1 && f2 >= f3)
		return f2;
	if(f3 >= f2 && f3 >= f1)
		return f3;
}
