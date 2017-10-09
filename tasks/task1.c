#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "dirent.h"
#include "signal.h"

extern int errno;

void show_all(void)
{
	int i = 0;
	printf("\n\n");
	for(; i < sys_nerr; i++)
	{
		printf("Code: %d\t Description: %s\n", i, sys_errlist[i]);
	}
	printf("\n\n");

}

void err(int code)
{
	printf("Error code: %d|\t%s\n", code, strerror(code));
}


int main(int argc, char **argv)
{
	char *fn1 = "tmp1.txt";
	char *fn2 = "tmp2.txt";
	char *fn3 = "tmpdir";
	int fd1, fd2, fd3;
	int status;
	char buffer[64] = { 0 };
	pid_t pid = 999999999;


	if(argc >= 2)
	{
		if(!strcmp(argv[1], "-a"))
		{
			show_all();
			return EXIT_SUCCESS;
		}
	}

	fd1 = open(fn1, O_RDONLY | O_EXCL);
	if(fd1 < 0)
	{
		err(errno);
		fd1 = open(fn2, O_CREAT | O_RDONLY, 0666);
	}

	DIR *dir;
	dir = fdopendir(fd1);
	if(dir == NULL)
	{
		err(errno);
	}

	fd2 = open(fn3, O_DIRECTORY);
	if(fd2 < 0)
	{
		err(errno);
	}

	dir = fdopendir(fd2);
	if(dir == NULL)
	{
		err(errno);
	}




	ssize_t n;
	n = read(fd1, (void *)buffer, 128);
	if(n < 0)
	{
		err(errno);
	}

	status = closedir(dir);
	if(status < 0)
	{
		err(errno);
	}
	status = closedir(NULL);
	if(status < 0)
	{
		err(errno);
	}


	status = close(fd1);
	if(status < 0)
	{
		err(errno);
	}
	status = close(-1);
	if(status < 0)
	{
		err(errno);
	}


	status = kill(pid, 2);
	if(status < 0)
	{
		err(errno);
	}


	status = execlp("/", NULL);
	if(status < 0)
	{
		err(errno);
	}

	return 0;
}
