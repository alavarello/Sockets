TARGET = client
TARGET_TEST = clientTests
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -pedantic -Wextra -Wparentheses

.PHONY: default all clean dosa

default: $(TARGET)
all: default
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

dosa:
	$(MAKE) -C ./tests all


.PHONY: all clean
