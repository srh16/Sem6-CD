#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int len=0;
char *buffer = 0;
long length;
char delim[] = "\t\n \n\t";
int currIndex = 0;

char keywords[34][11] = {"main", "auto", "double", "int", "struct", "break", "else", "long int", "long double", 	"switch", "case", "enum", "register", 
	"typedef", "char", "extern", "return", "union", "const", "float", "short int", "unsigned", "continue", "for", "signed", 	"void", 
	"default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};

char *relopp(char *s)
{
	char *op = malloc(3*sizeof(char));
	op[0] = s[currIndex++];

	char c2 = s[currIndex];
	switch(c2)
	{
		case '>' :op[1] = '>'; op[2] = '\0';
				 break;
		case '=' :op[1] = '='; op[2] = '\0';
				 break;
		default :op[1] = '\0';
	}
	
	return op;
}

char *arithopp(char *s)
{
	char *op = malloc(3*sizeof(char));
	op[0] = s[currIndex++];

	char c2 = s[currIndex];
	switch(c2)
	{
		case '+' :op[1] = '+'; op[2] = '\0';
				 break;
		case '=' :op[1] = '='; op[2] = '\0';
				 break;
		case '-' :op[1] = '-'; op[2] = '\0';
				 break;
		default :op[1] = '\0';
	}
	
	return op;
}


char *nxt_tok(char* s, char* delm)
{
	char *next_token = calloc(30, sizeof(char));
	if(s[currIndex] != '\0')
	{
		int i;
		int j=0;
		while(delm[j] != '\0')
		{
			if(s[currIndex] == delm[j])
				currIndex++;
			else
				j++;
		}

	    if(isalpha(s[currIndex]) || s[currIndex] == '_')
	    {
	    	i=0;
	    	while(isalnum(s[currIndex]) || s[currIndex] == '_' || s[currIndex] == '*')
	    		next_token[i++] = s[currIndex++];

	    	next_token[i] = '\0';

	    	int kword_found = 0;

	    	for(int k=0; k<34; k++)
	    	{
	    		if(!strcmp(next_token, keywords[k]))
	    		{
	    			kword_found = 1;
	    			break;
	    		}
	    	}
	    	
	    	if(!kword_found)
	    		strcpy(next_token, "id");

	    }
	    else if(isdigit(s[currIndex]))
	    {
	    	i=0;
	    	while(isdigit(s[currIndex]))
	    		currIndex++;

	    	strcpy(next_token, "num");
	    }
	    else if(s[currIndex] == '<' || s[currIndex] == '>' || s[currIndex] == '=')
	    {
	    	i=0;
	    	next_token = relopp(s);
	    }
	    else if(s[currIndex] == '+' || s[currIndex] == '-' || s[currIndex] == '*' || s[currIndex] == '/')
	    {
	    	i=0;
	    	next_token = arithopp(s);
	    }
	    else if(ispunct(s[currIndex]))
	    {
	    	i=0;
	    	next_token[i++] = s[currIndex++];
	    	next_token[i] = '\0';
	    }
		len=strlen(next_token);
	    return next_token;
	}

	return NULL;
}

char *getNextToken()
{
	char *token = nxt_tok(buffer, delim);

	if(token == NULL)
		return NULL;

	return token; 
}

void start()
{
	FILE *f1 = fopen("input.c", "rb");

	if(f1)
	{
		fseek (f1, 0, SEEK_END);
		length = ftell (f1);
		fseek (f1, 0, SEEK_SET);
		buffer = malloc (length);
		
		if (buffer)
		    fread (buffer, 1, length, f1);

		fclose (f1);
	}
	else
	{
		printf("Cannot open the file\n");
		exit(0);
	}
	
}


