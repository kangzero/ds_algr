# modular test makefile
CFLAGS += -D _MODULAR_TEST
VPATH = /singly_list

objects = linkedlist_test.o  linkedlist_algorithms.o \
		  singly_list/singly_linkedlist.o  \

cc = gcc

testList : $(objects)
	cc -o testList $^

singly_linkedlist.o 		: singly_linkedlist.h
linkedlist_algorithms.o 	: linkedlist_algorithms.h
linkedlist_test.o 			: linkedlist_test.c

.PHONY : clean
clean:
	rm $(objects)
