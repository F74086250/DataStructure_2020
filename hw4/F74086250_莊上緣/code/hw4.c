#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int counttotal=0,countdelete0=0,countdelete=0,count3=1;
int bta[200]={0};
int judge=0,judge1=0;
int case1=0,case2=0,case3=0,case4=0,case5=0,case6=0;
int delete[100]={0};



struct tree
{
	int data;
		struct tree *left;
		struct tree *right;
		struct tree *father;
};

typedef struct tree node;
typedef node *bt;
bt root=NULL;
bt create_tree(bt,int);
void preorder(bt);
bt position(bt,int);
void deletenode(bt);
void preordertest(bt);
int main(int argc,char** argv)
{
	char inp[10];
	while(scanf("%s",inp)!=EOF)
	{
		bta[counttotal]=atoi(inp);
		counttotal++;
		char ch=getchar();
		if(ch=='\r'||ch=='\n')
		{
			while(scanf("%s",inp)!=EOF)
			{
				delete[countdelete0]=atoi(inp);
				countdelete0++;
			}
			break;
		}	
	}
	//printf("%d %d\n",counttotal,countdelete0);


	

	
	


	int* btree=malloc(sizeof(int)*counttotal);
	
	for(int i=0;i<counttotal;i++)
	{
		btree[i]=bta[i];
		
	}


	int *bdelete=malloc(sizeof(int)*countdelete0);
	for(int i=0;i<countdelete0;i++)
	{
		bdelete[i]=delete[i];
		
	}
	



	for(int i=0;i<countdelete0;i++)
	{
		judge1=0;
		for(int j=0;j<counttotal;j++)
		{
			if(bdelete[i]==btree[j])
			{	
				judge1=1;
				countdelete++;
			}

		}
		if(judge1==0)
		{
			bdelete[i]=0;
		}
	}

	


	



	
	
	

	bt ptr=NULL;
	
	

	for(int i=0;i<counttotal;i++)
	{
		ptr=create_tree(ptr,btree[i]);
	}
	
	root=ptr;
	
	//preordertest(ans);
	/*for(int i=0;i<counttotal;i++)
	{
		if(btree[i]!=0)
		{
			printf("%d ",btree[i]);
		}
	}
	printf("\n");

	for(int i=0;i<countdelete0;i++)
	{
		if(bdelete[i]!=0)
		{
			printf("%d ",bdelete[i]);
		}
	}*/
	//printf("%d\n",countdelete0);
	
	for(int i=0;i<countdelete0;i++)
	{
		
		ptr=root;
	//	printf("%d ",bdelete[i]);
		//printf("%d\n",ptr->data);
		if(bdelete[i]!=0)
		{
			ptr=position(ptr,bdelete[i]);
			//printf("%d\n",ptr->data);
			judge=0;
			case5++;
			//printf("case5:%d\n",case5);
			deletenode(ptr);
		}
		
	}
	preorder(root);
	//preordertest(ans);
	/*if(ans->father==NULL)
	{
		printf("1");
	}*/
	return 0;
}







bt create_tree(bt root,int value)
{
	bt newnode,current,backup;
	newnode=(bt)malloc(sizeof(node));
	newnode->data=value;
	newnode->left=NULL;
	newnode->right=NULL;
	newnode->father=NULL;
	if(root==NULL)
	{
		root=newnode;
		
		return root;
	}
	else
	{
		for(current=root;current!=NULL;)
		{
			backup=current;
			
			if(current->data>value)
			{
				current=current->left;
				
				
			}else
			{
				current=current->right;
				
			}

		}

		if(backup->data>value)
		{
			backup->left=newnode;
			newnode->father=backup;
		
		}else
		{
			backup->right=newnode;
			newnode->father=backup;	
		}
	}

	return root;
}

void preorder(bt ptr)
{
	if(ptr!=NULL && count3<(counttotal-countdelete))
	{
		printf("%d\n",ptr->data);
		count3++;
		preorder(ptr->left);
		preorder(ptr->right);
	}else if(ptr!=NULL && count3==(counttotal-countdelete))
	{
		printf("%d",ptr->data);
	}
}

