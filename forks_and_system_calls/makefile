result.out: main.c child_helper.o
	gcc main.c child_helper.o -o result.out

child_helper.o: child_helper.c helper.h
	gcc -c child_helper.c

clean:
	rm -f *.o *.out