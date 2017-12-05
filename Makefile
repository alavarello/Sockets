
TARGET = project

LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra -Wparentheses

.PHONY: default all clean tests

default: $(TARGET)
all: $(TARGET)


OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

%.o: %.c 
	$(CC) $(CFLAGS)  -I./includes -c $< -o $@ 

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): 
	$(MAKE) -C ./The_Client all
	$(MAKE) -C ./The_Server all

clean:
	$(MAKE) -C ./The_Client clean
	$(MAKE) -C ./The_Server clean

.PHONY: all clean
