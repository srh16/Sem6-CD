#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *ptr;
FILE* f1;

void err(int i)
{

	printf("\nError parsing input string %d\n",i);
	exit(0);
}

void success()
{
	printf("\nSuccess parsing input string\n");
	exit(0);
}

char* getNextToken()
{
	char *token=calloc(25,sizeof(char));
	char c;
	int i=0;
	while((c=fgetc(f1))!='<');
	while((c=fgetc(f1))!='>')
	{
		token[i++]=c;
	}
	return token;
}

void program();
void declarations();
void assign_stat();
void data_types();
void identifier_list();


void program()
{
	ptr=getNextToken();
	printf("%s\n",ptr);
	if(strcmp(ptr,"main")==0)
	{
		ptr=getNextToken();printf("%s\n",ptr);
		if(strcmp(ptr,"(")==0)
		{
			ptr=getNextToken();printf("%s\n",ptr);
			if(strcmp(ptr,")")==0)
			{
				ptr=getNextToken();printf("%s\n",ptr);
				if(strcmp(ptr,"{")==0)
				{
					declarations();
					assign_stat();
					ptr=getNextToken();printf("%s\n",ptr);
					if(strcmp(ptr,"}")==0)
					{
						ptr=getNextToken();
					}
					else
						err(5);
				}
				else
					err(4);
			}
			else
				err(3);
		}
		else
			err(2);
	}
	else
		err(1);

	if(strcmp(ptr,"$")==0)
		success();
	else
		err(6);
}

void declarations()
{
	ptr=getNextToken();printf("%s\n",ptr);
	if(strcmp(ptr,"id")==0)
	{
		fseek(f1,-5,SEEK_CUR);	
	}	
	else
	{
		data_types();	

		identifier_list();

		if(strcmp(ptr,";")==0)
		{
			declarations();
		}
		else
			err(7);
	}
}

void data_types()
{
	if(strcmp(ptr,"int")==0||strcmp(ptr,"char")==0)
	{
	}
	else
		err(12);
}

void identifier1()
{
	ptr=getNextToken();printf("%s\n",ptr);
	if(strcmp(ptr,";")==0)
	{
	}
	else if(strcmp(ptr,",")==0)
	{
		identifier_list();
	}
}

void identifier_list()
{
	ptr=getNextToken();printf("%s\n",ptr);
	if(strcmp(ptr,"id")==0)
	{
		identifier1();
	}
	else
		err(13);
}

void assign_stat()
{
	ptr=getNextToken();printf("%s\n",ptr);
	if(strcmp(ptr,"id")==0)
	{
		ptr=getNextToken();printf("%s\n",ptr);
		if(strcmp(ptr,"=")==0)
		{
			ptr=getNextToken();printf("%s\n",ptr);
			if(strcmp(ptr,"id")==0||strcmp(ptr,"num")==0)
			{
				ptr=getNextToken();printf("%s\n",ptr);
				if(strcmp(ptr,";")==0)
				{
				}
				else
					err(11);
			}
			else
				err(10);
		}
		else
			err(9);
	}
	else
		err(8);
}

int main()
{
	f1=fopen("inp.txt","r");
	program();
	return 0;
}
