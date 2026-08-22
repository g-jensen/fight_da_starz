CC=gcc
CFLAGS=-I.
DEPS = $(shell find . -type f -name '*.h')
SRC := $(shell find . -type f -name '*.c')
OBJ = $(SRC:.c=.o)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core *~ 