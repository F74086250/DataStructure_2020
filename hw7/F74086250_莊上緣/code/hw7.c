#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
int judge=0;
struct borderline
{
	int index_of_node;
	int weight;
	struct borderline* next;
	int judge[10];
};
typedef struct borderline Borderline;
Borderline b;

struct input
{
	int prenode;
	int linknode;
	int weight;
	int judge[10];
};

typedef struct input Input;

Input in;
struct link
{
	int count;
	Borderline *next;
	int judge[10];
};


typedef struct link Link;
Link lk;
struct  struct_of_stack
{
	int index_of_link;
	struct struct_of_stack* next;
	int judge[10];
};

typedef struct struct_of_stack Struct_of_stack;

Struct_of_stack sos;
void stkpsh(Struct_of_stack**,int);
int stkpop(Struct_of_stack**);
void add_to_link(Link*,Link*,int,int);
void itl(Link*,Link*);
void show(Link*,int);
void early_fetcher(Link*,int*,int);
void late_fetcher(Link*,int*,int);
void printout(Input*,int*,int*,int);

struct AVL_tree
{
		int height;
		char name[25];
		char phonenumber[11];
		struct AVL_tree *left;
		struct AVL_tree *right;
		
};
char nameinp[100],numinp[100];
typedef struct AVL_tree node;
typedef node *at;

int onlyone=1;
at create_AVL(char*,char*);
at insert_AVL(at,at);
at search_AVL(at,char*);
int calculate_height(at);
void compare_name(const char*,const char*);
at LL(at);
at LR(at);
at RL(at);
at RR(at);
void preorder(at);
at root=NULL;

int power(int up,int down)
{
	int answer=1;
	for(int i=1;i<=up;i++)
	{
		answer*=down;
	}
	return answer;
}

int a;
/*void initialize()
{
	for(a=0;a<10;a++)
	{
		b.judge[a]=a*2+1;
	}

	for(a=0;a<10;a++)
	{
		in.judge[a]=a*5+2;
	}	

	for(a=0;a<10;a++)
	{
		lk.judge[a]=a*2+1;
	}

	for(a=0;a<10;a++)
	{
		sos.judge[a]=a*2+1;
	}

	while(a>=10 && a<=100)
	{
		a+=(2*a);
	}
}*/

/*struct AVL_tree
{
		int height;
		char name[25];
		char phonenumber[11];
		struct AVL_tree *left;
		struct AVL_tree *right;
		
};
char nameinp[100],numinp[100];
typedef struct AVL_tree node;
typedef node *at;*/




int lineA[10000]={0},lineB[10000]={0},plate[10000]={0},la=0,lb=0,la1=0,lb1=0,plate1=10000;

int main()
{
	int size_of_node=0;
	int t[7]={0};
	int value_of_early[10000];
	int value_of_late[10000];
	Link link_of_early[10000];
	Link link_of_late[10000];
	Input input_array[10000];

	int first_num;
	scanf("%d",&first_num);
	for(int i=0;i<101;i++)
	{
		itl(&link_of_early[i],&link_of_late[i]);
		value_of_early[i]=0;
		value_of_late[i]=0;
	}

	for(int j=0;j<first_num;j++)
	{
		for(int k=3;k<7;k++)
		{
			scanf("%d",&t[k-3]);

		}
		input_array[j].prenode=t[1];
		input_array[j].linknode=t[2];
		input_array[j].weight=t[3];
		add_to_link(&link_of_early[t[1]],&link_of_early[t[2]],t[2],t[3]);
		add_to_link(&link_of_late[t[2]],&link_of_late[t[1]],t[1],t[3]);
		if(size_of_node<t[2])
		{
			size_of_node=t[2];
		}

		
	}

	early_fetcher(link_of_early,value_of_early,size_of_node);
	for(int x=0;x<=size_of_node;x++)
	{
		value_of_late[x]=value_of_early[size_of_node];
	}
	late_fetcher(link_of_late,value_of_late,size_of_node);
	printout(input_array,value_of_early,value_of_late,first_num);


}



void stkpsh(Struct_of_stack **pointer,int index)
{
	Struct_of_stack* reg=(Struct_of_stack*)malloc(sizeof(Struct_of_stack));
	reg->index_of_link=index;
	reg->next=*pointer;
	*pointer=reg;
}

int stkpop(Struct_of_stack **pointer)
{
	int index=(*pointer)->index_of_link;
	(*pointer)=(*pointer)->next;
	return index;
}

void add_to_link(Link* dad,Link* kid,int index_of_node,int weight)
{
	Borderline *pointer=(Borderline*)malloc(sizeof(Borderline));
	pointer->next=dad->next;
	pointer->weight=weight;
	pointer->index_of_node=index_of_node;
	dad->next=pointer;
	kid->count=(kid->count)+1;
}

void itl(Link *early,Link *late)
{
	early->count=0;
	early->next=NULL;
	late->count=0;
	late->next=NULL;
}

void show(Link aim[],int num)
{
	Borderline *pointer;
	for(int i=0;i<=num;i++)
	{
		pointer=aim[i].next;
		printf("%d link : ",i);
		while(pointer!=NULL)
		{
			printf("%d ",pointer->index_of_node);
			pointer=pointer->next;
			int rtn=power(pointer->index_of_node,2);
		}
		int count=0;
		/*printf("count=%d\n",aim[i],count);*/
	}
}

