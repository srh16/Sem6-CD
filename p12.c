#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct symTable
{
	int id, size, nargs;
	char name[30], type[10], scope, args[40], ret_type[10];  

} symTable;

char keywords[33][11] = {"auto", "double", "int", "struct", "break", "else", "long int", "long double",	"switch", "case", "enum", "register", 
	"typedef", "char", "extern", "return", "union", "const", "float", "short int", "unsigned", "continue", "for", "signed",	"void",
	"default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};

char var_type[6][11] = {"int", "float", "double", "long int", "long double", "short int"};
char buf[20];
symTable ST[100];

void parser(char c1, int *iter, int *after_main, FILE *f1, FILE *f2);

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
	fseek(f1, -1, SEEK_CUR);
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
	fprintf(f2, "<num, %s> ", dig);
	fseek(f1, -1, SEEK_CUR);
}

int main()
{
	char c1;
	int iter = 0, after_main = 0;

	FILE *f1 = fopen("sample.c", "r");
	FILE *f2;

	if(f1 == NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	}

	f2 = fopen("Output1.c", "w");
	//c1 = fgetc(f1);

	while(!feof(f1))//this loop searches the for the current word
	{
	    c1 = getc(f1);

	    int buf_i;

	    printf("character passed main :\t%c :\t%d\n", c1, (int)c1);
	    parser(c1, &iter, &after_main, f1, f2);
	  
	}	

	fclose(f1);
	return 0;
}

void parser(char c1, int *iter, int *after_main, FILE *f1, FILE *f2)
{
	int j;

	int id = *iter;
	int af_main = *after_main;

	printf("character received :\t%c :\t%d\n", c1, (int)c1);

    if(c1 == '"')
	{
		literal(c1, f1, f2);
	}

    else if(c1 == '(' || c1 == '{' || c1 == '}' || c1 == '[' || c1 == ']')
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
		int buf_i = 0;
		int kword = 0;

	    while(isalnum(c1)) 	
	    {
		    buf[buf_i++] = c1;
		    c1 = fgetc(f1);
		}
		buf[buf_i] = '\0';

		//printf("buf = %s c1 = %c", buf, c1);

		for(j=0; j<32; j++)
		{
    		if(!strcmp(buf, keywords[j]))
    		{
    			fprintf(f2, "<%s> ", buf);
    			kword = 1;

    			for(int k=0; k<6; k++)
    			{
    				if(!strcmp(buf, var_type[k]))
    				{
    					strcat(ST[id++].type, buf);
    					break;
    				}
    			}

    			if(!strcmp(buf, "main"))
    				af_main = 1;
    			break;
    		}
    	} 
    	if(!kword)
    	{
    		fprintf(f2, "<id, %d> ", id);
    		strcat(ST[id].name, buf);

    		if(af_main)
    			ST[id].scope = 'L';
    		else
    			ST[id].scope = 'G';
    	}

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
    	
    	else if(c1 == '(')
    	{
    		fprintf(f2, "<%c> ", c1);

    		int n = 0;

    		while(c1 != ')' && !feof(f1))
    		{
    			c1 = fgetc(f1);

    			if(c1 == ',')
    				n++;
    			printf("character passed with :\t%c :\t%d\n", c1, (int)c1);
    			parser(c1, &id, &af_main, f1, f2);
    		}
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

	return;
}


/*

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

		//printf("buf = %s c1 = %c", buf, c1);

		for(j=0; j<32; j++)
		{
			if(!strcmp(buf, keywords[j]))
			{
				fprintf(f2, "<%s> ", buf);
				kword = 1;

				for(int k=0; k<6; k++)
				{
					if(!strcmp(buf, var_type[i]))
					{
						strcat(ST[iter++].type, buf);
						break;
					}
				}

				if(!strcmp(buf, "main"))
					after_main = 1;
				break;
			}
		} 
		if(!kword)
		{
			fprintf(f2, "<id, %d> ", ++i);
			strcat(ST[iter].name, buf);

			if(after_main)
				ST[iter].scope = 'L';
			else
				ST[iter].scope = 'G'
		}

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
*/