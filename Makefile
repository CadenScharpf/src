IDIR =./
CC=g++-7
CFLAGS= -g -I/

ODIR=./

_DEPS = inputbuf.h lexer.h grammar.h parser.h sets.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = project3.o inputbuf.o lexer.o grammar.o sets.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

a.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 