#include "stdio.h"
#include "stdlib.h"
#include "signal.h"
#include "unistd.h"


void signal_handler_function(int nsignal)
{

	if(nsignal == SIGUSR1)
	{
		printf("SIGUSR1 received\n");
		printf("User action in SIGUSR1: Call exit(1)...\n");
		exit(1);
	}
	else if(nsignal == SIGKILL)
		printf("SIGKILL received\n");
	else if(nsignal == SIGSTOP)
		printf("SIGSTOP received\n");

}



int main(void)
{

	printf("Process pid is %d\n", getpid());

	if(signal(SIGUSR1, signal_handler_function) == SIG_ERR)
	{
		printf("Can not catch SIGUSR1\n");
	}
	if(signal(SIGKILL, signal_handler_function) == SIG_ERR)
	{
		printf("Can not catch SIGKILL\n");
	}
	if(signal(SIGSTOP, signal_handler_function) == SIG_ERR)
	{
		printf("Can not catch SIGSTOP\n");
	}

	while( 1 )
	{
		sleep(1);
	}

	return EXIT_SUCCESS;

}
