task3: task3c task3s

task3c.o: task3c.c task3c.h
	gcc -c -Wall task3c.c -o task3c.o

task3c_funcs.o: task3c_funcs.c task3c.h
	gcc -c -Wall task3c_funcs.c -o task3c_funcs.o

task3s.o: task3s.c task3s.h
	gcc -c -Wall task3s.c -o task3s.o

task3s_funcs.o: task3s_funcs.c task3s.h
	gcc -c -Wall task3s_funcs.c -o task3s_funcs.o

task3s: task3s.o task3s_funcs.o
	gcc task3s.o task3s_funcs.o -lrt -lpthread -lsocket -lnsl -o task3s

task3c: task3c.o task3c_funcs.o
	gcc task3c.o task3c_funcs.o -lrt -lpthread -lsocket -lnsl -o task3c


clean:
	rm -rf *.o
	rm -rf task3c
	rm -rf task3s
