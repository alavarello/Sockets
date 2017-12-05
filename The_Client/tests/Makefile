
TARGET = tests
LIBS = -lm
CC = gcc
CFLAGS = -Wall

.PHONY: default all clean tests

default: $(TARGET)
all: default

clean:
	-rm -f *.o
	-rm -f denialOfServiceAttack
	-rm -f controllerTests
	-rm -f expressionsTests

$(TARGET):
	$(CC) $(CFLAGS)  -I../includes denialOfServiceAttack.c ../clientParser.c ../serialize_flight.c ../serialize_plane.c ../serialize_reservation.c ../random.c -o denialOfServiceAttack
	$(CC) $(CFLAGS)  -I../includes expressionsTest.c ../expressions.c ../client.c ../clientParser.c ../serialize_flight.c ../serialize_plane.c ../serialize_reservation.c -o expressionsTests
	$(CC) $(CFLAGS)  -I../includes controllerTests.c ../controller.c ../expressions.c ../client.c ../adminMenu.c ../clientParser.c ../serialize_flight.c ../serialize_plane.c ../serialize_reservation.c ../frontEnd.c ../freeMemory.c ../flightInfo.c ../clientMenu.c ../getnum2.c -o controllerTests

.PHONY: all clean