void preordertest(bt ptr)
{
	if(ptr!=NULL&&ptr->father==NULL)
	{
		printf("%d`s father is:%d\n",ptr->data,0);
		preordertest(ptr->left);
		preordertest(ptr->right);
	}else if(ptr!=NULL&&ptr->father!=NULL)
	{
		printf("%d`s father is:%d\n",ptr->data,ptr->father->data);
		preordertest(ptr->left);
		preordertest(ptr->right);
	}
}



bt position(bt ptr1,int del)
{
	while(ptr1!=NULL)
	{
		if(ptr1->data==del)
		{
			return ptr1;
		}else
		{
			if(ptr1->data>del)
			{
				ptr1=ptr1->left;
			}else
			{
				ptr1=ptr1->right;
			}
		}
	}

	
}

void deletenode(bt ptr1)
{	
	case6++;
	
		if(ptr1->father==NULL)
		{
			if(ptr1->left==NULL&&ptr1->right==NULL)
			{
				//return 0;
			}else if(ptr1->left!=NULL&&ptr1->right==NULL)
			{
				bt tmp=ptr1;
				ptr1=ptr1->left;
				free(tmp);
				ptr1->father=NULL;
				root=ptr1;
			}else if(ptr1->left==NULL&&ptr1->right!=NULL)
			{
				bt tmp=ptr1;
				ptr1=ptr1->right;
				free(tmp);
				ptr1->father=NULL;
				root=ptr1;
			}else if(ptr1->left!=NULL&&ptr1->right!=NULL)
			{
				bt tempptr=ptr1;
				bt tempptrleft=ptr1->left;

				case4++;
				//printf("%d ",ptr1->data);
				ptr1=ptr1->right;

				//printf("%d ",ptr1->data);
				while(ptr1->left!=NULL)
				{
					judge=1;
					ptr1=ptr1->left;
					//printf("%d\n",ptr1->data);
				}

				

				//printf("father:%d ",ptr1->data);
		
				//printf("\n");
				if(judge==0)
				{
					tempptrleft->father=ptr1;
					ptr1->left=tempptrleft;
					free(ptr1->father);
					ptr1->father=NULL;
					root=ptr1;
				}else if(judge==1)
				{
					tempptr->data=ptr1->data;
					ptr1=ptr1->father;
					free(ptr1->left);
					ptr1->left==NULL;
					root=tempptr;
				}
			}
		}else
		{
			if(ptr1->left==NULL && ptr1->right==NULL)
			{
				case1++;
				if(ptr1->data<ptr1->father->data)
				{
					bt ptr2=ptr1;
					ptr1=ptr1->father;
					free(ptr2);
					ptr1->left=NULL;
				}else
				{
					bt ptr2=ptr1;
					ptr1=ptr1->father;
					free(ptr2);
					ptr1->right=NULL;
				}
		

		
			}else if(ptr1->left==NULL && ptr1->right!=NULL)
			{	
		
				case2++;
				bt temp=ptr1;
				if(temp->data<temp->father->data)
				{
					temp->father->left=temp->right;
				}else
				{
					temp->father->right=temp->right;
				}
				free(temp);
			}else if(ptr1->right==NULL && ptr1->left!=NULL)
			{
				case3++;
				bt temp=ptr1;
				if(temp->data<temp->father->data)
				{
					temp->father->left=temp->left;
				}else
				{
					temp->father->right=temp->left;
				}
				free(temp);
			}else
			{
		
		
				bt tempptr=ptr1;
				bt tempptrleft=tempptr->left;
				case4++;
				//printf("%d ",ptr1->data);
				ptr1=ptr1->right;
				//printf("%d ",ptr1->data);
				while(ptr1->left!=NULL)
				{
					judge=1;
					ptr1=ptr1->left;
					//printf("%d\n",ptr1->data);
				}

				

				//printf("father:%d ",ptr1->data);
		
				//printf("\n");
				if(judge==0)
				{
					ptr1->father=tempptr->father;
					tempptr->father->right=ptr1;
					tempptrleft->father=ptr1;
					ptr1->left=tempptrleft;
					free(tempptr);
				}else if(judge==1)
				{
					tempptr->data=ptr1->data;
					//printf("data: %d\n",tempptr->data);

					ptr1=ptr1->father;
					free(ptr1->left);
					ptr1->left==NULL;
				}
				//printf("%d\n",ptr1->left->data);
		
				//printf("%d %d %d %d %d\n",case6,case1,case2,case3,case4);
			}
		}
}

	

