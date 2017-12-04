TARGET = client
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean dosa

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

%.o: %.c 
	$(CC) $(CFLAGS)  -I./includes -c $< -o $@ 

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC)  $(OBJECTS) -Wall  $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)

dosa:
	$(MAKE) -C ./tests all


.PHONY: all clean
