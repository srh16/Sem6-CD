#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr1;
	char filename[100], c;
	int cnt=0;
	while(cnt<3)
	{
		printf("Enter the filename to open for reading: \n");
		scanf("%s", filename);
		fptr1 = fopen(filename, "r");
		if (fptr1 == NULL)
		{
			printf("Cannot open file %s \n", filename);
			cnt++;
		}
		else
		{
			fclose(fptr1);
			exit(0);
		}
	}
	return 0;
}