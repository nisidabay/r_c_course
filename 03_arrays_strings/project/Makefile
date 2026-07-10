CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -Werror
LDFLAGS =

.PHONY: all clean run

all: grep-lite

grep-lite: project.c
	$(CC) $(CFLAGS) -o $@ $^

run: grep-lite
	./grep-lite test <<< "this is a test line"

clean:
	$(RM) grep-lite
