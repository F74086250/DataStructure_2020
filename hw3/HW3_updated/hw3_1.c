#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int judge,count=0,total=0;
int checka=0,checkb=0;
int power(int,int);
struct Plate
{
	int index;
	struct Plate *next;
};

typedef struct Plate Stack_Plate;
typedef Stack_Plate *Linked_Stack;
Linked_Stack top=NULL;
int PlateisEmpty()
{
	if(top==NULL) return 1;
	else return 0;
}

void Platepush(int index)
{
	Linked_Stack new_add_plate;
	new_add_plate=(Linked_Stack)malloc(sizeof(Stack_Plate));
	new_add_plate->index=index;
	new_add_plate->next=top;
	top=new_add_plate;

}

int Platepop()
{
	Linked_Stack ptr;
	int temp;
	if(PlateisEmpty())
	{	
		printf("platestack is empty\n");
		return -1;
	}else
	{
		ptr=top;
		top=top->next;
		temp=ptr->index;
		
		free(ptr);
		
		return temp;
	}
}

struct lineA
{
	int anum;
	struct lineA *anext;
};

typedef struct lineA A_data;
A_data *afront=NULL;
A_data *arear=NULL;

int Aenqueue(int anum)
{
	A_data *anew_data;
	anew_data=(A_data*)malloc(sizeof(A_data));
	anew_data->anum=anum;

	if(arear==NULL)
	{
		afront=anew_data;
	}else
	{
		arear->anext=anew_data;
	}
	arear=anew_data;
	anew_data->anext=NULL;
	printf("Anum=%d\n",anew_data->anum);
}


int Adequeue()
{
	A_data *afreeme;
	if(afront==NULL)
	{
		//printf("A is NULL\n");
		
	}else
	{
		//printf("%d\n",afront->anum);
		afreeme=afront;
		afront=afront->anext;
		free(afreeme);
	}	
}



struct lineB
{
	int bnum;
	struct lineB *bnext;
};

typedef struct lineB B_data;
B_data *bfront=NULL;
B_data *brear=NULL;

int Benqueue(int bnum)
{
	B_data *bnew_data;
	bnew_data=(B_data*)malloc(sizeof(B_data));
	bnew_data->bnum=bnum;

	if(brear==NULL)
	{
		bfront=bnew_data;
	}else
	{
		brear->bnext=bnew_data;
	}
	brear=bnew_data;
	bnew_data->bnext=NULL;
	printf("Bnum=%d\n",bnew_data->bnum);
}


int Bdequeue()
{
	B_data *bfreeme;
	if(bfront==NULL)
	{
		//printf("B is NULL\n");
		
	}else
	{
		//printf("%d\n",bfront->bnum);
		bfreeme=bfront;
		bfront=bfront->bnext;
		free(bfreeme);
	}	
}

int power(int a,int b)
{
	int ans=1;
	if(b<1)
	{
		return ans;
	}else
	{
		for(int i=1;i<=b;i++)
		{
			ans*=a;
		}
		return ans;

	}
	
}
int Ashow()
{
	A_data *aptr;
	aptr=afront;
	if(aptr==NULL)
	{
		printf("Aqueue is empty\n");
	}else
	{
		printf("afront->arear:");
		while(aptr!=NULL)
		{
			printf("%d ",aptr->anum);

			aptr=aptr->anext;
		}
		printf("\n");
	}
}

int Bshow()
{
	B_data *bptr;
	bptr=bfront;
	if(bptr==NULL)
	{
		printf("Bqueue is empty\n");
	}else
	{
		printf("bfront->brear:");
		while(bptr!=NULL)
		{
			printf("%d ",bptr->bnum);
			bptr=bptr->bnext;
		}
		printf("\n");
	}
}


int main(int argc,char** argv)
{

	
	char inp[10000];
	while(scanf("%s",inp)!=EOF)
	{
		char ch='\r';
		char *ret;
		if(ret=strchr(inp,ch))
		{
			*ret='\n';
		    *(ret+1)='\0';

		}
		
		
	
		if(inp[0]=='P'&&inp[1]=='O')
		{
			
			continue;
		}else if(inp[0]=='P'&&inp[1]=='U')
		{	
			judge=1;
			count=0;
			total=0;
			continue;
			
			
		}else if(inp[0]=='E')
		{
			judge=2;
			continue;
			
		}else if(inp[0]=='D')
		{
			judge=3;
			continue;
			
		}else
		{
			switch(judge)
			{
				case 1:
				
				
					
					while(inp[count]!='\0')
					{

						count++;
					}
					
					for(int i=(count-1),j=0;i>=0;i--,j++)
					{
						total+=((inp[i]-'0')*power(10,j));

					
					}
					
					Platepush(total);
					
			
					break;
				case 2:
			
					if(inp[0]=='A')
					{
						
					
						Aenqueue(Platepop());
						printf("EQA:");
						Ashow();
				
						

					}else if(inp[0]=='B')
					{
						
				
						Benqueue(Platepop());
						printf("EQB:");
						Bshow();
					}

					break;
				case 3:

					if (inp[0]=='A')
					{
						Adequeue();
						printf("DQA:");
						Ashow();
						
					}else if(inp[0]=='B')
					{
						Bdequeue();
						printf("DQB:");
						Bshow();
					}
					break;
			}
		} 
	}


	return 0;

}

