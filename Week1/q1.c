#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr1;
	char filename[100], c;
	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	int lines=0,ch=0;
	while ((c= fgetc(fptr1)) != EOF)
	{
		if(c=='\n')
			lines++;
		else if(c!='\n' && c!='\r' && c!='\t')
			ch++;
	}
	printf("\nCharacters= %d\nLines= %d\n", ch,lines);
	fclose(fptr1);
	return 0;
}