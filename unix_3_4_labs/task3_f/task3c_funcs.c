#include "task3c.h"

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