.RECIPEPREFIX = >
CC = gcc
CFLAGS = -I. -O3

DEPS = get_escapes.h get_params.h structs.h write_data.h
ODIR = obj
LIBS = -lm

_OBJ = main.o get_escapes.o get_params.o write_data.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
> $(CC) -c -o $@ $< $(CFLAGS)
mandelplot: $(OBJ)
> $(CC) -o $@ $^ $(LIBS)

.PHONY: clean

clean: 
> rm -f $(ODIR)/*.o mandelplot
