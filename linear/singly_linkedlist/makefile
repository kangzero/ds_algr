objects = testbench.o singly_linkedlist.o singly_linkedlist_op.o \

cc = gcc

testbench123 : $(objects)
	cc -o testbench $(objects)

tectbench.o : testbench.h
singly_linkedlist.o : singly_linkedlist.h
singly_linkedlist_op.o : singly_linkedlist_op.h

.PHONY : clean
clean :
	rm $(objects)
