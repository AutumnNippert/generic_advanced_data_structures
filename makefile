CC=gcc
CFLAGS= -g -Wall -ffloat-store

all: tests

linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c -o linked_list.o

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c -o stack.o

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c -o queue.o

tests: tests.c linked_list.o stack.o queue.o
	$(CC) $(CFLAGS) tests.c linked_list.o stack.o queue.o -o tests

clean:
	rm *.o linked_list stack queue tests vgcore.*