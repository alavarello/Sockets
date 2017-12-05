TARGET = client
TARGET_TEST = tests
TARGET_ALL = $(TARGET) $(TARGET_TEST)
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra -Wparentheses

.PHONY: default all clean tests

default: $(TARGET)
all: $(TARGET_ALL)
test : $(TARGET_TEST)

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

%.o: %.c 
	$(CC) $(CFLAGS)  -I./includes -c $< -o $@ 

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC)  $(OBJECTS) -Wall -pedantic -Wextra -Wparentheses $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	$(MAKE) -C ./tests clean

$(TARGET_TEST):
	$(MAKE) -C ./tests all


.PHONY: all clean
