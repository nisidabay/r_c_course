CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic -Werror
LDFLAGS =

.PHONY: all clean run

all: divider

divider: project.c
	$(CC) $(CFLAGS) -o $@ $^

run: divider
	./divider 10 + 3
	./divider 42 / 7
	./divider 100 x 2

clean:
	$(RM) divider
