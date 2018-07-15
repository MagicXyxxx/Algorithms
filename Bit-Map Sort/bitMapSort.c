/*
	163_union_1_sort.c
	author:Magic激流
	2018-5-26 
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

/*		查看该位是否为0		*
*		输入：一个整数n		*
*		返回：bit[n]的值	*/
bool bitValue(int num,Bits arr[],bitLoca *bitL)
{	
	if(num!=0)
	{
		int arr_n = num/32;
		int arr_b = num-arr_n*32;
		short arr_ch = 0;	//在第几个char里 
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
	else	//处理0 
	{
		bitL->n_arr = 0;
		bitL->n_ch = 0;
		bitL->n_bit = 0;
		
		return (arr[num].ele_ch[0] & arr2n[0]); 
	}
}

/*		把某位设为n						*
*		输入：一个整数n代表的地址		*
*		操作：将该地址上的值设为1		*/
void setBitValue(Bits arr[],bitLoca *bitL)
{
	arr[bitL->n_arr].ele_ch[bitL->n_ch] = arr[bitL->n_arr].ele_ch[bitL->n_ch] | arr2n[bitL->n_bit];
}

void bitSort(Bits arr[],int n)
{
	int max_arr = n/32;
	int tbit = n-max_arr*32;
	short max_ch = 0;	//在第几个char里 
	if(tbit)
	{
		max_ch = tbit/8;
	}
	int max_bit = tbit%8;

	for(int tarr = 0;tarr<=max_arr;tarr++)
		if(tarr != max_arr)	//全满的数组 
		{
			for(int tch = 0;tch<4;tch++)
				for(int tbit = 0;tbit<8;tbit++)
				{
					if(arr[tarr].ele_ch[tch] & arr2n[tbit])
					{
						printf("%d ",tarr*32+tch*8+tbit);
					}
				}
		}
		else	//非全满的数组 
		{
			for(int tch = 0;tch<=max_ch;tch++)
				if(tch != max_ch)	//全满的ch 
				{
					for(int tbit = 0;tbit<8;tbit++)
					{
						if(arr[tarr].ele_ch[tch] & arr2n[tbit])
						{
							printf("%d ",tarr*32+tch*8+tbit);
						}
					}
				}
				else	//非全满ch 
				{
					for(int tbit = 0;tbit<max_bit;tbit++)
					{
						if(arr[tarr].ele_ch[tch] & arr2n[tbit])
						{
							printf("%d ",tarr*32+tch*8+tbit);
						}
					}
				}
		}
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
	
	printf("Please input count of number,");
	do{
		printf("this number is less than %d\n",n);
		scanf("%d",&k);
	}while(k>n);

	srand(time(NULL));
	
	while(k)
	{
		bitLoca bitL;
		int value = rand()*rand()%n;
//		int value = rand()%n;
		if(bitValue(value,arr,&bitL)==0)
		{
			setBitValue(arr,&bitL);
			printf("%d ",value);
			k--;
		}
	}
	
	printf("\nSort:\n");
	
	bitSort(arr,n);
	
	return 0;
}

