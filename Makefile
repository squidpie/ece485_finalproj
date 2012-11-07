CC = gcc
CFLAGS = -g
OBJECTS = cachesim.o traceread.o cache.o

default: cachesim

cachesim: $(OBJECTS)
	$(CC) $(OBJECTS) -o cachesim

cachesim.o: cachesim.c
	$(CC) -c cachesim.c

cache.o: cache.c cache.h
	$(CC) -c cache.c

traceread.o: traceread.c traceread.h
	$(CC) -c traceread.c

clean:
	rm -rf *.o cachesim
