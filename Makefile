CC = g++
DEBUG = -g -O0 -pedantic-errors
CFLAGS = -Wall -std=c++14 -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) -o
FNAME = term
ONAME = term
DOT_O = $(FNAME).o clientManager.o

default: $(DOT_O)
	$(CC) $(LFLAGS) term term.o
	ln -s term harambash

$(FNAME).o:
	$(CC) $(CFLAGS) $(FNAME).cpp

clientManager.o:
	$(CC) $(CFLAGS) clientManager.cpp
	
run:
	$./term

clean:
	rm -f $(DOT_O)
	rm -f term
	rm -f harambash
