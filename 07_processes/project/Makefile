CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -Werror
LDFLAGS =

.PHONY: all clean run

all: runit

runit: project.c
	$(CC) $(CFLAGS) -o $@ $^

run: runit
	TIMEOUT=2 ./runit echo hello

clean:
	$(RM) runit
