CFLAGS=-Wall -g

all: ex1 ex3

clean:
	rm -f ex1
	rm -f ex3

ex22: ex22.c ex22_main.c ex22.h dbg.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ ex22.c ex22_main.c $(LDLIBS)
