#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"



int main(int argc, char **argv)
{
	char *file_name = "tmpfakefile";
	FILE *file_handle;
	errno = 0;

	if((file_handle = fopen(file_name, "rb")) == NULL)
	{
		perror("File handle is NULL: ");
	}
	else
	{
		fclose(file_handle);
	}

	return EXIT_SUCCESS;
}
