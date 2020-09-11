objects = agenda.o binarydata.o mainmenu.o registers.o staff_functions.o
headers = contactstruct.h binarydata.h registers.h typedef.h staff_functions.h


all: agenda

agenda: $(objects)
	gcc -o agenda $(objects)

agenda.o: agenda.c $(headers)

binarydata.o: binarydata.c $(headers)

mainmenu.o: mainmenu.c $(headers)

registers.o: registers.c $(headers)

staff_functions.o: staff_functions.c $(headers)


clean:
	rm -f globalVariable.dat
	rm -f contacts.dat
	rm -f agenda
	rm -f *.o
