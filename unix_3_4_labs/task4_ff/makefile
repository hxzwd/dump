task4: sv cl 

#program:
#	gcc -c -Wall program.c -o program.o
#	gcc program.o -o program



cl.o: cl.c
	gcc -c -Wall cl.c -o cl.o

cl: cl.o
	gcc cl.o -o cl

sv.o: sv.c
	gcc -c -Wall sv.c -o sv.o

sv: sv.o
	gcc sv.o -o sv

clean:
	rm -rf *.o
	rm -rf cl
	rm -rf sv
#	rm -rf program
