#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "memory.h"
#include "math.h"

#include "main.h"


void get_string(char *buffer)
{
	int i = 0;
	char c;
	while((c = getchar()) != '\n')
		buffer[i++] = c;
	buffer[i] = '\0';
}



uint32_t main(void)
{
	char buffer[64];
	char *str;
	str = (char *)malloc(256*sizeof(char));
	if(str == NULL)
	{
		printf("Can not alloc 256 bytes\n");
		return 1;
	}

	printf("hello\n");
	get_string(buffer);
	printf("Buffer: %s\n", buffer);

	strcpy(str, buffer);
	printf("Str: %s\n", str);

	strcat(str, buffer);
	printf("Str: %s\n", str);

	if(!strcmp(str, buffer))
	{
		printf("[1]Strings are equal\n");
	}
	if(!strcmp(str, str))
	{
		printf("[2]String are equal\n");
	}

	printf("strstr(str, buffer): %s\n", strstr(str, buffer));

	char *one_word;
	int counter = 0;
	printf("Source string is %s\n", str);
	one_word = strtok(str, " ,.-;:\t");
	while(one_word != NULL)
	{
		printf("%d:\t%s\n", counter, one_word);
		one_word = strtok(NULL, " ,.-;:\t");
		counter++;
	}

//	strcpy(str, "3.14159265358979323846");
	strcpy(str, "3.1415926535\0");
	printf("Str: %s\n", str);
	printf("strtod(str, NULL): %f\n", strtod(str, NULL));
	sprintf(str, "%.12f\n", M_PI);
	printf("Str: %s\n", str);

	if(str != NULL)
		free(str);
	return 0;
}
