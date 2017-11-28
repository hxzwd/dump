#include "task3c.h"
/*
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
*/


extern int errno;
int hclient[64] = { 0 };
struct sockaddr_in aclient;
struct sockaddr_in aservers[64];
int hservers[64] = { 0 };
int server_counter;
int status;
pthread_t sthreads[64] = { 0 };


struct mq_attr attr, old_attr;
struct sigevent sev;
mqd_t mqdes;
mqd_t mqdesa[64];
char *mq_name;

int msgid;
int msgflg;
key_t ipckey;
struct msqid_ds qstatus;
/*
struct message
{
	long mtype;
	char mtext[512];
};

void *server_func(void *ptr)
{
	char *msg;
	char buf[512] = { 0 };
	msg = (char *)ptr;
	int id;
	int nbytes;
	struct message Msg;
	unsigned int prio;
	size_t buf_len;
	id = atoi(msg);
	mqd_t mqdes_tmp;
	printf("Server thread func[%d]\n", id);
	while(1)
	{
//		nbytes = read(hclient[id], buf, 512);
		nbytes = recv(hclient[id], buf, 512, 0);
		fflush(stdout);
		printf("From server [id: %d] -> read %d bytes\n", id, nbytes);
		prio = id;
		Msg.mtype = id + 1;
		memset(Msg.mtext, 0, 512);
		strcpy(Msg.mtext, buf);
		buf_len = strlen(buf) + 1;
		// if(msgsnd(msgid, &Msg, sizeof(Msg), 0) < 0)
		// {
		// 	printf("%d\t%d\t%s\t%d\n", msgid, Msg.mtype, Msg.mtext, buf_len);
		// 	perror("msgsnd error in server_func");
		// 	exit(1);
		// }
		mqdes_tmp = mqdesa[id];
//		PRT2("Mqdes_tmp: %d\n", mqdes_tmp);
		if(mq_send(mqdes_tmp, buf, strlen(buf), 0) == -1)
		{
			char tmpbuf[128] = { 0 };
			sprintf(tmpbuf, "Server id: %d\t mq_send error\nMessage: %s\n", id, buf);
			mq_unlink(mq_name);
			perror(tmpbuf);
			exit(1);
		}

	}
}
*/

static void thr_func(union sigval sv)
{
	void *rbuf;
	struct mq_attr attr2;
	ssize_t nr;
	unsigned int rprio;
	int msg_counter;
	int retval;
	mqd_t mqdes2;

	mqdes2 = *((mqd_t *)sv.sival_ptr);
	mq_notify(mqdes, &sev);
	msg_counter = 64;
//	PRT("In thr_func.");
	retval = mq_getattr(mqdes2, &attr2);
	if(retval == -1)
	{
//		mq_close(mqdes2);
		mq_unlink(mq_name);
		perror("mq_getattr in thr_func error");
		exit(1);
	}

	rbuf = malloc(attr2.mq_msgsize);
	if(rbuf == NULL)
	{
//		mq_close(mqdes2);
		mq_unlink(mq_name);
		perror("malloc error in thr_func");	
		exit(1);
	}

	nr = mq_receive(mqdes2, rbuf, attr2.mq_msgsize, NULL);
	if(nr == -1)
	{
//		mq_close(mqdes2);
		mq_unlink(mq_name);
		perror("mq_receive error in thr_func");	
		exit(1);
	}

	printf("Read %d bytes from Queue\n", nr);
	printf("Message: %s\n", (char *)rbuf);
	fflush(stdout);
	free(rbuf);

	
}

void get_str(char *buf)
{
	char c;
	int i = 0;
	while((c = getchar()) != '\n')
		buf[i++] = c;
	buf[i] = '\0';
}


void sig_handler(int sig_num)
{
	printf("Recv signal # %d\n", sig_num);
}


