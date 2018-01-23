%{
int lc=0;
%}

%%
\n lc++;
%%

int main()
{
	yylex();
	printf("There were %d lines\n",lc);
	return 0;
}

int yywrap()
{
	return 1;
}
