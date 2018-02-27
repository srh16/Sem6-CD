#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct symTable
{
	int id, size, nargs;
	char name[30], type[10], scope, args[100], ret_type[10]; 

} symTable;

char keywords[33][11] = {"auto", "double", "int", "struct", "break", "else", "long int", "long double", 	"switch", "case", "enum", "register", 
	"typedef", "char", "extern", "return", "union", "const", "float", "short int", "unsigned", "continue", "for", "signed", 	"void", 
	"default", "goto", "sizeof", "volatile", "do", "if", "static", "while"};

char var_type[7][11] = {"char", "int", "float", "double", "long int", "long double", "short int"};
int var_size[7]={sizeof(char),sizeof(int),sizeof(float),sizeof(double),sizeof(long int),sizeof(long double),sizeof(short int)};
char buf[20];
symTable ST[100];
int func_found=0;
int arg_present = 0;
int n;

void parser(char c1, int *n_arg, int *iter, int *after_main, FILE *f1, FILE *f2);

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
		default :op[1] = '\0';
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
		default :
		op[1] = '\0';
		fseek(f1, -1, SEEK_CUR);

	}
	fprintf(f2, "<%s> ", op);
	
}

void literal(char c, FILE *f1, FILE *f2)
{
	c = fgetc(f1);

	while(c != '"')
		c = fgetc(f1);
	
	fprintf(f2, "<%s> ", "Literal");
}

int digit(char c, FILE *f1, FILE *f2)
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
	int ret=atoi(dig);
	return ret;
}

int main()
{
	char c1;
	int iter = 0, after_main = 0, n_arg = 0;

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

	  printf("char passed from main :\t%c :\t%d\n", c1, (int)c1);
	  parser(c1, &n_arg, &iter, &after_main, f1, f2);
	 
	}	

	fclose(f1);
	fclose(f2);
	int x=0;
	printf("\n\n\n\nSymbol table\n\n");
	printf("ID\tName\tType\tSize\tScope\tArgs(No.)\tArguments\tReturn Type\n");
	for(x=0;x<iter;x++)
	{
		printf("%d\t%s\t%s\t%d\t%c\t%d\t%s\t\t\t%s\n", x, ST[x].name, ST[x].type, ST[x].size, ST[x].scope, ST[x].nargs, ST[x].args, ST[x].ret_type);
	}
	return 0;
}

void parser(char c1, int *n_arg, int *iter, int *af_main, FILE *f1, FILE *f2)
{
	int j;

	int *id = iter;
	int *n = n_arg;
	

	printf("char received :\t%c :\t%d\n", c1, (int)c1);

	if(c1 == '"')
	{
		literal(c1, f1, f2);
	}

	else if(c1 == '{' || c1 == '}' || c1=='[' ||c1==']' )
		fprintf(f2, "<%c> ", c1);

	else if(c1 == '<' || c1 == '>')
	{
		relop(c1, f1, f2);
	}

	else if(c1 == '+' || c1 == '-' || c1 == '=' || c1 == '*' || c1 == '/')
	{
		arithop(c1, f1, f2);
	}

	else if(isalpha(c1) || c1 == '_')
	{
		int buf_i = 0;
		int kword = 0;

	  while(isalnum(c1) || c1 == '_') 	
	  {
		  buf[buf_i++] = c1;
		  c1 = fgetc(f1);
		}
		buf[buf_i] = '\0';

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
	  					strcpy(ST[*id].type, buf);
	  					ST[*id].size=var_size[k];
	  					break;
	  				}
	  			}
	  		}
		} 
	  	if(!kword)
	  	{
	  		int x=0;
	  		for(x=0;x<*id;x++)
				{
					if(!strcmp(buf, ST[x].name))
						break;
				}
				if(x==(*id))
				{
		  		strcpy(ST[*id].name, buf);
		  		fprintf(f2, "<id, %d> ", *id);
		  		if(*af_main)
	  				ST[(*id)++].scope = 'L';
	  			else
	  				ST[(*id)++].scope = 'G';
		  	}
		  	else
		  	{
		  		fprintf(f2, "<id, %d> ", x);
		  	}
		  	if(!strcmp(buf, "main"))
	  				*af_main = 1;

	  	}

	  	if(c1 == ' '|| c1 == '\t')
	  		fprintf(f2, "%c", c1);

		else if(c1 == ',')
			(*n) = (*n) + 1;
	  	
	  	else if(c1 == '<' || c1 == '>')
	  	{
	  		relop(c1, f1, f2);
	  	}

	  	else if(c1 == '[')
		{
			fprintf(f2, "<%c> ", c1);
			c1=fgetc(f1);
			int z=-1;
			if(isdigit(c1))
				z=digit(c1,f1,f2);
			else if(c1==']')
				fprintf(f2, "<%c> ", c1);
			if(z!=-1)
			{
				ST[(*id)-1].size*=z;
			}
		}
	  	
	  	else if(c1 == '+' || c1 == '-' || c1 == '=' || c1 == '*' || c1 == '/')
	  	{
	  		arithop(c1, f1, f2);
	  	}
	  	
	  	else if(c1 == '(')
	  	{
	  		fprintf(f2, "<%c> ", c1);

	  		if(!kword)
	  		{
	  			func_found = 1;
	  			*n = 0;

	  			if(!strcmp(ST[*id -1].type, ""))
	  				strcpy(ST[*id - 1].ret_type, "void");
	  			else
	  				strcpy(ST[*id - 1].ret_type, ST[*id-1].type);
	  			strcpy(ST[*id - 1].type, "FUNC");
	  			ST[*id - 1].size=0;
	  		}
	  		
	  		int pars_i = 0;

	  		while(c1 != ')' && !feof(f1))
	  		{
	  			c1 = fgetc(f1);

	  			if(c1 == ',')
	  			{
	  				arg_present = 1;
	  				(*n) = (*n) + 1;
	  			}

	  			else if(isalnum(c1) || c1 == '"')
	  			{
	  				printf("FOUND 1!!!\n");
	  				arg_present = 1;
	  			}
	  				

	  			printf("char passed from parser %d :\t%c :\t%d\n", pars_i, c1, (int)c1);
	  			pars_i++;
	  			printf("No. of args : %d\n", *n);
	  			parser(c1, n, id, af_main, f1, f2);
	  			printf("Return to the while (within parser)\n");
	  			
	  			if(!func_found)
	  				break;
	  		}
	  		printf("No. of args (func over): %d\n", *n);
	  		int varnum;
	  		for(varnum=*id;varnum<(*id)+(*n);varnum++)
	  		{
	  			char temp[100];
	  			sprintf(temp,"<id,%d> ",varnum);
	  			strcat(ST[*id - 1].args,temp);
	  		}
	  		printf("**Parse while ended!**\n");
	  	}
	  	
	  	else if(c1 == ')')
	  	{
	  		fprintf(f2, "<%c> ", c1);

	  		//printf("*n = %d || arg_present = %d\n", *n, arg_present);
	  		
	  		if(*n >= 1)
	  		{
		  		for(int x= *id; x>=0; x--)
		  		{
		  			if(!strcmp(ST[x].type, "FUNC"))
		  			{
		  				ST[x].nargs = *n + 1;
		  				break;
		  			}
		  		}
		  	}
		  	else if(arg_present)
		  	{
		  		for(int x= *id; x>=0; x--)
		  		{
		  			if(!strcmp(ST[x].type, "FUNC"))
		  			{
		  				ST[x].nargs = 1;
		  				break;
		  			}
		  		}
		  	}
	  		
	  		*n = 0;
	  		arg_present = 0;
	  		func_found = 0;
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

	return ;
}
