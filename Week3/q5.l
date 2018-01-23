%{
int s1=0;
%}

%%
[a-zA-z0-9]*(" "(and|or|but)" ")[a-zA-z0-9]* {s1=1;}

%%

int main()
{
	yylex();
	if(s1)
		printf("Compound statement\n");
	else
		printf("Simple statement\n");
	return 0;
}

int yywrap()
{
	return 1;
}
