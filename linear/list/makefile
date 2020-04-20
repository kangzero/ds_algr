# modular test makefile

CFLAGS += -D _MODULAR_TEST
VPATH = ../../ 

objects = list_test.o  list_api.o \
		  slink/slink.o \
		  dlink/dlink.o \
		  staticlist/staticlist.o \
		  ../../log.o \

cc = gcc

testList : $(objects)
	cc -o testList $(objects)

slink.o 		: slink.h
dlink.o 		: dlink.h
staticlist.o 	: staticlist.h
list_test.o 	: list_test.c
list_api.o 		: list_api.h
log.o 			: ../log.h 

.PHONY : clean
clean:
	rm $(objects)
