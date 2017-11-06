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

#include "sys/msg.h"
#include "sys/ipc.h"

#define SIGUSR1 10
#define SIGUSR2 12

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
char *mq_name;

int msgid;
int msgflg;
key_t ipckey;

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
	printf("Server thread func[%d]\n", id);
	while(1)
	{
		nbytes = read(hclient[id], buf, 512);
		printf("server [%d] -> read %d bytes\n", id, nbytes);
		prio = id;
		Msg.mtype = id + 1;
		memset(Msg.mtext, 0, 512);
		strcpy(Msg.mtext, buf);
		buf_len = strlen(buf) + 1;
		if(msgsnd(msgid, &Msg, sizeof(Msg), 0) < 0)
		{
			printf("%d\t%d\t%s\t%d\n", msgid, Msg.mtype, Msg.mtext, buf_len);
			perror("msgsnd error in server_func");
			exit(1);
		}
/*		if(mq_send(mqdes, buf, 4, prio) == -1)
		{
			char tmpbuf[128] = { 0 };
			sprintf(tmpbuf, "Server id: %d\t mq_send error\n", id);
			mq_close(mqdes);
			mq_unlink(mq_name);
			perror(tmpbuf);
			exit(1);
		}
*/
	}
}

void thr_func(union sigval sv)
{
	void *rbuf;
	struct mq_attr attr2;
	ssize_t nr;
	unsigned int rprio;
	int msg_counter;
	int retval;
	mqd_t mqdes2;

	mqdes2 = *((mqd_t *)sv.sival_ptr);
	msg_counter = 64;

	retval = mq_getattr(mqdes2, &attr2);
	if(retval == -1)
	{
		mq_close(mqdes2);
		mq_unlink(mq_name);
		perror("mq_getattr in thr_func error");
		exit(1);
	}

	rbuf = malloc(attr2.mq_msgsize);
	if(rbuf == NULL)
	{
		mq_close(mqdes2);
		mq_unlink(mq_name);
		perror("malloc error in thr_func");	
		exit(1);
	}

	nr = mq_receive(mqdes2, rbuf, attr2.mq_msgsize, NULL);
	if(nr == -1)
	{
		mq_close(mqdes2);
		mq_unlink(mq_name);
		perror("mq_receive error in thr_func");	
		exit(1);
	}

	printf("Read %d bytes from MQ\n", nr);
	printf("Message: %s\n", (char *)rbuf);

	free(rbuf);

	return 0;
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

/*
	if(argc != 2)
	{
		printf("Usage: %s /<mq_name>\n", argv[0]);
		exit(1);
	}
	strcpy(mqname, argv[1]);
	attr.mq_maxmsg = 300;
	attr.mq_msgsize = 512;
	attr.mq_flags = 0;
	attr.mq_curmsgs = 0;
	mq_name = mqname;
	flags = O_RDWR | O_CREAT;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	mqdes = mq_open(mqname, flags, mode, &attr);
	if(mqdes == (mqd_t)(-1))
	{
		perror("mq_open error in main");
		exit(1);
	}
//	mq_setattr(mqdes, &attr, 0);
	signal(SIGUSR2, sig_handler);
	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = thr_func;
	sev.sigev_notify_attributes = NULL;
	sev.sigev_value.sival_ptr = &mqdes;
	if(mq_notify(mqdes, &sev) == -1)
	{
		char tmpbuf[128] = { 0 };
		sprintf(tmpbuf, "mq_notify error: %s\n", strerror(errno));
		perror(tmpbuf);
		exit(1);
	}
*/
	struct msqid_ds qstatus;
	msgflg = O_CREAT | 0666;
//	ipckey = ftok("qtmp", 42);
//	ipckey = ftok("qtmp", 0);
	ipckey = 10;
	printf("IPC KEY: %d\n", ipckey);
	msgflg = 0666;
	msgid = msgget(ipckey, msgflg);
	printf("Msg ID: %d\n", msgid);

//	msgid = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL);

	if(msgid == -1)
	{
		perror("msgget error in main func");
		exit(1);
	}
/*	if(msgctl(msgid, IPC_STAT, &qstatus) < 0)
	{
		perror("msgctl error in main func");
		exit(1);
	}
*/

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
//			close(hclient);
//			mq_close(mqdes);
//			mq_unlink(argv[1]);
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
				mq_close(mqdes);
				mq_unlink(argv[1]);
				exit(1);
			}
			char tmpbuf[128] = { 0 };
			sprintf(tmpbuf, "%d", server_counter);
			status = pthread_create(&sthreads[server_counter], NULL, server_func, (void *)tmpbuf);
			if(status != 0)
			{
				sprintf(tmpbuf, "Error create thread [%d]\n", server_counter);
				perror(tmpbuf);
				mq_close(mqdes);
				mq_unlink(argv[1]);
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
			if(msgctl(msgid, IPC_STAT, &qstatus) < 0)
			{
				perror("msgctl error in main func");
				exit(1);
			}
			printf("%d id queue\n", msgid);
			printf("%d messages in queue\n", qstatus.msg_qnum);
		}

	}


	int ncurrmsg;
	struct message Msg;
	int received;
	int main_loop;

	main_loop = 4;
	memset(Msg.mtext, 0, 512);


	while(main_loop--)
	{

		if(msgctl(msgid, IPC_STAT, &qstatus) < 0)
		{
			perror("msgctl error in main func");
			exit(1);
		}

		ncurrmsg = qstatus.msg_qnum;
		if(ncurrmsg != 0)
		{
			received = msgrcv(msgid, &Msg, sizeof(Msg), 0, MSG_NOERROR);
			printf("Received value: %d\n", received);
			printf("Message: %s\n", Msg.mtext);
		}


	}

/*
	char recvbuf[512] = { 0 };
	unsigned int rprio;
	int msg_counter;
	msg_counter = 64;

	while(msg_counter--)
	{
		mq_getattr(mqdes, &attr);
		if(attr.mq_curmsgs != 0)
		{
			printf("Msgs in mq: %d\n", attr.mq_curmsgs);
			attr.mq_flags = O_NONBLOCK;
			mq_setattr(mqdes, &attr, &old_attr);
			while(mq_receive(mqdes, recvbuf, 512, &rprio) != -1)
			{
				printf("Recv msg: %s with prio: %d\n", recvbuf, rprio);
			}

			mq_setattr(mqdes, &old_attr, 0);
		}
	}
*/
	return 0;

}