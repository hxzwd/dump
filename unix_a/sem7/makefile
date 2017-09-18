.PHONY=clean all all2
CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
ALLTARGETS=t_errors
SOURCES=t_errors.c t_errors2.c t_assert.c t_time.c t_envs.c t_random.c t_fork.c t_fork2.c

all: $(ALLTARGETS)

all2: $(SOURCES)
	for arg in $(SOURCES);\
		#do echo $$arg;\
		do target=`(echo $$arg | grep -e "^[^/.]*" -o)`;\
		obj_target=$$target.o;\
		#echo $$obj_target;\
		echo $$arg -> $$obj_target;\
		$(CC) $(CFLAGS) $$arg -o $$obj_target;\
		echo $$obj_target -> $$target;\
		$(CC) $(LDFLAGS) $$obj_target -o $$target;\
	done	
	
	

t_errors: t_errors.o
	$(CC) $(LDFLAGS) t_errors.o -o t_errors	

t_errors.o: t_errors.c
	$(CC) $(CFLAGS) t_errors.c -o t_errors.o

clean:
	rm -rf *.o
