
TARGET = tests
LIBS = -lm
CC = gcc
CFLAGS = -Wall

.PHONY: default all clean tests

default: $(TARGET)
all: default

clean:
	-rm -f *.o
	-rm -f databaseTest
	

tests:
	$(CC) $(CFLAGS)  -I../includes databaseTest.c getTest.c insertTest.c ../reservationAndCancelationManager.c ../flightsTableManager.c ../planesTableManager.c ../semaphores.c  -o databaseTest -lsqlite3
	
.PHONY: all clean

