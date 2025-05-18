flags = -Wall -g
cc = g++ $(flags)
ifeq ($(OS),Windows_NT)
	e = .exe
	del = del /Q
else
	e = 
	del = rm -f
endif

all: DCI clean

DCI: main.o libmenu.o
	$(cc) -o drawscii$(e) main.o libmenu.o

main.o:
	$(cc) -c main.cpp

libmenu.o:
	$(cc) -c libmenu.cpp

clean:
	$(del) *.o