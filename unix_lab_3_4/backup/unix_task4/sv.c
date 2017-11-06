#include "rpc/rpc.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"


#define SV_PROG (unsigned long)0x20000011
#define SV_VER (unsigned long)1
#define SV_PROC (unsigned long)1

char **proc_func(int *);


int main(int argc, char **argv)
{

	int status;

	status = registerrpc(SV_PROG, SV_VER, SV_PROC, proc_func, xdr_int, xdr_wrapstring);
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

char **proc_func(int *indata_p)
{

	static char *result;
	static char even[] = { "even" };
	static char odd[] = { "odd" };

	printf("Received number: %d\n", *indata_p);

	if(*indata_p % 2 == 0)
	{
		result = odd;
	}
	else
	{
		result = even;
	}

	return &result;

}



