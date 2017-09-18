#include "stdlib.h"
#include "stdio.h"


int main(void)
{
	char *env_name = "PATH";
	char *env_buffer;

	env_buffer = getenv(env_name);

	if(env_buffer != NULL)
	{
		printf("Variable[$%s] = %s\n", env_name, env_buffer);
	}

	return 0;
}
