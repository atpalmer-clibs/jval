SOURCES=src/*.c
CC=gcc
CFLAGS=-Wall -Wextra -pedantic -I./include/
ALL=main

all: $(ALL)

%: $(SOURCES) %.c
	$(CC) $(CFLAGS) -o $@ $?

.PHONY: clean
clean:
	rm $(ALL)
