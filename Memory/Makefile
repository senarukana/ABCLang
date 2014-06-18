TARGET = mem.o
CC=gcc
CFLAGS = -c -DDEBUG -Wall
OBJS = memory.o

$(TARGET):$(OBJS)
	ld -r -o $@ $(OBJS)

memory.o: memory.h
	$(CC) $(CFLAGS) $(OBJS)