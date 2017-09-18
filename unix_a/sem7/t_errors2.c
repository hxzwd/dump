#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "errno.h"


int main(int argc, char **argv)
{
	char *file_name = "tmp_test_file";
	FILE *handle;
	int error_num;

	errno = 0;

	handle = fopen(file_name, "rb");
	error_num = errno;

	if(handle)
	{
		fclose(handle);
	}
	else
	{
		char *errorbuf = strerror(error_num);
		fprintf(stderr, "Error[%d]: %s\n", error_num, errorbuf);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
