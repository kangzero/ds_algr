# modular test makefile

CFLAGS += -D _MODULAR_TEST
VPATH = 

objects = singly_list_test.o  linkedlist_algorithms.o \
		  singly_list/singly_linkedlist.o  \
		  ../log.o \

cc = gcc

testList : $(objects)
	cc -o testList $(objects)

singly_linkedlist.o 		: singly_linkedlist.h
linkedlist_algorithms.o 	: linkedlist_algorithms.h
singly_list_test.o 			: singly_list_test.c
log.o 						: ../log.h 

.PHONY : clean
clean:
	rm $(objects)
