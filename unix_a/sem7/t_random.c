#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "unistd.h"
#include "time.h"


int main(int argc, char **argv)
{
	char *outputfile = "file_random.txt";
	extern char *optarg;
	extern int opterr;
	extern int optind;
	extern int optopt;
	int c;
	char str_len[32] = {0};
	char str_nlines[32] = {0};
	int len = 256;
	int nlines = 1;

	while((c = getopt(argc, argv, "n:f:l:")) != -1)
	{
		switch(c)
		{
			case 'f':
				outputfile = optarg;
				printf("Output file is %s\n", outputfile);
				break;
			case 'l':
				strcpy(str_len, optarg);
				printf("Output file size is %s\n", str_len);
				break;
			case 'n':
				strcpy(str_nlines, optarg);
				printf("Number of lines in output file is %s\n", str_nlines);
				break;
			case ':':
				printf("-%c without argument\n", optopt);
				break;
			case '?':
				printf("%c - unknown argument\n", optopt);
		}
	}

//	printf("str_len is %s\n", str_len);

	if(strcmp(str_nlines, "1") && strcmp(str_nlines, ""))
	{
		nlines = atoi(str_nlines);
		if(nlines == 0 && nlines != 1)
		{
			printf("Invalid number of lines in output file: %s\n", str_nlines);
			return EXIT_FAILURE;
		}
	}
	if(nlines == 1)
	{
		printf("Use default number of lines in output file: %d\n", nlines);
	}

	if(strcmp(str_len, "256") && strcmp(str_len, ""))
	{
		len = atoi(str_len);
//		printf("Len is %d\n", len);
		if(len == 0 && len != 256)
		{
			printf("Invalid size: %s\n", str_len);
			return EXIT_FAILURE;
		}
	}
	if(len == 256)
	{
		printf("Use default file size: %d\n", len);
	}

	srand(time(NULL));

	FILE *handle;
	int value;
	int i;
	int value_max = 64;
	char chartable[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int charsperline = len / nlines;
	int bytescounter = 0;
	value_max = strlen(chartable);


	handle = fopen(outputfile, "w+");

	if(!handle)
	{
		printf("Can not open file %s\n", outputfile);
		return EXIT_FAILURE;
	}

	for(i = 0; i < len; i++)
	{
		value = rand() % value_max;
//		printf("[%d]\t%d\t%c\n", i, value, chartable[value]);
		fprintf(handle, "%c", chartable[value]);
		bytescounter++;
		if(i != 0 && ((i % charsperline) == 0))
		{
			fprintf(handle, "%c", '\n');
			bytescounter++;
		}
	}

	printf("%d bytes writed in %s\n", bytescounter, outputfile);
	fclose(handle);

	return EXIT_SUCCESS;
}
