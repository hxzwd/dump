#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "sys/wait.h"


int main(void)
{
	pid_t child_pid, wait_pid;
	int status;
	int i;
	int a[3] = {1, 2, 1};

	status = 0;

	printf("Parent pid is %d\n", getpid());

	for(i = 0; i < 3; i++)
	{
		printf("i is %d\n", i);
		if((child_pid = fork()) == 0)
		{
			printf("In child process (child process pid is %d)\n", getpid());

			if(a[i] < 2)
			{
				printf("Should be accept\n");
				exit(1);
			}
			else
			{
				printf("Should be reject\n");
				exit(0);
			}

		}
	}

	while((wait_pid = wait(&status)) > 0)
	{
		printf("Exit status of %d was %d (%s)\n", (int)wait_pid, status, (status == 0) ? "reject" : "accept");
	}

	return 0;
}
