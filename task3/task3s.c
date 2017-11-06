#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/un.h"
#include "unistd.h"
#include "errno.h"
#include "assert.h"
#include "pthread.h"

extern int errno;
int hclients[64] = { 0 };
int hserver;
struct sockaddr_in aserver;
struct sockaddr_in aclients[64];
int aclient_size;
int client_counter;
pthread_t cthreads[64] = { 0 };
int status;

void * client_func(void *ptr)
{
	char *msg;
	int id;
	int nbytes;
	char tmpbuf[512] = { 0 };
	msg = (char *)ptr;
	id = atoi(msg);
	printf("Thread msg(id): %s\n", msg);
	sprintf(tmpbuf, "Some message olololo [for client with id = %d]\n", id);
	nbytes = write(hclients[id], tmpbuf, strlen(tmpbuf));
	printf("write %d bytes -> client [%d]\n", nbytes, id);

}

void get_str(char *buf)
{
	char c;
	int i = 0;
	while((c = getchar()) != '\n')
		buf[i++] = c;
	buf[i] = '\0';
}

int main(int argc, char **argv)
{
	extern int optopt, optind, opterr;
	extern char *optarg;
	int c;
	char servport[16] = { 0 };
	int sport = 5000;

	while((c = getopt(argc, argv, "p:")) != -1)
	{
		switch(c)
		{
			case 'p':
				strcpy(servport, optarg);
				printf("Set server port to %s\n", servport);
				break;
				printf("Is parent proccess\n");
				break;
			case '?':
				printf("Invalid argument: %c\n", optopt);
				break;
		}
	}

	if(strcmp(servport, ""))
	{
		sport = atoi(servport);
	}

	printf("Server port: %d\n", sport);


	

	client_counter = 0;

	hserver = socket(AF_INET, SOCK_STREAM, 0);
	assert(hserver);

	aserver.sin_family = AF_INET;
	aserver.sin_port = htons(sport);
	aserver.sin_addr.s_addr = INADDR_ANY;

	if(bind(hserver, (struct sockaddr *)&aserver, sizeof(aserver)) < 0)
	{
		perror("Bind server error");
		exit(1);
	}

	listen(hserver, 64);
	while(client_counter < 64)
	{
		aclient_size = sizeof(aclients[client_counter]);
		hclients[client_counter] = accept(hserver, (struct sockaddr *)&aclients[client_counter], &aclient_size);
		if(hclients[client_counter] < 0)
		{
			char tmpbuf[128] = { 0 };
			sprintf(tmpbuf, "Accept error[%d]\n", client_counter);
			perror(tmpbuf);
			exit(1);
		}
		char tmpbuf[128] = { 0 };
		sprintf(tmpbuf, "%d", client_counter);
		status = pthread_create(&cthreads[client_counter], NULL, client_func, (void *)tmpbuf);
		if(status != 0)
		{
			sprintf(tmpbuf, "Error create thread [%d]\n", client_counter);
			perror(tmpbuf);
			exit(1);
		}
		client_counter++;
	}

	char cmdbuf[128] = { 0 };
	while(1)
	{
		get_str(cmdbuf);
		if(!strcmp(cmdbuf, "quit") || !strcmp(cmdbuf, "q"))
		{
			int i = 0;
			for(; i < 64; i++)
			{
				if(hclients[i] != 0)
					close(hclients[i]);
				if(cthreads[i] != 0)
				{
					status = pthread_cancel(cthreads[i]);
					if(status != 0)
					{
						char tmpbuf[128] = { 0 };
						sprintf(tmpbuf, "Thread cancel error[%d]\n", i);
						perror(tmpbuf);
						exit(1);
					}
				}
			}
			exit(0);

		}

	}

	return 0;
}


