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
	int hserv, hclient, sport, socklen;
	struct sockaddr_in aserv, aclient;
	char msgbuf[512];
	char *sockpath = "server.socket";
	key_t ipckey;
	int mq_id;
	struct
	{
		long type;
		char text[256];
	} mymsg;


	sport = 5000;

	memset(&aserv, 0, sizeof(struct sockaddr_in));
	aserv.sin_family = AF_INET;
	aserv.sin_addr.s_addr = INADDR_ANY;
	aserv.sin_port = htons(sport);
//	strncpy(aserv.sin_path, sockpath, sizeof(aserv.sin_path));
	hserv = socket(AF_INET, SOCK_STREAM, 0);
	if(hserv < 0)
	{
		perror(strerror(errno));
		return 1;
	}
	else
	{
		ipckey = hserv;
	}

	bind(hserv, (struct sockaddr *)&aserv, sizeof(struct sockaddr_in));

	printf("Binded...\n");
	printf("IPC key is %d\n", ipckey);

	mq_id = msgget(ipckey, IPC_CREAT | 0666);
	if(mq_id < 0)
	{
		perror(strerror(errno));
		exit(1);
	}

	printf("Mq ID: %d\n", mq_id);


	listen(hserv, 8);

	printf("Waiting for clients...\n");

	socklen = sizeof(struct sockaddr_in);
	hclient = accept(hserv, (struct sockaddr *)&aclient, (socklen_t *)&socklen);
	if(hclient < 0)
	{
		perror(strerror(errno));
		return 1;
	}


	memset(mymsg.text, 0, 256);
	strcpy(mymsg.text, "MESSAGE SDLFKS:DLFK");
	mymsg.type = 1;
	msgsnd(mq_id, &mymsg, sizeof(mymsg), 0);

	getchar();

	close(hclient);
	close(hserv);

	return 0;

}


