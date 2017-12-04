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
FILE *fd;
char *msg_data[64] = { NULL };
int gen_port = 0;

void * client_func(void *ptr)
{
	char *default_data = "[MSG#%d]\nSome message olololo[for client with id = %d]\n";
	char *msg;
	int id;
	int nbytes;
	char tmpbuf[512] = { 0 };
	int cloops = 10;
	int msg_counter = 1;
	msg = (char *)ptr;
	id = atoi(msg);
	printf("Thread msg(id): %s\n", msg);
	while(cloops--)
	{
		if(msg_data[id] == NULL)
		{
			sprintf(tmpbuf, default_data, msg_counter, id);
		}
		else
		{
			sprintf(tmpbuf, "[MSG#%d]\n%s[for client with id = %d]\n", msg_counter, msg_data[id], id);
		}
		nbytes = write(hclients[id], tmpbuf, strlen(tmpbuf));
		printf("Server[port: %d]:write %d bytes -> client [%d]\n", gen_port, nbytes, id);
		sleep(10);
		msg_counter++;
	}
}

void get_str(char *buf)
{
	char c;
	int i = 0;
	while((c = getchar()) != '\n')
		buf[i++] = c;
	buf[i] = '\0';
}

void free_msg_data()
{
	int i = 0;
	for(i = 0; i < 64; i++)
	{
		if(msg_data[i] != NULL)
		{
			free(msg_data[i]);
			msg_data[i] = NULL;
		}
	}
}

int main(int argc, char **argv)
{
	extern int optopt, optind, opterr;
	extern char *optarg;
	int c;
	char servport[16] = { 0 };
	int sport = 5000;

	char data_file[128] = { 0 };

	while((c = getopt(argc, argv, "p:f:")) != -1)
	{
		switch(c)
		{
			case 'p':
				strcpy(servport, optarg);
				printf("Set server port to %s\n", servport);
				break;
				printf("Is parent proccess\n");
				break;
			case 'f':
				strcpy(data_file, optarg);
				printf("Set data file to %s\n", data_file);
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

	gen_port = sport;

	if(!strcmp(data_file, ""))
	{
		printf("Use default data for sending\n");
	}
	if(!strcmp(data_file, "std"))
	{
		printf("Use data/messages.txt data for sending\n");
		strcpy(data_file, "data/messages.txt");
	}

	if(strcmp(data_file, ""))
	{
		fd = fopen(data_file, "r");
		if(fd == NULL)
		{
			perror(strerror(errno));
			exit(1);
		}
		int i = 0;
		char tmp_buffer[256];
		for(; i < 64; i++)
		{
			fgets(tmp_buffer, 256, fd);
			if(tmp_buffer == NULL)
			{
				break;
			}
			msg_data[i] = malloc(256*sizeof(char));
			strcpy(msg_data[i], tmp_buffer);
			msg_data[strlen(tmp_buffer) - 1] = ' ';

		}
		fclose(fd);
	}

	client_counter = 0;

	hserver = socket(AF_INET, SOCK_STREAM, 0);
	assert(hserver);

	aserver.sin_family = AF_INET;
	aserver.sin_port = htons(sport);
	aserver.sin_addr.s_addr = INADDR_ANY;

	if(bind(hserver, (struct sockaddr *)&aserver, sizeof(aserver)) < 0)
	{
		perror("Bind server error");
		free_msg_data();
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
			free_msg_data();
			exit(1);
		}
		char tmpbuf[128] = { 0 };
		sprintf(tmpbuf, "%d", client_counter);
		status = pthread_create(&cthreads[client_counter], NULL, client_func, (void *)tmpbuf);
		if(status != 0)
		{
			sprintf(tmpbuf, "Error create thread [%d]\n", client_counter);
			perror(tmpbuf);
			free_msg_data();
			exit(1);
		}
		client_counter++;
	}

	char cmdbuf[128] = { 0 };
	while(1)
	{
		get_str(cmdbuf);
		if(!strcmp(cmdbuf, "showd") || !strcmp(cmdbuf, "s"))
		{
			int i = 0;
			for(; i < 64; i++)
			{
				if(msg_data[i] == NULL)
					break;
				printf("Id[%d]:\t%s\n", i, msg_data);
			}
			continue;
		}
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
						free_msg_data();
						exit(1);
					}
				}
			}
			free_msg_data();
			exit(0);

		}

	}

	free_msg_data();

	return 0;
}


