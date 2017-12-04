
TARGET = dosa
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean dosa

default: $(TARGET)
all: default

clean:
	-rm -f *.o
	-rm -f $(TARGET)

dosa:
	$(CC) $(CFLAGS)  -I../includes denialOfServiceAttack.c ../clientParser.c ../serialize_flight.c ../serialize_plane.c ../serialize_reservation.c ../random.c -o $(TARGET)


.PHONY: all clean
