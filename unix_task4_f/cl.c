#include "rpc/rpc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"

#define SV_PROG (unsigned long)0x20000011
#define SV_VER (unsigned long)1
#define SV_PROC (unsigned long)1

int main(int argc, char **argv)
{

	if(argc < 3)
	{
		printf("Usage: %s <host> <value>\n", argv[0]);
		exit(1);
	}

	char *arg_value;
	char *answer;
	int status;
	char buf[256] = { 0 };

	arg_value = argv[2];
	status = callrpc(argv[1], SV_PROG, SV_VER, SV_PROC, xdr_wrapstring, &arg_value, xdr_wrapstring, &answer);
	if(status != 0)
	{
		clnt_perrno(status);
		exit(2);
	}

	printf("Input string is %s:\tanswer is %s\n", arg_value, answer);
/*
	if(!strcmp(answer, "ok"))
	{
		printf("in write if\n");
		strcpy(buf, "write");
		status = callrpc(argv[1], SV_PROG, SV_VER, SV_PROC, xdr_wrapstring, &buf, xdr_wrapstring, &answer);
		if(status != 0)
		{
			clnt_perrno(status);
			exit(3);
		}
		printf("Write begin: answer = %s\n", answer);
	}
*/
	return 0;

}
