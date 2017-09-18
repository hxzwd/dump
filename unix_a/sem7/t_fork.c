#include "stdio.h"
#include "stdlib.h"

#include "errno.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"

int main(int argc, char **argv)
{
	int c;
	extern int optopt, optind, opterr;
	extern char *optarg;
	int is_parent;
	pid_t proc_pid;

	is_parent = 0;

	while((c = getopt(argc, argv, "p")) != -1)
	{
		switch(c)
		{
			case 'p':
				is_parent = 1;
				printf("Is parent proccess\n");
				break;
			case '?':
				printf("Invalid argument: %c\n", optopt);
				break;
		}
	}

	int ret_code;
	int status = 0;

	if(!is_parent)
	{
		switch(proc_pid = fork())
		{
			case -1:
				perror("fork");
				exit(1);
				break;
			case 0:
				printf("Child proccess!\n");
				printf("PID is %d\n", getpid());
				printf("PPID is %d\n", getppid());
				printf("Error return code for child: ");
				scanf("%d", &ret_code);
				exit(ret_code);
				break;
			default:
				printf("Parent proccess!\n");
				printf("PID is %d\n", getpid());
				printf("PID of child is %d\n", proc_pid);
				printf("Wait for child call exit()...\n");
				wait(&status);
				printf("Child exit code is %d\n", WEXITSTATUS(ret_code));
				printf("Parent say bye!\n");
				break;
		}
	}


	return 0;
}
