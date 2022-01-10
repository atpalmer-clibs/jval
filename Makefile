P=main
OBJECTS=main.o jobj.o jarr.o jcollection.o
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -I./include/


$P: $(OBJECTS)
	$(CC) $(CFLAGS) -o $P $(OBJECTS)

.PHONY: clean
clean:
	rm $(OBJECTS) $P
