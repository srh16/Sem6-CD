#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fa, *fb;
	int ca, cb;
	fa = fopen("sol_out.c", "r");
	if (fa == NULL)
	{
		printf("Cannot open file \n");
		exit(0); 
	}
	fb = fopen("q1_out.c", "w");
	ca = getc(fa); 
	while (ca != EOF)
	{
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
		int st=0;
		while(ca==' ' || ca=='\t')
		{
			st=1;
			ca = getc(fa);
		}		
		if(st)
			putc(' ',fb);
		putc(ca,fb);
		ca = getc(fa);
		
	}
	fclose(fa);
	fclose(fb);
	return 0;
}

