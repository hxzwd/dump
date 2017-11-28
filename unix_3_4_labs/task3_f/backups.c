//########################################################################################
//client
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
	ipckey = 20;
	ipckey = ftok(argv[0], 1337);
	printf("IPC KEY: %d\n", ipckey);
//	msgflg = 0666;
	msgid = msgget(ipckey, IPC_CREAT | 0666);
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
//########################################################################################


//########################################################################################
//client
	int ncurrmsg;
	struct message Msg;
	int received;
	int main_loop;

	main_loop = 4;
	memset(Msg.mtext, 0, 512);


//	while(main_loop--)
	while(1)
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
			printf("#######################################\n");
			printf("Received value: %d\n", received);
			printf("Message: %s\n", Msg.mtext);
			printf("From server with id = %d\n", Msg.mtype);
			printf("#######################################\n");
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

//########################################################################################

//########################################################################################
//client
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
//		nbytes = read(hclient[id], buf, 512);
		nbytes = recv(hclient[id], buf, 512, 0);
		fflush(stdout);
		printf("From server [id: %d] -> read %d bytes\n", id, nbytes);
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
//########################################################################################



//########################################################################################
//client



//########################################################################################