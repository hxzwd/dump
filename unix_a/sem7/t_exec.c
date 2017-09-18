#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include "unistd.h"


void strtrim(char *str)
{
	char *dest = str;
	char *src = str;
	char *end;

	while( isspace((unsigned char)(*src)) )
	{
		src++;
	}

	end = strlen(src) + src - 1;

	while( end > src && isspace((unsigned char)(*end)) )
	{
		*end = 0;
		end--;
	}

	if( src != dest )
	{
		while( (*dest++) = (*src++) );
	}
}

int main(int argc, char **argv)
{
	int c;
	extern int optopt, optind, opterr;
	extern char *optarg;
	char progname[64] = {0};
	char progargs[128] = {0};

	while((c = getopt(argc, argv, "p:a:")) != -1)
	{
		switch(c)
		{
			case 'p':
				strcpy(progname, optarg);
				printf("Set rogramm name to %s\n", progname);
				break;
			case 'a':
				strcpy(progargs, optarg);
				printf("Set programm arguments in %s\n", progargs);
				break;
			case ':':
				printf("-%c invalid parameter\n", optopt);
				break;
			case '?':
				printf("Invalud option: %c\n", optopt);
				break;
		}
	}

	if(!strcmp(progname, ""))
	{
		printf("Empty programm name!\n");
		return EXIT_FAILURE;
	}

	printf("Programm name is %s\n", progname);

	char *word;
	char *pargv[16];
	int i;
	int numofargs;

	for(i = 0; i < 16; i++)
	{
		pargv[i] = NULL;
	}
//	pargv[0] = (char *)malloc(sizeof(char) * strlen(progname));
//	strcpy(pargv[0], progname);
	pargv[0] = (char *)progname;
	if(strcmp(progargs, ""))
	{
		printf("Programm arguments is %s\n", progargs);

		word = strtok(progargs, ",");
		if( word != NULL )
		i = 1;
		while( word != NULL )
		{
			strtrim(word);
			if( word != NULL )
			{
				pargv[i] = (char *)malloc(sizeof(char) * strlen(word));
				strcpy(pargv[i], word);
			}
//			printf("Arg[%d]:\t%s\n", i, word);
			i++;
			word = strtok(NULL, ",");
		}
		numofargs = i + 1;
		printf("Num of programm arguments is %d\n", numofargs);
		for(i = 0; i < numofargs; i++)
		{
			printf("pargv[%d] = %s\n", i, pargv[i]);
		}
	}
	else
	{
		printf("Programm arguments is empty\n", progargs);
	}

	execv(progname, pargv);

	for(i = 0; i < numofargs; i++)
	{
		if( pargv[i] == NULL )
			free(pargv[i]);
	}

	return EXIT_SUCCESS;

}