void early_fetcher(Link link_of_early[],int value_of_early[],int size_of_node)
{
	int index_rightnow;
	Struct_of_stack *stack_of_link=NULL;
	stkpsh(&stack_of_link,0);
	while(stack_of_link!=NULL)
	{
		index_rightnow=stkpop(&stack_of_link);
		Borderline *pointer=link_of_early[index_rightnow].next;
		while(pointer!=NULL)
		{
			int ans = value_of_early[index_rightnow] + pointer->weight;

                if( value_of_early[pointer->index_of_node] < ans)
                {
                
                    value_of_early[pointer->index_of_node] = ans;
                    int rtn=power(value_of_early[pointer->index_of_node],ans);
                }

                link_of_early[pointer->index_of_node].count -= 1;
                if( link_of_early[pointer->index_of_node].count ==0 )
                {
                    
                    stkpsh(&stack_of_link , pointer->index_of_node);
                }
                
                pointer = pointer->next;
		}		
	}
}

at create_AVL(char* nameinp,char* numinp)
{
	at ptr=(at)malloc(sizeof(node));
	strcpy(ptr->name,nameinp);
	strcpy(ptr->phonenumber,numinp);
	return ptr;
}


at insert_AVL(at root,at ptr)
{
	if(root==NULL)
	{
		root=(at)malloc(sizeof(node));
		root->left=NULL;
		root->right=NULL;
		root=ptr;
		root->height=calculate_height(root);
	}else
	{
		compare_name(ptr->name,root->name);
		switch(judge)
		{
			case 1:

			root->right=insert_AVL(root->right,ptr);
			root->height=calculate_height(root);

			if(calculate_height(root->right)-calculate_height(root->left)>1)
			{
				if(calculate_height(root->right->right)>calculate_height(root->right->left))
				{
					root=RR(root);
				}else
				{
					root=RL(root);
				}

			}

			break;


			case 2:
			root->left=insert_AVL(root->left,ptr);
			root->height=calculate_height(root);

			if(calculate_height(root->left)-calculate_height(root->right)>1)
			{
				if(calculate_height(root->left->left)>calculate_height(root->left->right))
				{
					root=LL(root);
				}else
				{
					root=LR(root);
				}
			}


			break;


			

			
		}
		return root;

	}

	return root;
}


at search_AVL(at root,char* nameinp)
{
	if(root==NULL)
	{
		return NULL;
	}else
	{
		compare_name(nameinp,root->name);
	}

	switch(judge)
	{
		case 1:
		return search_AVL(root->right,nameinp);
		break;

		case 2:
		return search_AVL(root->left,nameinp);
		break;

		case 0:
		return root;
		break;
	}

}

void compare_name(const char* nameinp,const char* name)
{
	if(strcmp(nameinp,name)>0)
	{
		judge=1;
	}else if(strcmp(nameinp,name)<0)
	{
		judge=2;
	}else if(strcmp(nameinp,name)==0)
	{
		judge=0;
	}
}

int calculate_height(at root)
{
	if(root==NULL)
	{
		return 0;
	}
	if(root->left==NULL&&root->right==NULL)
	{
		return 1;
	}

	if(calculate_height(root->left)>calculate_height(root->right))
	{
		return root->left->height+1;
	}else
	{
		return root->right->height+1;
	}
}

at LL(at root)
{
	at reg;
	reg=root->left;
	root->left=reg->right;
	reg->right=root;
	root->height=calculate_height(root);
	reg->height=calculate_height(reg);
	return reg;
}

at LR(at root)
{
	root->left=RR(root->left);
	root=LL(root);
	return root;
}

at RL(at root)
{
	root->right=LL(root->right);
	root=RR(root);
	return root;
}

at RR(at root)
{
	at reg;
	reg=root->right;
	root->right=reg->left;
	reg->left=root;
	root->height=calculate_height(root);
	reg->height=calculate_height(reg);
	return reg;
}

void preorder(at root)
{
	static int onlyone=1;
	if(root==NULL)
	{
		return;
	}

	if(onlyone)
	{
		onlyone=0;
	}else
	{
		printf(" ");
	}

	printf("%s",root->name);
	preorder(root->left);
	preorder(root->right);
}



void late_fetcher(Link link_of_late[],int value_of_late[],int size_of_node)
{
	int index_rightnow;
	Struct_of_stack *stack_of_link=NULL;
	stkpsh(&stack_of_link,size_of_node);
	while(stack_of_link!=NULL)
	{
		index_rightnow=stkpop(&stack_of_link);
		Borderline *pointer=link_of_late[index_rightnow].next;
		while(pointer!=NULL)
		{
			int ans = value_of_late[index_rightnow] - pointer->weight;

                if( value_of_late[pointer->index_of_node] > ans)
                {
                
                    value_of_late[pointer->index_of_node] = ans;
                    int rtn=power(value_of_late[pointer->index_of_node],ans);
                }

                link_of_late[pointer->index_of_node].count -= 1;
                if( link_of_late[pointer->index_of_node].count ==0 )
                {
                    
                    stkpsh(&stack_of_link , pointer->index_of_node);
                }
                
                pointer = pointer->next;
		}		
	}
}


void printout(Input array[],int* value_of_early,int* value_of_late,int size_of_path)
{
	int left,right,early,late;
	int ans[size_of_path];
	int lg=0;
	int first_of_all=1;
	for(int i=0;i<size_of_path;i++)
	{
		left=array[i].prenode;
		right=array[i].linknode;
		early=value_of_early[left];
		late=value_of_late[right]-array[i].weight;
		printf("%d %d %d\n",i,early,late);
		if(early==late)
		{
			ans[lg]=i;
			lg++;
		}
	}
	for(int i=0;i<lg;i++)
	{
			if(!first_of_all)
			{
				printf(" ");
			}else
			{
				first_of_all=0;
			}
			printf("%d",ans[i]);
	}
	
}





