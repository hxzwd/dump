#include "sys/types.h"
#include "sys/msg.h"
#include "sys/ipc.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/un.h"
#include "errno.h"

extern int errno;

int main(int argc, char **argv)
{

	int hclient, sport, mq_id;
	struct sockaddr_in aserv;
	char msgbuf[512];
	key_t ipckey;
	struct
	{
		long type;
		char text[256];
	} mymsg;
	int received;

	sport = 5000;

	hclient = socket(AF_INET, SOCK_STREAM, 0);
	if(hclient < 0)
	{
		perror(strerror(errno));
		exit(1);
	}
	else
	{
		ipckey = hclient;
		printf("IPC key is: %d\n", ipckey);
	}

	aserv.sin_family = AF_INET;
	aserv.sin_addr.s_addr = inet_addr("127.0.0.1");
	aserv.sin_port = htons(sport);

	if(connect(hclient, (struct sockaddr *)&aserv, sizeof(aserv)) < 0)
	{
		perror(strerror(errno));
		exit(1);
	}

	printf("Connected...\n");

	mq_id = msgget(ipckey, 0);
	if(mq_id < 0)
	{
		perror(strerror(errno));
		exit(1);
	}

	printf("Mq ID: %d\n", mq_id);


	received = msgrcv(mq_id, &mymsg, sizeof(mymsg), 0, 0);

	printf("received value: %d\n", received);
	printf("text: %s\n", mymsg.text);

	return 0;

}