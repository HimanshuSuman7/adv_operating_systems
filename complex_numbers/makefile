result.out: main.c threads.o
	gcc -g -pthread main.c threads.o -o result.out

threads.o: threads.c project.h
	gcc -c threads.c

clean:
	rm -f *.o *.out