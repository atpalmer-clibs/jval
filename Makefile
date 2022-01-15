BIN=bin
SOURCES=src/*.c
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -I./include/

samples: sample0 sample_hello sample_jval

sample%: $(SOURCES) samples/sample%.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/$@ $?

.PHONY: clean
clean:
	rm -r $(BIN)
