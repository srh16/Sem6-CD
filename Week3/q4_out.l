%{
int pi=0,ni=0,pf=0,nf=0;
%}

%%
(\+?([0-9]+)((\.[0-9]+))(E(\+|-)?([0-9]+))?) pf++;
(-([0-9]+)((\.[0-9]+))(E(\+|-)?([0-9]+))?) nf++;
((\+)?([0-9]+)(E(\+|-)?([0-9]+))?) pi++;
(-([0-9]+)(E(\+|-)?([0-9]+))?) ni++;
%%

int main()
{
	yylex();
	WRITE("There were %d positive integer, %d negative integer, %d positive floating point number and %d negative floating point number\n",pi,ni,pf,nf);
	return 0;
}

int yywrap()
{
	return 1;
}
