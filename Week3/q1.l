%{
int v=0,c=0;
%}

%%
(a|e|i|o|u|A|E|I|O|U) v++;
[a-zA-Z] c++;
%%

int main()
{
	yylex();
	printf("There were %d vowels and %d consonents\n",v,c);
	return 0;
}

int yywrap()
{
	return 1;
}
