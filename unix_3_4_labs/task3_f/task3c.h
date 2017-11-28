#ifndef H_TASK3C
#define H_TASK3C

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
#include "mqueue.h"
#include "signal.h"
#include "sys/resource.h"

#include "sys/msg.h"
#include "sys/ipc.h"

#define SIGUSR1 10
#define SIGUSR2 12

#define DEBUG

#ifdef DEBUG
#define PRT(x) printf("%s\n", x)
#define PRT2(x, y) printf(x, y)
#else
#define PRT(x) 
#define PRT2(x, y)
#endif

extern int hclient[64];
extern struct sockaddr_in aclient;
extern struct sockaddr_in aservers[64];
extern int hservers[64];
extern int server_counter;
extern int status;
extern pthread_t sthreads[64];


extern struct mq_attr attr, old_attr;
extern struct sigevent sev;
extern mqd_t mqdes;
extern mqd_t mqdesa[64];
extern char *mq_name;

extern int msgid;
extern int msgflg;
extern key_t ipckey;
extern struct msqid_ds qstatus;

struct message
{
	long mtype;
	char mtext[512];
};

void *server_func(void *ptr);

#endif