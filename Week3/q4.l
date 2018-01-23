%{
int pf=0,sf=0;
%}

%%
printf {pf++; fprintf(yyout,"WRITE");}
scanf {sf++; fprintf(yyout,"READ");}
%%

int main()
{
	yyin=fopen("q3.l","r");
	yyout=fopen("q4_out.l","w");
	yylex();
	printf("There are %d printf and %d scanf\n",pf,sf);
	return 0;
}

int yywrap()
{
	return 1;
}
