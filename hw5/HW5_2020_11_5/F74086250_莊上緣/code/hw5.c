#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int TABLE_SIZE;
#define PRIME 7
int num[100000]={0};
int count=0;

int main(int argc,char** argv)
{
	char inp[10];
	while(scanf("%s",inp)!=EOF)
	{
		num[count++]=atoi(inp);
		
	}
	//printf("count=%d\n",count);
	/*for(int j=0;j<count;j++)
	{
		printf("%d\n",num[j]);
	}*/
	TABLE_SIZE=count;
	int *ans=(int*)malloc(count*sizeof(int));
	int *check=(int*)malloc(count*sizeof(int));
	for(int l=0;l<count;l++)
	{
		check[l]=0;
	}
	for(int k=0;k<count;k++)
	{
		int i=0;
		if(check[((num[k]%TABLE_SIZE)+(i*(PRIME-(num[k]%PRIME))))%TABLE_SIZE]==0)
		{
			ans[((num[k]%TABLE_SIZE)+(i*(PRIME-(num[k]%PRIME))))%TABLE_SIZE]=num[k];
			check[((num[k]%TABLE_SIZE)+(i*(PRIME-(num[k]%PRIME))))%TABLE_SIZE]=1;
		}else if(check[((num[k]%TABLE_SIZE)+(i*(PRIME-(num[k]%PRIME))))%TABLE_SIZE]==1)
  		{
  			do
  			{
  				i++;
  			}while(check[((num[k]%TABLE_SIZE)+(i*(PRIME-(num[k]%PRIME))))%TABLE_SIZE]==1);
  			ans[((num[k]%TABLE_SIZE)+(i*(PRIME-(num[k]%PRIME))))%TABLE_SIZE]=num[k];
  			check[((num[k]%TABLE_SIZE)+(i*(PRIME-(num[k]%PRIME))))%TABLE_SIZE]=1;
  		}	

	}
	for(int i=0;i<count;i++)
	{
		printf("%d->%d",i,ans[i]);
		if(i<(count-1))
		{
			printf("\n");
		}
	}

	return 0;
}
