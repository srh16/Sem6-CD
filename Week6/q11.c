#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void relop(char c, FILE *f1, FILE *f2)
{
	char op[3];
	op[0] = c;
	FILE *temp = f1;

	char c2 = fgetc(temp);
	switch(c2)
	{
		case '>' :op[1] = '>'; op[2] = '\0';
				  break;
		case '=' :op[1] = '='; op[2] = '\0';
				  break;
		default  :op[1] = '\0';
	}
	fprintf(f2, "<%s> ", op);
}

void arithop(char c, FILE *f1, FILE *f2)
{
	char op[3];
	op[0] = c;
	FILE *temp = f1;

	char c2 = fgetc(temp);
	switch(c2)
	{
		case '+' :op[1] = '+'; op[2] = '\0';
				  break;
		case '=' :op[1] = '='; op[2] = '\0';
				  break;
		case '-' :op[1] = '-'; op[2] = '\0';
				  break;
		default  :op[1] = '\0';
	}
	fprintf(f2, "<%s> ", op);
	//fseek(f1, -1, SEEK_CUR);
}

void literal(char c, FILE *f1, FILE *f2)
{
	c = fgetc(f1);

	while(c != '"')
		c = fgetc(f1);
	
	fprintf(f2, "<%s> ", "Literal");
}

void digit(char c, FILE *f1, FILE *f2)
{
	char dig[100];
	int d = 0;

	while(isdigit(c))
	{
		dig[d++] = c;
		c = fgetc(f1);
	}

	dig[d] = '\0';
	fprintf(f2, "<%s> ", dig);
	fseek(f1, -1, SEEK_CUR);
}

int main()
{
	char c1;
	int i = 0, j;
	char keywords[32][10] = {"auto", "double", "int",	"struct", "break",	"else",	"long",	"switch", "case", "enum", "register", 
	"typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed",	"void",
	"default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};

	FILE *f1 = fopen("q1_in.c", "r");
	FILE *f2;

	if(f1 == NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	}

	f2 = fopen("q1_out.c", "w");

	while(!feof(f1))//this loop searches the for the current word
	{
	    c1 = getc(f1);

	    int buf_i;
	    char buf[20];
	    int word;

	    if(c1 == '"')
		{
			literal(c1, f1, f2);
		}

	    else if(c1 == '(' || c1 == ')' || c1 == '{' || c1 == '}' || c1 == '[' || c1 == ']')
		    	fprintf(f2, "<%c> ", c1);

		else if(c1 == '<' || c1 == '>')
    	{
    		relop(c1, f1, f2);
    	}
    	
    	else if(c1 == '+' || c1 == '-' || c1 == '=' || c1 == '*' || c1 == '/')
    	{
    		arithop(c1, f1, f2);
    	}
		
		else if(isalpha(c1))
		{
			buf_i = 0;
			int kword = 0;

		    while(isalnum(c1)) 	
		    {
			    buf[buf_i++] = c1;
			    c1 = fgetc(f1);
			}
			buf[buf_i] = '\0';

			printf("buf = %s c1 = %c", buf, c1);

			for(j=0; j<32; j++)
			{
	    		if(!strcmp(buf, keywords[j]))
	    		{
	    			fprintf(f2, "<%s> ", buf);
	    			kword = 1;
	    			break;
	    		}
	    	} 
	    	if(!kword)
	    		fprintf(f2, "<id, %d> ", ++i);

	    	if(c1 == ' '|| c1 == '\t')
	    		fprintf(f2, "%c", c1);
	    	
	    	else if(c1 == '<' || c1 == '>')
	    	{
	    		relop(c1, f1, f2);
	    	}
	    	
	    	else if(c1 == '+' || c1 == '-' || c1 == '=' || c1 == '*' || c1 == '/')
	    	{
	    		arithop(c1, f1, f2);
	    	}
	    	else
	    		fprintf(f2, "<%c> ", c1);	
		}
		
		else if(isdigit(c1))
		{
			digit(c1, f1, f2);
		}

		else if(ispunct(c1))
			fprintf(f2, "<%c>", c1);

		else 
			fprintf(f2, "%c", c1);
	}	

	fclose(f1);
	return 0;
}
