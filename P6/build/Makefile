IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src
LDIR =../lib

LIBS=-lm

_OBJ = estado_t.o dfa_t.cpp main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: dfa

$(ODIR)/estado_t.o: $(ODIR)/estado_t.cpp $(IDIR)/estado_t.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/dfa_t.o: $(ODIR)/dfa_t.cpp $(IDIR)/dfa_t.hpp $(IDIR)/estado_t.hpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/dfa_t.hpp $(IDIR)/estado_t.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)		

dfa: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
