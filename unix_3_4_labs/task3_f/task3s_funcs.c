#include "task3s.h"

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