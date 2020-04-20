# queue modular test makefile

CFLAGS += -D _MODULAR_TEST
VPATH = ../../   ../list/slink/ 

objects = array_queue.o \
		  slink_queue.o \
		  dlink_queue.o \
		  ../list/slink/slink.o \
		  ../list/dlink/dlink.o \
		  ../../log.o	\

#		 

cc = gcc

testQueue : $(objects)
	cc -o testQueue $(objects)

array_queue.o : array_queue.h
slink_queue.o : slink_queue.h
dlink_queue.o : dlink_queue.h
slink.o : slink.h
dlink.o : dlink.h
log.o 	: log.h

.PHONY : clean
clean:
	rm $(objects)

