#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int power(int,int);
int lineA[10000]={0},lineB[10000]={0},plate[10000]={0},la=0,lb=0,la1=0,lb1=0,plate1=10000,judge;
int count=0,total=0;
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
		//printf("%s\n",inp);
		
	
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
					
					plate1--;
					plate[plate1]=total;
					
			
					break;
				case 2:
			
					if(inp[0]=='A')
					{
						int temp;
			
						temp=plate[plate1];
						plate[plate1]=0;
						lineA[la]=temp;
				
						la++;
						plate1++;	

					}else if(inp[0]=='B')
					{
						int temp;
					
						temp=plate[plate1];
						plate[plate1]=0;
						lineB[lb]=temp;

						lb++;
						plate1++;

					}

					break;
				case 3:

					if (inp[0]=='A')
					{
						char c[64];
						sprintf(c,"%d",lineA[la1]);
						printf("%s\n",c);
						la1++;
					}else if(inp[0]=='B')
					{
						char c[64];
						sprintf(c,"%d",lineB[lb1]);
						printf("%s\n",c);
						lb1++;
					}
					break;
			}
		} 
	}

	return 0;

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