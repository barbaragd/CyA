IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src
LDIR =../lib

LIBS=-lm

_OBJ = language_t.o main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: language

$(ODIR)/language_t.o: $(ODIR)/language_t.cpp $(IDIR)/language_t.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/language_t.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)		

language: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
