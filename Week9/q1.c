#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "p1.c"

char *ptr;

void err(int i)
{

	printf("\nError parsing input string at \" %s \". Error code: %d. \n",ptr,i);
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
void decision_stat();
void dprime();
void looping_stat();

void program()
{
	printf("program\n");
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
					{	}
					else
						err(1);
				}
				else
					err(2);
			}
			else
				err(3);
		}
		else
			err(4);
	}
	else
		err(5);

	ptr=getNextToken();
	if(strcmp(ptr,"")==0)
		success();
	else
		err(6);
}

void declarations()
{
	printf("declarations\n");
	ptr=getNextToken();
	currIndex -= len;
	if(strcmp(ptr,"id")==0)
	{ }	
	else
	{
		data_types();	

		identifier_list();

		ptr=getNextToken();
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
	printf("data_types\n");
	ptr=getNextToken();
	if(strcmp(ptr,"int")==0 || strcmp(ptr,"char")==0)
	{ }
	else
		err(8);
}
 
void identifier_list() 
{
	printf("identifier_list\n");
	ptr=getNextToken();
	if(strcmp(ptr,"id")==0)
	{
		ptr=getNextToken();
		if(strcmp(ptr,",")==0)
		{
			identifier_list();
		}
		else if(strcmp(ptr,"[")==0)
		{
			ptr=getNextToken();
			if(strcmp(ptr,"num")==0)
			{
				ptr=getNextToken();
				if(strcmp(ptr,"]")==0)
				{
					ptr=getNextToken();
					if(strcmp(ptr,",")==0)
					{
						identifier_list();
					}
					else if(strcmp(ptr,";")==0)
						currIndex-=len;
					else
						err(9);
				}
				else
					err(10);
			}
			else
				err(11);
		}
		else if(strcmp(ptr,";")==0)
		{	currIndex-=len;}
		else
			err(12);
	}
	else
		err(13);
}

void statement_list()
{
	printf("statement_list\n");
	ptr=getNextToken();
	currIndex -= len;
	if(strcmp(ptr,"}")==0)
	{ }
	else
	{
		statement();
		statement_list();
	}
}

void statement()
{
	printf("statement\n");
	ptr=getNextToken();
	currIndex -= len;
	if(strcmp(ptr,"id")==0)
	{
		assign_stat();
		ptr=getNextToken();
		if(strcmp(ptr,";")==0)
		{ }
		else
			err(14);
	}
	else if(strcmp(ptr,"if")==0)
	{
		decision_stat();
	}
	else
		looping_stat();
}

void assign_stat()
{
	printf("assign_stat\n");
	ptr=getNextToken();
	if(strcmp(ptr,"id")==0)
	{
		ptr=getNextToken();
		if(strcmp(ptr,"=")==0)
		{
			expn();
		}
		else
			err(15);
	}
	else
		err(16);
}

void expn()
{
	printf("expn\n");
	simple_expn();
	eprime();
}

void eprime()
{
	printf("eprime\n");
	ptr=getNextToken();
	currIndex -= len;
	if(strcmp(ptr,";")==0 || strcmp(ptr,")")==0)
	{ }
	else
	{
		relop();
		simple_expn();
	}
}

void simple_expn()
{
	printf("simple_expn\n");
	term();
	seprime();
}

void seprime()
{
	printf("seprime\n");
	ptr=getNextToken();
	currIndex -= len;
	if(strcmp(ptr,";")==0 || strcmp(ptr,")")==0 || strcmp(ptr,"==")==0 || strcmp(ptr,"!=")==0 || strcmp(ptr,"<=")==0 || strcmp(ptr,">=")==0 || strcmp(ptr,"<")==0 || strcmp(ptr,">")==0)
	{ }
	else
	{
		addop();
		term();
		seprime();
	}
}

void term()
{
	printf("term\n");
	factor();
	tprime();
}

void tprime()
{
	printf("tprime\n");
	ptr=getNextToken();
	currIndex -= len;
	if(strcmp(ptr,"+")==0 || strcmp(ptr,"-")==0 || strcmp(ptr,";")==0 || strcmp(ptr,")")==0 || strcmp(ptr,"==")==0 || strcmp(ptr,"!=")==0 || strcmp(ptr,"<=")==0 || strcmp(ptr,">=")==0 || strcmp(ptr,"<")==0 || strcmp(ptr,">")==0)
	{ }
	else
	{
		mulop();
		factor();
		tprime();
	}
}

void factor()
{
	printf("factor\n");
	ptr=getNextToken();
	if(strcmp(ptr,"id")==0 || strcmp(ptr,"num")==0 )
	{ }
	else
	{
		err(17);
	}
}

void relop()
{
	printf("relop\n");
	ptr=getNextToken();
	if(strcmp(ptr,"==")==0 || strcmp(ptr,"!=")==0 || strcmp(ptr,"<=")==0 || strcmp(ptr,">=")==0 || strcmp(ptr,">")==0 || strcmp(ptr,"<")==0)
	{ }
	else
	{
		err(18);
	}
}

void addop()
{
	printf("addop\n");
	ptr=getNextToken();
	if(strcmp(ptr,"+")==0 || strcmp(ptr,"-")==0)
	{ }
	else
	{
		err(19);
	}
}

void mulop()
{
	printf("mulop\n");
	ptr=getNextToken();
	if(strcmp(ptr,"*")==0 || strcmp(ptr,"/")==0 || strcmp(ptr,"%")==0)
	{ }
	else
	{
		err(20);
	}
}

void decision_stat()
{
	printf("decision_stat\n");
	ptr=getNextToken();
	if(strcmp(ptr,"if")==0)
	{
		ptr=getNextToken();
		if(strcmp(ptr,"(")==0)
		{
			expn();
			ptr=getNextToken();
			if(strcmp(ptr,")")==0)
			{ 
				ptr=getNextToken();
				if(strcmp(ptr,"{")==0)
				{ 
					statement_list();
					ptr=getNextToken();
					if(strcmp(ptr,"}")==0)
					{ 
						dprime();
					}
					else
						err(21);
				}
				else
					err(22);
			}
			else
				err(23);
		}
		else
			err(24);
	}
	else
		err(25);
}

void dprime()
{
	printf("dprime\n");
	ptr=getNextToken();
	if(strcmp(ptr,"id")==0 || strcmp(ptr,"if")==0 || strcmp(ptr,"for")==0 || strcmp(ptr,"while")==0 || strcmp(ptr,"}")==0)
	{
		currIndex-=len;
	}
	else if(strcmp(ptr,"else")==0)
	{
		ptr=getNextToken();
		if(strcmp(ptr,"{")==0)
		{
			statement_list();
			ptr=getNextToken();
			if(strcmp(ptr,"}")==0)
			{ }
			else
				err(26);
		}
		else
			err(27);
	}
	else
		err(28);
}

void looping_stat()
{
	printf("looping_stat\n");
	ptr=getNextToken();
	if(strcmp(ptr,"while")==0)
	{
		ptr=getNextToken();
		if(strcmp(ptr,"(")==0)
		{
			expn();
			ptr=getNextToken();
			if(strcmp(ptr,")")==0)
			{ 
				ptr=getNextToken();
				if(strcmp(ptr,"{")==0)
				{ 
					statement_list();
					ptr=getNextToken();
					if(strcmp(ptr,"}")==0)
					{  }
					else
						err(29);
				}
				else
					err(30);
			}
			else
				err(31);
		}
		else
			err(32);
	}
	else if(strcmp(ptr,"for")==0)
	{
		ptr=getNextToken();
		if(strcmp(ptr,"(")==0)
		{
			assign_stat();
			ptr=getNextToken();
			if(strcmp(ptr,";")==0)
			{ 
				expn();
				ptr=getNextToken();
				if(strcmp(ptr,";")==0)
				{ 
					assign_stat();
					ptr=getNextToken();
					if(strcmp(ptr,")")==0)
					{  
						ptr=getNextToken();
						if(strcmp(ptr,"{")==0)
						{ 
							statement_list();
							ptr=getNextToken();
							if(strcmp(ptr,"}")==0)
							{  }
							else
								err(33);
						}
						else
							err(34);
					}
					else
						err(35);
				}
				else
					err(36);
			}
			else
				err(37);
		}
		else
			err(38);
	}
	else
		err(39);
}

int main()
{
	start();
	program();
	return 0;
}
