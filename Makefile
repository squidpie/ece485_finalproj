CC = gcc
CFLAGS = -g
OBJECTS = cachesim.o traceread.o cache.o L2.o

default: cachesim

cachesim: $(OBJECTS)
	$(CC) $(OBJECTS) -o cachesim

cachesim.o: cachesim.c
	$(CC) -c cachesim.c

cache.o: cache.c cache.h
	$(CC) -c cache.c

traceread.o: traceread.c traceread.h
	$(CC) -c traceread.c

L2.o: L2.c L2.h
	$(CC) -c L2.c

clean:
	rm -rf *.o cachesim
