
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

tests:
	$(CC) $(CFLAGS)  -I../includes denialOfServiceAttack.c ../clientParser.c ../serialize_flight.c ../serialize_plane.c ../serialize_reservation.c ../random.c -o denialOfServiceAttack
	$(CC) $(CFLAGS)  -I../includes expressionsTest.c ../expressions.c ../client.c ../clientParser.c ../serialize_flight.c ../serialize_plane.c ../serialize_reservation.c -o expressionsTests
	
.PHONY: all clean


