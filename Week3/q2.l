%{
int w=0,c=0,b=0,l=0;
%}

%%
[\n] {l++;w++;}
[\t" "] {b++;w++;}
[^\n\t] {c++;}
%%

int main()
{
	yylex();
	printf("There were %d words, %d characters, %d blanks and %d lines\n",w,c,b,l);
	return 0;
}

int yywrap()
{
	return 1;
}
