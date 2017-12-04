#ifndef H_TASK3S
#define H_TASK3S

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


extern int hclients[64];
extern int hserver;
extern struct sockaddr_in aserver;
extern struct sockaddr_in aclients[64];
extern int aclient_size;
extern int client_counter;
extern pthread_t cthreads[64];
extern int status;
extern FILE *fd;
extern char *msg_data[64];
extern int gen_port;


void * client_func(void *ptr);

#endif