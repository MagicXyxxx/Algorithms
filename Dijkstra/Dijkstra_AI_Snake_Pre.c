/*
	dijkstra_plus_with_wall_setjmp.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <setjmp.h>
#define N 5
#define WALL_CNT 3
#define MIN(X,Y) ((X<Y)?(X):(Y))

typedef struct loca{
	int x;
	int y;
}Local;

typedef struct unit{
	int value;
	Local local;
	struct unit *pre;
}Unit;

typedef struct queue{
	int head,tail;
	Local queue[N*N];
}Queue;

jmp_buf jump_buffer;
Unit mapUnit[N][N];
Queue que;
//			方向，	上	 	下 		左 	右 
int direct[4][2] = {{0,-1},{0,1},{-1,0},{1,0}};
Local Wall[WALL_CNT];

void push(int x,int y)
{
	que.tail++;
	que.queue[que.tail].x = x;
	que.queue[que.tail].y = y;
}
void pop()
{
	que.head++;
}

void Pos(int x, int y)  
{
    COORD pos;  
    HANDLE hOutput;  
    pos.X = x;  
    pos.Y = y;  
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);  
    SetConsoleCursorPosition(hOutput, pos);  
}

void InitializeMapUnit()
{
	que.head = 0;
	que.tail = -1;

	for(int i = 0;i<N;i++)
		for(int j = 0;j<N;j++)
		{
			mapUnit[i][j].local.x = i;
			mapUnit[i][j].local.y = j;
			mapUnit[i][j].pre = NULL;
			mapUnit[i][j].value = N*N; 
		}
}

void setOrigin(int x,int y)
{
	mapUnit[x][y].value = 0;
	push(x,y);
}

void setWall(void)
{
	Wall[0].x = 1;
	Wall[0].y = 1;
	
	Wall[1].x = 2;
	Wall[1].y = 1;
	
	Wall[2].x = 3;
	Wall[2].y = 1;
}

bool stepRight(int x,int y)
{
//	out of map
	if(x >= N || y >= N ||
		x < 0 || y < 0)
		return false;
	for(int i = 0;i<WALL_CNT;i++)
		if(Wall[i].x == x && Wall[i].y == y)
			return false;
	
	return true;
}
void bfs(int end_x,int end_y)
{
	if(que.tail>N*N || que.head>que.tail)
		return;
	
	int head = que.head;
	int tail = que.tail;
	//当前队列
	for(int i = head;i<=tail;i++)
	{
		int base_x = que.queue[i].x;
		int base_y = que.queue[i].y;
		
		//	四个方向 
		for(int j = 0;j<4;j++)
		{
			int new_x = base_x + direct[j][0];
			int new_y = base_y + direct[j][1];
			//溢出 
			if(new_x >= N || new_y >= N ||
				 new_x < 0 || new_y < 0)
				continue;
			if(stepRight(new_x,new_y) == false)
				continue;
			//新结点为 N*N
			if(mapUnit[new_x][new_y].value == N*N)
			{
				mapUnit[new_x][new_y].value = mapUnit[base_x][base_y].value +1;
				mapUnit[new_x][new_y].pre = &mapUnit[base_x][base_y];
				push(new_x,new_y);
			}
			else	//取小值 
			{
				mapUnit[new_x][new_y].value = MIN(mapUnit[new_x][new_y].value,mapUnit[base_x][base_y].value +1);
				if(mapUnit[new_x][new_y].value != mapUnit[new_x][new_y].value)
					mapUnit[new_x][new_y].pre = &mapUnit[base_x][base_y];
			}
			if(new_x == end_x && new_y == end_y)
			{
				longjmp(jump_buffer, 1);
			}
		}
	}
	for(int i = head;i<=tail;i++)
		pop();
	bfs(end_x,end_y);
}

void getStepNext(int x,int y)
{
	Unit *scan = &mapUnit[x][y];
	if(scan->pre!= NULL)
	{
		int x = scan->local.x;
		int y = scan->local.y;
		scan = scan->pre;
		getStepNext(scan->local.x,scan->local.y);
		printf(" -> ");
	}
	printf("(%d,%d)",x,y);
}

void getStep(int x,int y,int orgin_x,int orgin_y)
{
	Unit *scan = &mapUnit[x][y];
	Pos(0,10);
	
	if(scan->pre == NULL)
	{
		printf("NO Path To Point (%d,%d) From Point (%d,%d)!\n",x,y,orgin_x,orgin_y);
	}
	else
	{
		getStepNext(x,y);
	}
}

void printMapValue()
{
	for(int i = 0;i<N;i++)
	{
		for(int j = 0;j<N;j++)
		{
			printf("\t%d\t",mapUnit[j][i].value);
		}
		printf("\n");
	}
}

int main (void)
{
	int orgin_x = N/2;
	int orgin_y = N/2;
	int finishing_x = 1;
	int finishing_y = 4;
	
	InitializeMapUnit();
	
	setOrigin(orgin_x,orgin_y);
	setWall();
	
	if(setjmp(jump_buffer) == 0)
		bfs(finishing_x,finishing_y);
	
	printMapValue();
	getStep(finishing_x,finishing_y,orgin_x,orgin_y);
	
	return 0;
}
