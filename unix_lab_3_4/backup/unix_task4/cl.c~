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

	int arg_value;
	char *answer;
	int status;

	arg_value = strlen(argv[2]);
	status = callrpc(argv[1], SV_PROG, SV_VER, SV_PROC, xdr_int, &arg_value, xdr_wrapstring, &answer);
	if(status != 0)
	{
		clnt_perrno(status);
		exit(2);
	}


	printf("Num of letters in %s  is %d: answer = %s\n", argv[2], arg_value, answer);
	
	return 0;

}
