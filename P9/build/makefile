IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src
#LDIR =../lib

LIBS=-lm

_OBJ = estado_t.o dfa_t.o GR_t.o main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: grammar

$(ODIR)/estado_t.o: $(ODIR)/estado_t.cpp $(IDIR)/estado_t.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/dfa_t.o: $(ODIR)/dfa_t.cpp $(IDIR)/dfa_t.hpp $(IDIR)/estado_t.hpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/GR_t.o: $(ODIR)/GR_t.cpp $(IDIR)/GR_t.hpp $(IDIR)/dfa_t.hpp
	$(CC) -c -o $@ $< $(CFLAGS)	

$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/GR_t.hpp
	$(CC) -c -o $@ $< $(CFLAGS)		

grammar: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~