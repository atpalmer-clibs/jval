BIN=bin
SOURCES=src/*.c
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -I./include/

samples: sample_hello sample_jval sample_bool sample_null sample_json \
	sample_object sample_parse

sample%: $(SOURCES) samples/sample%.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/$@ $?

.PHONY: clean
clean:
	rm -r $(BIN)
