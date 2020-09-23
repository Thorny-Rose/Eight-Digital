#include<stdio.h>
#define DM 15
#define PATH 20
#define CLOSE 100000
typedef int BOOL;
#define TRUE  1
#define FALSE 0
int a[3][3];
int b[CLOSE][3][3]; //已遍历过的状态 
int c[PATH][3][3]; //路径状态 
int i0,j0;
void DFS(int i0,int j0);
int main()
{
	int i,j;
	int i0=0,j0=1;
	for(i=0;i<3;i++)
	for(j=0;j<3;j++)
			scanf("%d",&a[i][j]); 
	DFS(i0,j0); 
	return 0;
}
void exchange(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void blank_left(int i0,int j0)
{//空格左移 
	exchange(&a[i0][j0-1],&a[i0][j0]);
} 
void blank_right(int i0,int j0)
{//空格右移 
	exchange(&a[i0][j0+1],&a[i0][j0]);
}
void blank_up(int i0,int j0)
{//空格上移 
	exchange(&a[i0-1][j0],&a[i0][j0]);
}
void blank_down(int i0,int j0)
{//空格下移 
	exchange(&a[i0+1][j0],&a[i0][j0]);
}
void show_matrix(int a[3][3])
{//打印矩阵 
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void save_matrix(int b[3][3],int a[3][3])
{//将矩阵保存在三维数组中 
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			b[i][j]=a[i][j];
		}
	}
}
BOOL ComparePath(int num)
{//与已走过的路径比较 
	if(a[0][0]==c[num][0][0]&&
	a[0][1]==c[num][0][1]&&
	a[0][2]==c[num][0][2]&&
	a[1][0]==c[num][1][0]&&
	a[1][1]==c[num][1][1]&&
	a[1][2]==c[num][1][2]&&
	a[2][0]==c[num][2][0]&&
	a[2][1]==c[num][2][1]&&
	a[2][2]==c[num][2][2])
		return TRUE;
	else
		return FALSE;
}
BOOL CompareClose(int num)
{//与close表比较 
	if(a[0][0]==b[num][0][0]&&
	a[0][1]==b[num][0][1]&&
	a[0][2]==b[num][0][2]&&
	a[1][0]==b[num][1][0]&&
	a[1][1]==b[num][1][1]&&
	a[1][2]==b[num][1][2]&&
	a[2][0]==b[num][2][0]&&
	a[2][1]==b[num][2][1]&&
	a[2][2]==b[num][2][2])
		return TRUE;
	else
		return FALSE;
}
BOOL CompareAll(int close,int path)
{//是否与已遍历过的情况重合 
	int i;
	for(i=0;i<path;i++)
	{
		if(ComparePath(i)==TRUE)//在表Path中 
			return TRUE;
	}
	for(i=0;i<close;i++)//在表close中 
	{
		if(CompareClose(i)==TRUE)
			return TRUE;
	}
	return FALSE;
} 
BOOL IsTravel(int f,int close,int path,int i0,int j0)
{//检测移动后的位置是否已被访问过 
	BOOL flag=FALSE;
	if(f==0)
	{
		blank_left(i0,j0);
		if(CompareAll(close,path)==TRUE)
			flag=TRUE;
		blank_right(i0,j0-1);
	}
	else if(f==1)
	{
		blank_up(i0,j0);
		if(CompareAll(close,path)==TRUE)
			flag=TRUE;
		blank_down(i0-1,j0);
	}
	else if(f==2)
	{
		blank_right(i0,j0);
		if(CompareAll(close,path)==TRUE)
			flag=TRUE;
		blank_left(i0,j0+1);
	}
	else if(f==3)
	{
		blank_down(i0,j0);
		if(CompareAll(close,path)==TRUE)
			flag=TRUE;
		blank_up(i0+1,j0);
	}
	return flag;
} 
BOOL FINAL()
{//是否完成任务 
	if(a[0][0]==1&&
	a[0][1]==2&&
	a[0][2]==3&&
	a[1][0]==4&&
	a[1][1]==5&&
	a[1][2]==6&&
	a[2][0]==7&&
	a[2][1]==8&&
	a[2][2]==0)
		return TRUE;
	else
		return FALSE;
}





void DFS(int i0,int j0)
{
	int deep=0;//当前深度 
	int close=0;
	int path=0;
	
	int i;
while(TRUE)
{
	if(j0!=0&&IsTravel(0,close,path,i0,j0)==FALSE&&path<=DM)
	{//优先左移 
		save_matrix(c[path],a);
		path++;
		deep++;
		
		blank_left(i0,j0);
		j0--;
	}
	else if(i0!=0&&IsTravel(1,close,path,i0,j0)==FALSE&&path<=DM)
	{//上移 
		save_matrix(c[path],a);
		path++;
		deep++;
		
		blank_up(i0,j0);
		i0--;
	}
	else if(j0!=2&&IsTravel(2,close,path,i0,j0)==FALSE&&path<=DM)
	{//右移
		save_matrix(c[path],a);
		path++;
		deep++;
		
		blank_right(i0,j0);
		j0++;
	}
	else if(i0!=2&&IsTravel(3,close,path,i0,j0)==FALSE&&path<=DM)
	{//下移 
		save_matrix(c[path],a);
		path++;
		deep++;
		
		blank_down(i0,j0);
		i0++;
	}
	else
	{
		save_matrix(b[close],a);
		close++;//存入close表
		path--;
		save_matrix(a,c[path]);//将a矩阵恢复为上一个节点的值
		int m,n;
		for(m=0;m<3;m++)
		{
			for(n=0;n<3;n++)
				if(a[m][n]==0)
				{
					i0=m;
					j0=n;
				}
		 } 
	}

	if(FINAL()==TRUE)
	{
		printf("FIND!\n");	
		break;
	}
}
	for(i=0;i<path;i++)
	{
		show_matrix(c[i]);
	}
	show_matrix(a);
}

