CC = g++
CFLAGS = -std=c++11

nbody: nBodyInt.o main.o 
	$(CC) $(CFLAGS) -o nbody nBodyInt.o main.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

nBodyInt.o: nBodyInt.cpp nBodyInt.h
	$(CC) $(CFLAGS) -c nBodyInt.cpp

clean: 
	\rm *.o  
