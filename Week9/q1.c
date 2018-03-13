#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "p1.c"

char *ptr;

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


void program();
void declarations();
void assign_stat();
void data_types();
void identifier_list();
void identifier_list();
void statement_list();
void statement();
void expn();
void simple_expn();
void eprime();
void relop();
void addop();
void mulop();
void term();
void seprime();
void tprime();
void factor();

void factor()
{
	ptr=getNextToken();
	if(strcmp(ptr,"id")==0 || strcmp(ptr,"num")==0 )
	{ }
	else
	{
		err(17);
	}
}

void tprime()
{
	ptr=getNextToken();
	if(strcmp(ptr,"+")==0 || strcmp(ptr,"-")==0 || strcmp(ptr,";")==0 )
		currIndex-=len;
	else
	{
		mulop();
		factor();
		tprime();
	}
}

void seprime()
{
	ptr=getNextToken();
	if(strcmp(ptr,";")==0)
		currIndex-=len;
	else
	{
		addop();
		term();
		seprime();
	}
}

void term()
{
	factor();
	tprime();
}

void relop()
{
	ptr=getNextToken();
	if(strcmp(ptr,"==")==0 || strcmp(ptr,"!=")==0 || strcmp(ptr,"<=")==0 || strcmp(ptr,">=")==0 || strcmp(ptr,">")==0 || strcmp(ptr,"<")==0)
	{ }
	else
	{
		err(16);
	}
}

void addop()
{
	ptr=getNextToken();
	if(strcmp(ptr,"+")==0 || strcmp(ptr,"-")==0)
	{ }
	else
	{
		err(15);
	}
}

void mulop()
{
	ptr=getNextToken();
	if(strcmp(ptr,"*")==0 || strcmp(ptr,"/")==0 || strcmp(ptr,"%")==0)
	{ }
	else
	{
		err(14);
	}
}

void eprime()
{
	ptr=getNextToken();
	if(strcmp(ptr,";")==0)
		currIndex-=len;
	else
	{
		relop();
		simple_expn();
	}
}

void expn()
{
	simple_expn();
	eprime();
}

void simple_expn()
{
	term();
	seprime();
}

void statement_list()
{
	ptr=getNextToken();
	if(strcmp(ptr,"}")==0)
		currIndex-=len;
	else
	{
		statement();
		statement_list();
	}
}

void statement()
{
	assign_stat();
}


void program()
{
	ptr=getNextToken();
	if(strcmp(ptr,"main")==0)
	{
		ptr=getNextToken();
		if(strcmp(ptr,"(")==0)
		{
			ptr=getNextToken();
			if(strcmp(ptr,")")==0)
			{
				ptr=getNextToken();
				if(strcmp(ptr,"{")==0)
				{
					declarations();
					statement_list();
					ptr=getNextToken();
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

	if(strcmp(ptr,"")==0)
		success();
	else
		err(6);
}

void declarations()
{
	ptr=getNextToken();
	
	if(strcmp(ptr,"id")==0)
	{
		currIndex -= len;	
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
	ptr=getNextToken();
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
	ptr=getNextToken();
	if(strcmp(ptr,"id")==0)
	{
		identifier1();
	}
	else
		err(13);
}

void assign_stat()
{
	ptr=getNextToken();
	if(strcmp(ptr,"id")==0)
	{
		ptr=getNextToken();
		if(strcmp(ptr,"=")==0)
		{
			ptr=getNextToken();
			if(strcmp(ptr,"id")==0||strcmp(ptr,"num")==0)
			{
				ptr=getNextToken();
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
	start();
	program();
	return 0;
}
