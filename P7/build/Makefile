IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src
LDIR =../lib

LIBS=-lm

_OBJ = estado_t.o nfa_t.cpp main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: nfa

$(ODIR)/estado_t.o: $(ODIR)/estado_t.cpp $(IDIR)/estado_t.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/dfa_t.o: $(ODIR)/nfa_t.cpp $(IDIR)/nfa_t.hpp $(IDIR)/estado_t.hpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/nfa_t.hpp $(IDIR)/estado_t.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)		

nfa: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
