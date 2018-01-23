#include <stdio.h>
#include <stdlib.h>  

int main()
{
	FILE *fa, *fb;
	int ca, cb;
	fa = fopen("q1_out.c", "r");
	if (fa == NULL)
	{
		printf("Cannot open file \n");
		exit(0); 
	}
	fb = fopen("q2_out.c", "w");
	ca = getc(fa); 
	int st=0;
	while (ca != EOF)
	{
		while(ca=='#' && st==0)
		{
			while((ca=getc(fa))!='\n');
			ca=getc(fa);
		} 
		st=1;
		putc(ca,fb);
		ca=getc(fa);		
	}
	
	fclose(fa);
	fclose(fb);
	return 0;
}

