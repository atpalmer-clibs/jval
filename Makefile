BIN=bin
SOURCES=src/*.c
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -I./include/

samples: sample1

sample%: $(SOURCES) samples/sample%.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/$@ $?

.PHONY: clean
clean:
	rm -r $(BIN)
