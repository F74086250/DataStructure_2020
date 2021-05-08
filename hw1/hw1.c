#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int power(int,int);
int main(int argc,char **argv)
{

	FILE *finput,*foutput;
		int a;
	char base64table[64]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};
	
	while((a=getopt(argc,argv,"i:o:"))!=-1)
	{
		switch(a)
		{
			case 'i':
			finput=fopen(optarg,"r");
			
			break;
			case 'o':
			foutput=fopen(optarg,"w");
			break;
			case '?':
			return -1;
			break;	



		}
	}
	char chinp[100000];
	
	
	
	
	
	while(fgets(chinp,99999,finput)!=NULL)
	{
		

		char ch='\r';
		char *ret;
		if(ret=strchr(chinp,ch))
		{
			*ret='\n';
		    *(ret+1)='\0';

		}
				
	
		int count=0;
		while (chinp[count]!='\n')
		{
			count++;
		}

		unsigned *numinp=malloc(count*sizeof(unsigned));
		for(int i=0;i<count;i++)
		{
			if(chinp[i]>='0' && chinp[i]<='9')
			{
				numinp[i]=chinp[i]-'0';
			}else
			{
				numinp[i]=chinp[i]-'A'+10;
			}
		
		
		}
	
		unsigned mask=63;
		unsigned compare;
		char ans[3];
		int group=count/3;
		int residue=count%3;
		for(int i=0;i<(count-residue);i+=3)
		{
			compare=numinp[i]*power(2,8)+numinp[i+1]*power(2,4)+numinp[i+2];
		
			ans[0]=base64table[((compare>>6)&mask)];
			ans[1]=base64table[((compare)&mask)];
			ans[2]='\0';
			fputs(ans,foutput);
		

		}
		char a1;
		if(residue==1)
		{
			compare=numinp[count-residue]*power(2,2);
		
			a1=base64table[compare&mask];
			fputc(a1,foutput);
			fputc('=',foutput);
			fputc('\0',foutput);
		}else if(residue==2)
		{
			compare=numinp[count-residue]*power(2,8)+numinp[count-residue+1]*power(2,4);
		
			ans[0]=base64table[((compare>>6)&mask)];
			ans[1]=base64table[compare&mask];
			ans[2]='\0';
			fputs(ans,foutput);
			fputc('=',foutput);
			fputc('=',foutput);
			fputc('\0',foutput);
		}

		fputc('\n',foutput);
		
		

	}


	fclose(finput);
	fclose(foutput);
	

	

	
	return 0;
}
int power(int a,int b)
{
	int ans=1;
	for(int i=1;i<=b;i++)
	{
		ans*=a;
	}
	return ans;
}