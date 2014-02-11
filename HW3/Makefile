main: main.o
	gcc main.o -o myscheduler -O2 -Wall -Wshadow -lpthread
	rm -rf *.o *.gch
main.o: main.c 
	gcc main.c -c 
