P=main
OBJECTS=main.o jobj.o
CC=gcc


$P: $(OBJECTS)
	$(CC) -o $P $(OBJECTS)

.PHONY: clean
clean:
	rm $(OBJECTS) $P
