#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit() function
#include <math.h>
int main(int argc, char *argv[]) {
	char *c = (char *)malloc(sizeof(char) * 2000);
	FILE *fptr;
	if ((fptr = fopen(argv[1], "r")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}

	ssize_t read;
	size_t  len;

	double std = 0.0, avg = 0.0;
	double sum = 0.0;
	double arr[1024];
	int count = 0;
	// reads text until newline is encountered
	while ((read = getline(&c, &len, fptr)) != -1)
	{
		char temp[100];
		double d;
		char *footer;
		if((footer = strstr(c, "Comm Time")) != NULL)
		{
			int i = 0;
			while(footer[i] != '\n')
			{
				i++;
			}
			footer[i] = '\0';
			d = atof(footer + 10);
			if (d == 0.0)
				break;
			arr[count++] = d;
			sum += d;
		}
	}
	fclose(fptr);
	avg = sum / count;
	int i;
	for(i = 0; i  < count; i++)
	{
		double diff = arr[i] - avg;
		std = std + (diff * diff);
	}
	std = std / count;
	std = sqrt(std);
	avg = avg / 1000000000.0;
	std = std / 1000000000.0;
	printf("%f\t%f\t", avg, std);

	return 0;
}
