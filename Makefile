default: cachesim

cachesim: cachesim.o traceread.o
	gcc cachesim.o traceread.o -o cachesim

cachesim.o: cachesim.c
	gcc -c cachesim.c

traceread.o: traceread.c traceread.h
	gcc -c traceread.c

clean:
	rm -rf *.o cachesim
