#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char tokens[20][3]={"(" , "a" , ")" , "$" , "," , ">" , "," , ">" , "," , "a" , ")" , "$"};
int currToken=-1;

void err()
{

	printf("\nError parsing input string at %d %s\n",currToken,tokens[currToken]);
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
		err();
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
			err();
	}
	else
		err();

	if(strcmp(tokens[currToken],"$")==0)
		success();
	else
		err();
}

int main()
{
	currToken++;
	S();
	return 0;
}
