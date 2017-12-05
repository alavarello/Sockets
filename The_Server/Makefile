TARGET = server
TARGET_TEST = test
TARGET_ALL = $(TARGET) $(TARGET_TEST)
LIBS = -lm -lsqlite3 -lpthread
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: $(TARGET_ALL)
test : $(TARGET_TEST)

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

%.o: %.c 
	$(CC) $(CFLAGS)  -I./includes -c $< -o $@ 

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC)  $(OBJECTS) -Wall  $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	$(MAKE) -C ./tests clean
	
$(TARGET_TEST):
	$(MAKE) -C ./tests all


.PHONY: all clean
