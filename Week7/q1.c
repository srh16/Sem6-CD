#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char tokens[20][3]={"(" , "a" , ")" , "$" , "," , ">" , "," , ">" , "," , "a" , ")" , "$"};
int currToken=-1;

void err(int i)
{

	printf("\nError parsing input string at %d %s %d\n",currToken,tokens[currToken],i);
	exit(0);
}

void success()
{
	printf("\nSuccess parsing input string\n");
	exit(0);
}

void getNextToken()
{
	printf("%s ",tokens[currToken]);
	currToken++;
}

void S();

void T1()
{
	if(strcmp(tokens[currToken],",")==0)
	{
		getNextToken();
		
		T1();
	}
	else if(strcmp(tokens[currToken],")")==0)
		return;
	
	else	
		err(1);
}

void T()
{
	S();	

	getNextToken();

	T1();
}

void S()
{
	if(strcmp(tokens[currToken],"a")==0)
	{	
		getNextToken();
	}
	else if(strcmp(tokens[currToken],">")==0)
	{	
		getNextToken();
	}
	else if(strcmp(tokens[currToken],"(")==0)
	{
		getNextToken();
		
		T();
		
		getNextToken();
		
		if(strcmp(tokens[currToken],")")==0)
		{	
			getNextToken();
		}	
		else
			err(2);
	}
	else
		err(3);

	printf("\n%s\n",tokens[currToken]);
	if(strcmp(tokens[currToken],"$")==0)
		success();
	else
		err(4);
}

int main()
{
	currToken++;
	S();
	return 0;
}
