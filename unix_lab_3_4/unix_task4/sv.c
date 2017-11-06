#include "rpc/rpc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "sys/types.h"
#include "signal.h"
#include "unistd.h"

#define SV_PROG (unsigned long)0x20000011
#define SV_VER (unsigned long)1
#define SV_PROC (unsigned long)1

char **proc_func(char **);

pid_t server_pid;

int main(int argc, char **argv)
{

	int status;

	server_pid = getpid();
	printf("Server PID: %d\n", server_pid);

	status = registerrpc(SV_PROG, SV_VER, SV_PROC, proc_func, xdr_wrapstring, xdr_wrapstring);
	if(status == -1)
	{
		perror("registerrpc error in main func of server");
		exit(1);
	}

	svc_run();

	perror("return from svc_run in main func of server");
	exit(1);

	return 0;
}

char **proc_func(char **indata_p)
{

	static char *result;
	static char even[] = { "even" };
	static char odd[] = { "odd" };
	static char ok_result[] = { "ok" };
	static char bad_result[] = { "err" };
	static char ok_write[] = { "write_ok" };
	static char *data_part;
	static char filename[128] = { 0 };
	static char fileoff[128] = { 0 };
	static char datasize[128] = { 0 };
	static int write_mode = 0;
	char tmp_buf[512] = { 0 };

//	memcpy(tmp_buf, &(*indata_p[1]), 5*sizeof(char));

	if(!strcmp(*indata_p, "write") && write_mode == 0)
	{
		write_mode = 1;
		result = ok_result;
		printf("Received string[wr/mode is %d]: %s\n", write_mode, *indata_p);
		return &result;
	}

	if(!strcmp(*indata_p, "nowrite") && write_mode == 1)
	{
		write_mode = 0;
		result = ok_result;
		printf("Received string[wr/mode is %d]: %s\n", write_mode, *indata_p);
		return &result;
	}

	printf("Received string[wr/mode is %d]: %s\n", write_mode, *indata_p);

	if(write_mode)
	{
//		printf("In write mode\n");
		FILE *fd;
		int ds;
		int foff;
//		printf("atoi datasize\n");
		ds = atoi(datasize);
//		printf("atoi fileoff\n");
		foff = atoi(fileoff);
		fd = fopen(filename, "a+");

		fsetpos(fd, &foff);

		fprintf(fd, "%s", *indata_p);

		fclose(fd);

		result = ok_write;
		return &result;

	}

	if(!write_mode)
	{
		memset(filename, 0, 128);
		memset(fileoff, 0, 128);
		memset(datasize, 0, 128);


/*
	if(!strcmp(*indata_p, "cmd:kill"))
	{
		printf("Close server...\n");
		exit(1);
	}
*/
	data_part = strtok(*indata_p, ",");
	if(data_part != NULL)
	{
		strcpy(filename, data_part);
		data_part = strtok(NULL, ",");
		if(data_part != NULL)
		{
			strcpy(fileoff, data_part);
			data_part = strtok(NULL, ",");
			if(data_part != NULL)
			{
				strcpy(datasize, data_part);
			}
			else
			{
				result = bad_result;
			}
		}
		else
		{
			result = bad_result;
		}
	}
	else
	{
		result = bad_result;
	}

	if(!strcmp(filename, "") || !strcmp(fileoff, "") || !strcmp(datasize, ""))
	{
		result = bad_result;
	}
	else
	{
		printf("File name: %s\n", filename);
		printf("File offset: %s\n", fileoff);
		printf("Data size: %s\n", datasize);
		result = ok_result;
	}
	}
/*
	if(*indata_p[0] == 'o')
	{
		result = odd;
	}
	else
	{
		result = even;
	}
*/
	return &result;

}



