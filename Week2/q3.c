#include <stdio.h>
#include <stdlib.h>  
#include <string.h>


int main()
{
	FILE *fa, *fb;
	int ca, cb, i;
	fa = fopen("q2_out.c", "r");
	if (fa == NULL)
	{
		printf("Cannot open file \n");
		exit(0); 
	}
	fb = fopen("q3_out.c", "w");
	ca = getc(fa); 
	char key[9][10]={"if", "else", "int", "float", "char", "while", "return", "void", "for"};
	char keyu[9][10]={"IF", "ELSE", "INT", "FLOAT", "CHAR", "WHILE", "RETURN", "VOID", "FOR"};
	char buf[100];
	while (ca != EOF)
	{
		i=0;
		if(ca=='\"')
		{
			putc(ca,fb);
			cb=getc(fa);
			while(cb!='\"')
			{
				putc(cb,fb);
				cb = getc(fa);	
			}
			putc(cb,fb);
			ca = getc(fa);
			continue;
		}
		while(ca!=' ' && ca!=EOF)
		{
			buf[i++]=ca;
			ca=getc(fa);
		}
		buf[i]='\0';
		int j=0,st=0;
		for(j=0;j<9;j++)
		{
			if(strcmp(buf,key[j])==0)
			{
				fputs(keyu[j],fb),putc(' ',fb);
				st=1;
			}
		}
		if(st==0)
			fputs(buf,fb),putc(' ',fb);
		ca=getc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}

