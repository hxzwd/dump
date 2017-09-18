#include "stdio.h"

#include "assert.h"


int main(void)
{
	FILE *handle;
	char *file_name = "tmptestfile";

	handle = fopen(file_name, "rb");

	assert(handle);

	fclose(handle);

	return 0;
}
