#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include "time.h"
#include "unistd.h"
#include "fcntl.h"

#define DATA_SIZE 128

int main(void)
{

	int handle;
	int value;
	int max_value;
	int nlines;
	int charsperline;
	char *filename = "t_dup.tmp.txt";
	char *chartable = "abcdefghijklmnopqrstuwxyzABCEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	char data[DATA_SIZE];

	max_value = strlen(chartable);
	charsperline = 16;
	nlines = DATA_SIZE / charsperline;

	srand(time(NULL));

	int i;
	for(i = 0; i < DATA_SIZE; i++)
	{
		if( i != 0 && ( (i % nlines) == 0 ) )
		{
			data[i] = '\n';
		}
		else
		{
			value = rand() % max_value;
			data[i] = chartable[value];
		}
	}

	handle = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if( handle == -1 )
	{
		printf("Can not open file %s\n", filename);
		return 1;
	}

	if( dup2(handle, STDOUT_FILENO) == -1 )
	{
		printf("Error: can not link %s file and STDOUT\n", filename);
		close(handle);
		return 1;
	}

	printf("\n");
	for(i = 0; i < DATA_SIZE; i++)
	{
		printf("%c ", data[i]);
		if( i != 0 && ( (i % nlines) == 0 ) )
		{
			printf("\n");
		}
	}
	printf("\n");

	close(handle);

	return 0;
}
