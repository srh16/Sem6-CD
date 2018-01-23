#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr1;
	char filename[100],c;
	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);
	getchar();
	fptr1 = fopen(filename, "r");
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	int lines=0;
	while(1)
	{
		printf("\nQ to QUIT, C to continue: ");
		scanf("%c",&c);
		getchar();
		printf("\n");
		if(c=='q' || c=='Q')
			break;
		lines=0;
		while ((c= fgetc(fptr1)) != EOF)
		{
			if(c=='\n')
				lines++;
			printf("%c",c);
			if(lines==5)
				break;
		}
		if(c==EOF)
			break;
	}
	fclose(fptr1);
	return 0;
}