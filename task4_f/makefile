task3: task3c task3s

task3c:
	gcc -c -Wall task3c.c -o task3c.o
	gcc task3c.o -lrt -lpthread -o task3c

task3s:
	gcc -c -Wall task3s.c -o task3s.o
	gcc task3s.o -lrt -lpthread -o task3s

clean:
	rm -rf *.o
	rm -rf task3c
	rm -rf task3s
