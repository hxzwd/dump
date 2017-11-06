#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


int print_msg(char *msg)
{
	FILE *fd;
	fd = fopen("tmp_file.txt", "w+");

	if(fd == NULL)
	{
		return 0;
	}

	fprintf(fd, "%s\n", msg);
	fclose(fd);

	return 1;
}

int main(int argc, char **argv)
{
	
	char *message;
	if(argc != 2)
	{
		printf("Usage: %s <message>\n", argv[0]);
		exit(1);
	}

	message = argv[1];

	if(!print_msg(message))
	{
		perror("print_msg error");
		exit(1);
	}

	printf("Message printed!\n");

	return 0;

}
