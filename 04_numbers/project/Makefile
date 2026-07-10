CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -Werror
LDFLAGS =

.PHONY: all clean run

all: calc

calc: project.c
	$(CC) $(CFLAGS) -o $@ $^

run: calc
	./calc 42 + 8

clean:
	$(RM) calc
