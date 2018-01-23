#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr1, *fptr2;
	char filename[100], c1, c2;
	int flg=0;
	printf("Enter the first filename to open for reading: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	// Open one file for reading
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	printf("Enter the second filename to open for reading: \n");
	scanf("%s", filename);
	fptr2 = fopen(filename, "r"); // Open another file for writing
	if (fptr2 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	// Read contents from file
	while ((c1 = fgetc(fptr1)) != EOF && (c2 = fgetc(fptr2)) != EOF)
	{
		if(c1!=c2)
		{
			flg=1;
			break;
		}
	}
	if(flg==1 || ( (c1!=c2) && (c1==EOF || c2==EOF)))
		printf("File contents are different\n");
	else
		printf("File contents are same\n");
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}
