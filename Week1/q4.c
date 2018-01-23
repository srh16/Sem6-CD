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
	fseek(fptr1,0,SEEK_SET);
	int pos1=ftell(fptr1);
	fseek(fptr1,0,SEEK_END);
	int pos2=ftell(fptr1);
	printf("Size of file is =%d\n",pos2-pos1);
	return 0;
}