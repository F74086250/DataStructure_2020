#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int mover=13,count=0;
struct Poker
{
	int num;
	struct Poker *next;
};
typedef struct Poker poker_data;
poker_data *pokerfront=NULL;
poker_data *pokerrear=NULL;
poker_data *pokerptr;
int enqueue(int num)
{
	poker_data *pokernew_data;
	pokernew_data=(poker_data*)malloc(sizeof(poker_data));
	pokernew_data->num=num;

	if(pokerfront==NULL)
	{
		pokerfront=pokernew_data;
	}else
	{
		pokerrear->next=pokernew_data;
	}
	pokerrear=pokernew_data;
	pokernew_data->next=NULL;
	//printf("%d ",pokernew_data->num);

	
}


int dequeue()
{
	poker_data *pokerfreeme;
	
	
		
		pokerfreeme=pokerfront;
		pokerfront=pokerfront->next;
		free(pokerfreeme);
		
}

int show()
{
	poker_data *ptr;
	ptr=pokerfront;
	while(ptr!=NULL)
	{
		if((ptr->num)==1)
		{
			printf("A");
		}else if((ptr->num)==11)
		{
			printf("J");
		}else if((ptr->num)==12)
		{
			printf("Q");
		}else if((ptr->num)==13)
		{
			printf("K");
		}else printf("%d",ptr->num);
		printf(" ");
		ptr=ptr->next;
	}
	printf("\n");
}
int check(int num,int mover)
{
	if(num==mover) return 1;
	else return 0;
}
int main(int argc,char** argv)
{

	
	char inp[10000];
	while(scanf("%s",inp)!=EOF)
	{	
		count=0;
		
		int receive;

		char che='\r';
		char *ret;
		if(ret=strchr(inp,che))
		{
			*ret='\n';
		    *(ret+1)='\0';

		}
		

		if(inp[0]!='1')
		{
			count=1;
		}else count=2;
		//printf("count=%d\n",count);
		if(count==1)
		{
			if((inp[0]>='2')&&(inp[0]<='9'))
			{
				receive=inp[0]-'0';
			}else if(inp[0]=='A')
			{
				receive=1;
			}else if(inp[0]=='J')
			{
				receive=11;
			}else if(inp[0]=='Q')
			{
				receive=12;
			}else if(inp[0]=='K')
			{
				receive=13;
			}
		}else if(count==2)
		{
			receive=10;
		}

		//printf("%d\n",receive);

		enqueue(receive);
		
	}
	show();
	while(mover>=1)
	{
		pokerptr=pokerfront;
		if(check((pokerptr->num),mover))
		{
			dequeue();
			mover--;

		}else
		{
			enqueue(pokerptr->num);
			dequeue();
		}
		show();
	}
	
	return 0;

}