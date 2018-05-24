/*
	163_union_1_git.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

typedef union str{
	short element[2];
	char ele_ch[4];
}Bits;

typedef struct bitLoca{
	int n_arr;
	int n_ch;
	int n_bit;
}bitLoca;

int arr2n[8]={1,2,4,8,16,32,64,128};

/*		�鿴��λ�Ƿ�Ϊ0		*
*		���룺һ������n		*
*		���أ�bit[n]��ֵ	*/
bool bitValue(int num,Bits arr[],bitLoca *bitL)
{	
	if(num!=0)
	{
		int arr_n = num/(32);
		int arr_b = num-arr_n*32;
		short arr_ch = 0;	//�ڵڼ���char�� 
		if(arr_b)
		{
			arr_ch = arr_b/8;
		}
		
		int arr_c_b = arr_b;
		while(arr_c_b>=8)
		{
			arr_c_b -= 8;
		}
		
		bitL->n_arr = arr_n;
		bitL->n_ch = arr_ch;
		bitL->n_bit = arr_c_b;
		
		return (arr[arr_n].ele_ch[arr_ch] & arr2n[arr_c_b]);
	}
	else	//����0 
	{
		bitL->n_arr = 0;
		bitL->n_ch = 0;
		bitL->n_bit = 0;
		return (arr[num].ele_ch[0] & arr2n[0]); 
	}

}

/*		��ĳλ��Ϊn						*
*		���룺һ������n����ĵ�ַ		*
*		���������õ�ַ�ϵ�ֵ��Ϊ1		*/
void setBitValue(Bits arr[],bitLoca *bitL)
{
	arr[bitL->n_arr].ele_ch[bitL->n_ch] = arr[bitL->n_arr].ele_ch[bitL->n_ch] | arr2n[bitL->n_bit];
}

int main (void)
{
	int n = 0;
	printf("Please input range:\n");
	scanf("%d",&n); 
	const int N = n/32+1;
	Bits arr[N];
	memset(arr,0,sizeof(arr));
	
	int k = 0;
	printf("Please input number to show:\n");
	scanf("%d",&k);		//k������ 
	int key = k;
	
	srand(time(NULL));
	
	while(key)
	{
		bitLoca bitL;
		int value = rand()%n;
		if(bitValue(value,arr,&bitL)==0)
		{
			setBitValue(arr,&bitL);
			printf("%d ",value);
			key--;
		}
	}
		
	return 0;
}
