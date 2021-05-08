#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int judge;
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
int main(int argc,char** argv)
{
	at root=NULL;
	char inp;
	scanf("%c",&inp);
    if(getchar()=='\r')
    {
        getchar();
    }
	while(inp!='E')
	{
		if(inp=='D')
		{
			scanf("%s",nameinp);
			if(nameinp[1]=='\0')
			{
				inp=nameinp[0];
				preorder(root);
			}else
			{
				onlyone=0;
				scanf("%s",numinp);
				if(getchar()=='\r')
				{
					getchar();
				}

				at ptr=create_AVL(nameinp,numinp);
				root=insert_AVL(root,ptr);
			}
		}

		if(inp=='S')
		{
			scanf("%s",nameinp);
			if(nameinp[1]!='\0')
			{
				if(getchar()=='\r')
				{
					getchar();
				}

				at ptr=search_AVL(root,nameinp);
				if(onlyone==1)
				{
					onlyone=0;
				}else
				{
					printf("\n");
				}


				if(ptr==NULL)
				{
					printf("%s null",nameinp);
				}else
				{
					printf("%s %s",nameinp,ptr->phonenumber);
				}
			
		
			}else
			{
				inp=nameinp[0];
			}

		}		

	}
	return 0;
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