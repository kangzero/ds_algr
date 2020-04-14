# modular test makefile

CFLAGS += -D _MODULAR_TEST
VPATH = 

objects = slink_test.o  list_api.o \
		  slink/slink.o  \
		  ../log.o \

cc = gcc

testList : $(objects)
	cc -o testList $(objects)

slink.o 		: slink.h
slink_test.o 	: slink_test.c
list_api.o 		: list_api.h
log.o 			: ../log.h 

.PHONY : clean
clean:
	rm $(objects)
