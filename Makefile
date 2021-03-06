CC = gcc
CFLAGS = -g
OBJECTS = cachesim.o traceread.o cache.o L2.o debug.o cachestats.o lru.o

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

debug.o: debug.c debug.h
	$(CC) -c debug.c

cachestats.o: cachestats.c cachestats.h
	$(CC) -c cachestats.c

lru.o: lru.c lru.h
	$(CC) -c lru.c

L2_test.o: L2_test.c 
	$(CC) -c L2_test.c

l2_test: L2.o L2_test.o 
	$(CC) L2.o L2_test.o -o l2_test
	
clean:
	rm -rf *.o cachesim