int main(int argc, char **argv)
{
	extern int optopt, optind, opterr;
	extern char *optarg;
	int c;
	char servport[16] = { 0 };
	int sport = 5000;
	char servaddr[16] = { 0 };

	strcpy(servaddr, "127.0.0.1");
	strcpy(servport, "5000");

	char mqname[64] = { 0 };
	int flags;
	mode_t mode;

	if(argc != 2)
	{
		printf("Usage: %s /<mq_name>\n", argv[0]);
		exit(1);
	}
	strcpy(mqname, argv[1]);
	attr.mq_maxmsg = 5;
	attr.mq_msgsize = 512;
	mq_name = mqname;
	flags = O_CREAT | O_EXCL |  O_NONBLOCK | O_RDWR;
	mode = 0666;
	printf("Queue name: %s\n", mq_name);
	printf("Max msgs: %d\n", attr.mq_maxmsg);
	printf("Msg size: %d\n", attr.mq_msgsize);
	mq_unlink(mq_name);
	mqdes = mq_open(mq_name, flags, mode, &attr);
	if(mqdes == (mqd_t)(-1))
	{
		perror("mq_open error in main()");
		exit(1);
	}
	else
	{
		printf("Queue descriptor: %d\n", mqdes);
	}
	PRT("mq_open ok!");
	mq_setattr(mqdes, &attr, 0);
//	signal(SIGUSR2, sig_handler);
	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = thr_func;
	sev.sigev_notify_attributes = NULL;
	sev.sigev_value.sival_ptr = &mqdes;
	if(mq_notify(mqdes, &sev) == -1)
	{
		char tmpbuf[128] = { 0 };
		sprintf(tmpbuf, "mq_notify error: %s\n", strerror(errno));
		mq_unlink(mq_name);
		perror(tmpbuf);
		exit(1);
	}
//	mq_unlink(mq_name);
//	exit(0);

	int counter = 0;
	for(; counter < 64; counter++)
	{
		mqdesa[counter] = mqdes;
	}

	server_counter = 0;

	char cmdbuf[128] = { 0 };

	while(1)
	{
		get_str(cmdbuf);
		if(!strcmp(cmdbuf, "quit") || !strcmp(cmdbuf, "q"))
		{
			int i = 0;
			for(; i < 64; i++)
			{
				if(hclient[i] != 0)
					close(hclient[i]);
				if(sthreads[i] != 0)
				{
					status = pthread_cancel(sthreads[i]);
					if(status != 0)
					{
						char tmpbuf[128] = { 0 };
						sprintf(tmpbuf, "Thread cancel error[%d]\n", i);
						perror(tmpbuf);
						exit(1);
					}
				}
			}
			close(hclient);
//			mq_close(mqdes);
//			mq_unlink(argv[1]);
			mq_unlink(mq_name);
			exit(0);
		}
		if(!strcmp(cmdbuf, "connect") || !strcmp(cmdbuf, "c"))
		{

			hclient[server_counter] = socket(AF_INET, SOCK_STREAM, 0);
			assert(hclient[server_counter]);

			memset(&aservers[server_counter], 0, sizeof(aservers[server_counter]));
			memset(cmdbuf, 0, 128);
			aservers[server_counter].sin_family = AF_INET;
			printf("Address: ");
			get_str(cmdbuf);
			if(!strcmp(cmdbuf, ""))
				status = inet_pton(AF_INET, "127.0.0.1", &aservers[server_counter].sin_addr);
			else
				status = inet_pton(AF_INET, cmdbuf, &aservers[server_counter].sin_addr);
			memset(cmdbuf, 0, 128);
			printf("Port: ");
			get_str(cmdbuf);
			if(!strcmp(cmdbuf, ""))
				aservers[server_counter].sin_port = htons(sport);
			else
				aservers[server_counter].sin_port = htons(atoi(cmdbuf));
			if(connect(hclient[server_counter], (struct sockaddr *)&aservers[server_counter], sizeof(aservers[server_counter])) == -1)
			{
				perror("Connection error");
				close(hclient[server_counter]);
//				mq_close(mqdes);
//				mq_unlink(argv[1]);
				mq_unlink(mq_name);
				exit(1);
			}
			char tmpbuf[128] = { 0 };
			sprintf(tmpbuf, "%d", server_counter);
			status = pthread_create(&sthreads[server_counter], NULL, server_func, (void *)tmpbuf);
			if(status != 0)
			{
				sprintf(tmpbuf, "Error create thread [%d]\n", server_counter);
				perror(tmpbuf);
//				mq_close(mqdes);
//				mq_unlink(argv[1]);
				mq_unlink(mq_name);
				exit(1);
			}
			server_counter++;
		}
		if(!strcmp(cmdbuf, "break") || !strcmp(cmdbuf, "b"))
		{
			break;
		}
		if(!strcmp(cmdbuf, "status"))
		{
			struct mq_attr tmp_attr;
			if(mq_getattr(mqdes, &tmp_attr) < 0)
			{
				perror("msq_getattr error in main() | status func");
				mq_unlink(mq_name);
				exit(1);
			}
			printf("Queue name: %s\n", mq_name);
			printf("Queue id: %d\n", mqdes);
			printf("Max msgs: %d\n", tmp_attr.mq_maxmsg);
			printf("Current msgs : %d\n", tmp_attr.mq_curmsgs);
		}

	}

	// struct mq_attr tmp_attr;
	// while(1)
	// {
	// 	mq_getattr(mqdes, &tmp_attr);
	// 	if(tmp_attr.mq_curmsgs != 0)
	// 		continue;
	// 	else
	// 		break;
	// }

	// char recvbuf[512] = { 0 };
	// unsigned int rprio;
	// int msg_counter;
	// struct mq_attr tmp_attr;
	// msg_counter = 64;

	// while(msg_counter--)
	// {
	// 	mq_getattr(mqdes, &tmp_attr);
	// 	if(tmp_attr.mq_curmsgs != 0)
	// 	{
	// 		printf("Msgs in Queue: %d\n", tmp_attr.mq_curmsgs);
	// 		attr.mq_flags = O_NONBLOCK;
	// 		mq_setattr(mqdes, &tmp_attr, &old_attr);
	// 		while(mq_receive(mqdes, recvbuf, 512, &rprio) != -1)
	// 		{
	// 			printf("Recv msg: %s with prio: %d\n", recvbuf, rprio);
	// 		}

	// 		mq_setattr(mqdes, &old_attr, 0);
	// 	}
	// }

	return 0;

}
